#include <stdio.h>
#include <memory>
#include <vector>

#include <unistd.h>

#include "Mutex.h"
#include "Thread.h"

class Observable;
class Observer : public std::enable_shared_from_this<Observer>
{
public:
    Observer()
    {
        printf("tid: %d %s, Observer %p\n", CurrentThread::tid(), CurrentThread::name(), this);
    }

    ~Observer()
    {
        printf("tid: %d %s, ~Observer start %p\n", CurrentThread::tid(), CurrentThread::name(), this);
        usleep(1000);
        printf("tid: %d %s, ~Observer end %p\n", CurrentThread::tid(), CurrentThread::name(), this);
    }

    void update()
    {
        printf("### tid: %d %s, Observer::update start %p\n", CurrentThread::tid(), CurrentThread::name(), this);
        usleep(110);
        printf("### tid: %d %s, Observer::update end %p\n", CurrentThread::tid(), CurrentThread::name(), this);
    }

    void observe(std::weak_ptr<Observable> s);
};

class Observable
{
public:
    void register_(std::weak_ptr<Observer> x)
    {
        MutexLockGuard lock(mutex_);
        observers_.push_back(x);
    }

    void notifyObservers()
    {
        usleep(20);
        MutexLockGuard lock(mutex_);
        std::vector<std::weak_ptr<Observer>>::iterator it = observers_.begin();
        while (it != observers_.end())
        {
            std::shared_ptr<Observer> obj(it->lock());
            if (obj)
            {
                obj->update();
                ++it;
            }
            else
            {
                printf("### tid: %d %s, notifyObservers() erase\n", CurrentThread::tid(), CurrentThread::name());
                it = observers_.erase(it);
            }
        }
    }

private:
    MutexLock mutex_;
    std::vector<std::weak_ptr<Observer>> observers_;
};

void Observer::observe(std::weak_ptr<Observable> s)
{
    std::shared_ptr<Observable> observable(s.lock());
    if (observable)
    {
        observable->register_(shared_from_this());
    }
}

std::shared_ptr<Observable> subject = std::make_shared<Observable>();

void task()
{
    std::shared_ptr<Observer> p = std::make_shared<Observer>();
    p->observe(subject);
    usleep(120);
    printf("tid: %d %s, exit thread task.\n", CurrentThread::tid(), CurrentThread::name());
}

int main()
{
    Thread t(std::bind(task), "task");
    t.start();

    printf("tid: %d %s, main notify1.\n", CurrentThread::tid(), CurrentThread::name());
    subject->notifyObservers();

    t.join();

    printf("tid: %d %s, main notify2.\n", CurrentThread::tid(), CurrentThread::name());
    subject->notifyObservers();
    usleep(1000);

    return 0;
}

/*
Observable 管理 Observer，但是不负责 Observer 的生命周期
所以添加接口和数据集合都用 std::weak_ptr
使用时，需要判断是否存在
1. 使用obj时，weak_ptr 可以判断该对象是否已经析构
2. 当前对象使用前，用了智能指针，因此只有当所有线程都不再使用该对象时，才会立刻销毁，销毁时，就不一定时在创建对象的线程中
总结：Observable 使用std::weak_ptr管理聚合对象，内部使用前，判断是否已经销毁才使用，而当所有线程不再引用对象时，才会立刻销毁
*/