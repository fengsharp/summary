#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_

#include "noncopyable.h"
#include "Mutex.h"
#include "Condition.h"
#include "Thread.h"

#include <functional>
#include <vector>
#include <string>
#include <memory>
#include <deque>

class ThreadPool : private noncopyable
{
public:
    typedef std::function<void()> Task;

    explicit ThreadPool(const std::string & name = std::string());
    ~ThreadPool();

    void start(int numThreads);
    void stop();

    void run(const Task& f);
private:
    void runInThread();
    Task take();
private:
    MutexLock mutex_;
    Condition cond_;
    std::string name_;

    std::vector<std::unique_ptr<Thread>> threads_;
    std::deque<Task> queue_;
    bool running_;
};

#endif