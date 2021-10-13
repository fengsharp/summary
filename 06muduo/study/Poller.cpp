#include "Poller.h"

#include <assert.h>
#include <errno.h>
#include <poll.h>
#include <sys/epoll.h>
#include <unistd.h>

#include <iostream>

#include "Channel.h"
#include "EventLoop.h"

static_assert(EPOLLIN == POLLIN, "EPOLLIN == POLLIN");
static_assert(EPOLLPRI == POLLPRI, "EPOLLPRI == POLLPRI");
static_assert(EPOLLOUT == POLLOUT, "EPOLLOUT == POLLOUT");
static_assert(EPOLLRDHUP == POLLRDHUP, "EPOLLRDHUP == POLLRDHUP");
static_assert(EPOLLERR == POLLERR, "EPOLLERR == POLLERR");
static_assert(EPOLLHUP == POLLHUP, "EPOLLHUP == POLLHUP");

const int kNew = -1;
const int kAdded = 1;
const int kDeleted = 2;

Poller::Poller(EventLoop *loop)
    : loop_(loop),
      epollFd_(::epoll_create1(EPOLL_CLOEXEC)),
      vecEvents_(kInitEventListsize)
{
}

Poller::~Poller()
{
    ::close(epollFd_);
}

Timestamp Poller::poll(int timeoutMs, std::vector<Channel *> *pOutChannels)
{
    // std::cout << "fd total count" << mapchannels_.size() << std::endl;
    int numEvents = ::epoll_wait(epollFd_, vecEvents_.data(), vecEvents_.size(), timeoutMs);
    int savedErron = errno;
    Timestamp now(Timestamp::now());
    if (numEvents > 0)
    {
        // LOG_TRACE << numEvents << " events happened";
        fillActiveChannels(numEvents, pOutChannels);
        if (implicit_cast<size_t>(numEvents) == vecEvents_.size())
        {
            vecEvents_.resize(vecEvents_.size() * 2);
        }
    }
    else if (numEvents == 0)
    {
        // LOG_TRACE << "nothing happened";
    }
    else
    {
        if (savedErron != EINTR)
        {
            errno = savedErron;
            // LOG_SYSERR << "poll()";
        }
    }

    return now;
}

void Poller::assertInLoopThread() const
{
    return loop_->assertInLoopThread();
}

void Poller::fillActiveChannels(int numEvents, std::vector<Channel *> *pOutActiveChannles) const
{
    assert(implicit_cast<size_t>(numEvents) <= vecEvents_.size());
    for (int i = 0; i < numEvents; ++i)
    {
        Channel *pChannel = static_cast<Channel *>(vecEvents_[i].data.ptr);
#ifndef NDEBUG
        int fd = pChannel->fd();
        std::map<int, Channel *>::const_iterator it = mapChannels_.find(fd);
        assert(it != mapChannels_.end() && it->second == pChannel);
#endif
        pChannel->setReceiveEvents(vecEvents_[i].events);
        pOutActiveChannles->push_back(pChannel);
    }
}

const char *Poller::operationToString(int op)
{
    switch (op)
    {
    case EPOLL_CTL_ADD:
        return "ADD";
    case EPOLL_CTL_DEL:
        return "DEL";
    case EPOLL_CTL_MOD:
        return "MOD";
    default:
        assert(false && "ERROR OP");
        return "Unknown Operation";
    }
}

bool Poller::hasChannel(Channel *pChannel) const
{
    assertInLoopThread();
    std::map<int, Channel *>::const_iterator it = mapChannels_.find(pChannel->fd());
    return it != mapChannels_.end() && it->second == pChannel;
}

void Poller::update(int operation, Channel *pChannel)
{
    struct epoll_event event;
    memZero(&event, sizeof(event));
    event.events = pChannel->events();
    event.data.ptr = pChannel;
    int fd = pChannel->fd();
    // LOG_TRACE << "epoll_ctrl op=" << operationToString(operation)
    //           << " fd=" << fd << " event={" << pChannel->eventsToString() << "}";
    if (::epoll_ctl(epollFd_, operation, fd, &event) < 0)
    {
        if (operation == EPOLL_CTL_DEL)
        {
            // LOG_SYSERR << "epoll_ctl op = " << operationToString(operation) << " fd = " << fd;
        }
        else
        {
            // LOG_SYSFATAL << "epoll_ctl op = " << operationToString(operation) << " fd = " << fd;
        }
    }
}

void Poller::removeChannel(Channel *pChannel)
{
    assertInLoopThread();
    int fd = pChannel->fd();
    assert(mapChannels_.find(fd) != mapChannels_.end());
    assert(mapChannels_[fd] == pChannel);
    assert(pChannel->isNoneEvents());
    int state = pChannel->pollerState();
    assert(state == kAdded || state == kDeleted);
    size_t n = mapChannels_.erase(fd);
    (void)n;
    assert(n == 1);

    if (state == kAdded)
    {
        update(EPOLL_CTL_DEL, pChannel);
    }
    pChannel->setPollerState(kNew);
}

void Poller::updateChannel(Channel *pChannel)
{
    assertInLoopThread();
    const int state = pChannel->pollerState();
    // LOG_TRACE << "fd=" << pChannel->fd() << " events=" << pChannel->events() << " state=" << state;
    if (state == kNew || state == kDeleted)
    {
        int fd = pChannel->fd();
        if (state == kNew)
        {
            assert(mapChannels_.find(fd) == mapChannels_.end());
            mapChannels_[fd] = pChannel;
        }
        else
        {
            assert(mapChannels_.find(fd) != mapChannels_.end());
            assert(mapChannels_[fd] == pChannel);
        }
        pChannel->setPollerState(kAdded);
        update(EPOLL_CTL_ADD, pChannel);
    }
    else
    {
        int fd = pChannel->fd();
        (void)fd;
        assert(mapChannels_.find(fd) != mapChannels_.end());
        assert(mapChannels_[fd] == pChannel);
        assert(state == kAdded);
        if (pChannel->isNoneEvents())
        {
            update(EPOLL_CTL_DEL, pChannel);
            pChannel->setPollerState(kDeleted);
        }
        else
        {
            update(EPOLL_CTL_MOD, pChannel);
        }
    }
}