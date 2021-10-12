#include <stdio.h>
#include <memory>
#include <vector>

#include "Mutex.h"
#include "Thread.h"

class Observable;
class Observer : public std::enable_shared_from_this<Observer>
{
public:
    Observer()
    {
        printf("Observer %p\n", this);
    }

    ~Observer()
    {
        printf("~Observer %p\n", this);
    }

    void update()
    {
        printf("Observer::update %p\n", this);
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
                printf("notifyObservers() erase\n");
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

int main()
{
    std::shared_ptr<Observable> subject = std::make_shared<Observable>();
    {
        std::shared_ptr<Observer> p = std::make_shared<Observer>();
        p->observe(subject);
        subject->notifyObservers();
    }
    subject->notifyObservers();

    return 0;
}

/*
Observable 管理 Observer，但是不负责 Observer 的生命周期
所以添加接口和数据集合都用 std::weak_ptr
使用时，需要判断是否存在
*/