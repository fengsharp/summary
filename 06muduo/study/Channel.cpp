#include "Channel.h"

#include <iostream>

#include <poll.h>
#include <sstream>

#include "EventLoop.h"

const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = POLLIN | POLLPRI;
const int Channel::kWriteEvent = POLLOUT;

Channel::Channel(EventLoop *pLoop, int fd)
    : loop_(pLoop), 
      fd_(fd), 
      events_(0), 
      revents_(0), 
      pollerStatus_(-1)
{
}

Channel::~Channel()
{
    // assert(m_bAddedToLoop == false);
    // if (m_pLoop->isInLoopThread())
    // {
    //     assert(m_pLoop->hasChannel(this) == false);
    // }
}

void Channel::update()
{
    loop_->updateChannel(this);
}

void Channel::handleEvent()
{
    if (revents_ & POLLNVAL)
    {
        std::cout << "Channel::handle_event() POLLNVAL" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (revents_ & (POLLERR | POLLNVAL))
    {
        if (errorCallback_)
            errorCallback_();
    }
    if (revents_ & (POLLIN | POLLPRI | POLLRDHUP))
    {
        if (readCallback_)
            readCallback_();
    }
    if (revents_ & POLLOUT)
    {
        if (writeCallback_)
            writeCallback_();
    }
}
