#include <stdio.h>

#include <string>
#include <vector>
#include <memory>
#include <functional>

#include "Thread.h"
#include "Mutex.h"
#include "Condition.h"
#include "CountDownLatch.h"
#include "BlockingQueue.h"

class Workers
{
public:
    explicit Workers(int threadNums)
        : latch_(threadNums)
    {
        for (int i = 0; i < threadNums; ++i)
        {
            char name[32];
            snprintf(name, sizeof name, "work thread %d", i);
            std::unique_ptr<Thread> thread = std::make_unique<Thread>(std::bind(&Workers::func, this), name);
            threads_.emplace_back(std::move(thread));
        }

        for (const auto &it : threads_)
        {
            it->start();
        }
    }

    void joinAll()
    {
        for (size_t i = 0; i < threads_.size(); ++i)
        {
            queue_.put("stop");
        }

        for (const auto &it : threads_)
        {
            it->join();
        }
    }

    void work(int taskNum)
    {
        latch_.wait();

        for (int i = 0; i < taskNum; ++i)
        {
            char buf[32];
            snprintf(buf, sizeof buf, "\t * task * %d", i);
            queue_.put(buf);
        }
    }

private:
    void func()
    {
        latch_.countDown();

        while (true)
        {
            std::string msg(queue_.take());
            if (msg == "stop")
            {
                break;
            }

            printf("tid=%d, get data = %s, size = %zd\n", CurrentThread::tid(), msg.c_str(), queue_.size());
        }

        printf("tid=%d, %s stopped\n", CurrentThread::tid(), CurrentThread::name());
    }

private:
    BlockingQueue<std::string> queue_;
    std::vector<std::unique_ptr<Thread>> threads_;
    CountDownLatch latch_;
};


int main()
{
    Workers workers(2);
    workers.work(10);
    workers.joinAll();

    printf("number of created threads %d\n", Thread::numCreated());

    return 0;
}