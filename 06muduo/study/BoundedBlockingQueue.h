#ifndef BOUNDED_BLOCKING_QUEUE_H_
#define BOUNDED_BLOCKING_QUEUE_H_

#include "noncopyable.h"
#include "Mutex.h"
#include "Condition.h"

#include <deque>
#include <assert.h>

template <typename T>
class BoundedBlockingQueue : private noncopyable
{
public:
    explicit BoundedBlockingQueue(int maxSize)
        : maxSize_(maxSize),
          mutex_(),
          notEmpty_(mutex_),
          notFull_(mutex_),
    {
    }

    void put(const T &x)
    {
        MutexLockGuard lock(mutex_);
        while (queue_.size() == maxSize_)
        {
            notFull_.wait();
        }
        assert(queue_.size() < maxSize_);

        queue_.push_back(x);
        notEmpty_.notify();
    }

    T take()
    {
        MutexLockGuard lock(mutex_);
        while (queue_.empty())
        {
            notEmpty_.wait();
        }
        assert(!queue_.empty());
        T front(queue_.front());
        queue_.pop_front();
        notFull_.notify();
        return front;
    }

    bool empty() const
    {
        MutexLockGuard lock(mutex_);
        return queue_.empty();
    }

    bool full() const
    {
        MutexLockGuard lock(mutex_);
        return queue_.size() == maxSize_;
    }

    size_t size() const
    {
        MutexLockGuard lock(mutex_);
        return queue_.size();
    }

    size_t capacity() const
    {
        MutexLockGuard lock(mutex_);
        return queue_.capacity();
    }

private:
    const unsigned maxSize_;
    mutable MutexLock mutex_;
    Condition notEmpty_;
    Condition notFull_;
    std::deque<T> queue_;
};

#endif