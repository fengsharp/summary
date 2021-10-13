#include "EventLoop.h"

#include <iostream>
#include <assert.h>

#include <unistd.h>

#include "Channel.h"
#include "Poller.h"

__thread EventLoop *t_loopInThisThread = 0;
const int kPollTimeMs = 10000;

EventLoop::EventLoop()
    : looping_(false),
      quit_(false),
      threadId_(CurrentThread::tid()),
      poller_(new Poller(this))
{
    t_loopInThisThread = this;
}

EventLoop::~EventLoop()
{
    t_loopInThisThread = NULL;
}

void EventLoop::loop()
{
    assertInLoopThread();
    looping_ = true;
    quit_ = false;

    while (quit_ == false)
    {
        activeChannels_.clear();
        poller_->poll(kPollTimeMs, &activeChannels_);
        for (Channel *it : activeChannels_)
        {
            it->handleEvent();
        }
    }

    looping_ = false;
}

void EventLoop::assertInLoopThread()
{
    if (!isInLoopThread())
    {
        abortNotInLoopThread();
    }
}

bool EventLoop::isInLoopThread() const
{
    return CurrentThread::tid() == threadId_;
}

void EventLoop::abortNotInLoopThread()
{
    std::cout << "EventLoop::abortNotInLoopThread error" << CurrentThread::tid() << std::endl;
    exit(EXIT_FAILURE);
}

void EventLoop::quit()
{
    quit_ = true;
    if (!isInLoopThread())
    {
        // wake up
    }
}

void EventLoop::updateChannel(Channel * pChannel)
{
    assert(pChannel->ownerLoop() == this);
    assertInLoopThread();
    poller_->updateChannel(pChannel);
}

void EventLoop::removeChannel(Channel * pChannel)
{
    assert(pChannel->ownerLoop() == this);
    assertInLoopThread();
    // if (m_bEventHanding)
    // {
    //     assert(m_pCurrentActiveChannel == pChannel || std::find(m_vecActiveChannels.begin(), m_vecActiveChannels.end(), pChannel) == m_vecActiveChannels.end());
    // }
    poller_->removeChannel(pChannel);
}