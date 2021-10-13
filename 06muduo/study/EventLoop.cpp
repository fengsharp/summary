#include "EventLoop.h"

#include <iostream>

#include <unistd.h>

__thread EventLoop* t_loopInThisThread = 0;

EventLoop::EventLoop()
    : looping_(false),
      threadId_(CurrentThread::tid())
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

    usleep(1000);
    printf("eventloop %p %d\n", this, threadId_);

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
