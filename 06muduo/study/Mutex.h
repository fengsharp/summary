#ifndef MUTEX_H_
#define MUTEX_H_

#include "noncopyable.h"
#include "Thread.h"

#include <assert.h>
#include <pthread.h>

class MutexLock : private noncopyable
{
public:
    MutexLock()
        : holder_(0)
    {
        pthread_mutex_init(&mutex_, NULL);
    }

    ~MutexLock()
    {
        assert(holder_ == 0);
        pthread_mutex_destroy(&mutex_);
    }

    bool isLockedByThisThread()
    {
        return holder_ == CurrentThread::tid();
    }

    void assertLocked()
    {
        assert(isLockedByThisThread());
    }

    void lock()
    {
        pthread_mutex_lock(&mutex_);
        holder_ = CurrentThread::tid();
    }

    void unlock()
    {
        holder_ = 0;
        pthread_mutex_unlock(&mutex_);
    }

    pthread_mutex_t *getPthreadMutex()
    {
        return &mutex_;
    }

private:
    pthread_mutex_t mutex_;
    pid_t holder_;
};

class MutexLockGuard : private noncopyable
{
public:
    explicit MutexLockGuard(MutexLock &mutex)
        : mutex_(mutex)
    {
        mutex_.lock();
    }

    ~MutexLockGuard()
    {
        mutex_.unlock();
    }

private:
    MutexLock &mutex_;
};

// Prevent misuse like: MutexLockGuard(mutex_);
#define MutexLockGuard(x) error "Missing guard object name"

#endif