#ifndef POLLER_H_
#define POLLER_H_

#include <map>
#include <vector>

#include "Timestamp.h"

class EventLoop;
struct epoll_event;
class Channel;

class Poller
{
public:
    explicit Poller(EventLoop* pLoop);
    ~Poller();

    Timestamp poll(int timeoutMs, std::vector<Channel*>* pOutActiveChannles);
    void updateChannel(Channel* pChannel);
    void removeChannel(Channel* pChannel);

    bool hasChannel(Channel* pChannel) const;
    void assertInLoopThread() const;
private:
    static const int kInitEventListsize = 16;
    static const char* operationToString(int op);
    void fillActiveChannels(int numEvents, std::vector<Channel*>* pOutActiveChannles) const;
    void update(int operation, Channel* pChannel);
    

private:
    EventLoop* loop_;
    std::map<int, Channel*> mapChannels_;

    int epollFd_;
    std::vector<struct epoll_event> vecEvents_;
};


#endif