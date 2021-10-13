#ifndef CHANNEL_H_
#define CHANNEL_H_

#include "noncopyable.h"

#include <functional>

class EventLoop;

class Channel : private noncopyable
{
public:
    typedef std::function<void(void)> EventCallback;

    Channel(EventLoop *loop, int fd);
    ~Channel();

    void handleEvent();
    void setReadCallback(const EventCallback &cb)
    {
        readCallback_ = cb;
    }
    void setWriteCallback(const EventCallback &cb)
    {
        writeCallback_ = cb;
    }
    void setErrorCallback(const EventCallback &cb)
    {
        errorCallback_ = cb;
    }

    int fd() const { return fd_; }
    int events() const { return events_; }

    void setReceiveEvents(int revt)
    {
        revents_ = revt;
    }
    bool isNoneEvents() const
    {
        return events_ == kNoneEvent;
    }

    void enableReading()
    {
        events_ |= kReadEvent;
        update();
    }
    void disableReading()
    {
        events_ &= ~kReadEvent;
        update();
    }
    void enableWriting()
    {
        events_ |= kWriteEvent;
        update();
    }
    void disableWriting()
    {
        events_ &= ~kWriteEvent;
        update();
    }
    void disableAll()
    {
        events_ = kNoneEvent;
        update();
    }
    bool isWriting() const
    {
        return events_ & kWriteEvent;
    }
    bool isReading() const
    {
        return events_ & kReadEvent;
    }

    int pollerState() const
    {
        return pollerStatus_;
    }
    void setPollerState(int state)
    {
        pollerStatus_ = state;
    }

    EventLoop *ownerLoop()
    {
        return loop_;
    }

private:
    void update();

private:
    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    EventLoop *loop_;
    const int fd_;
    int events_;
    int revents_;
    int pollerStatus_;

    EventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback errorCallback_;
};

#endif