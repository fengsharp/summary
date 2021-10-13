#ifndef EVENT_LOOP_H_
#define EVENT_LOOP_H_

#include "noncopyable.h"
#include "Thread.h"


class EventLoop : private noncopyable
{
public:
    EventLoop();
    ~EventLoop();

    void loop();

    void assertInLoopThread();
    bool isInLoopThread() const;
private:
    void abortNotInLoopThread();
private:
    bool looping_;
    const pid_t threadId_;
};

#endif