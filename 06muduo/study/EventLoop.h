#ifndef EVENT_LOOP_H_
#define EVENT_LOOP_H_

#include <vector>

#include "noncopyable.h"
#include "Thread.h"

class Channel;
class Poller;

class EventLoop : private noncopyable
{
public:
    EventLoop();
    ~EventLoop();

    void loop();
    void quit();

    void updateChannel(Channel *channel);
    void removeChannel(Channel * pChannel);

    void assertInLoopThread();
    bool isInLoopThread() const;

private:
    void abortNotInLoopThread();

private:
    bool looping_;
    bool quit_;
    const pid_t threadId_;

    std::unique_ptr<Poller> poller_;

    std::vector<Channel *> activeChannels_;
};

#endif