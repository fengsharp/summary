#include "Mutex.h"

class Request
{
public:
    void process() // __attribute__ ((noinline))
    {
        MutexLockGuard lock(mutex_);
        print();
    }

    void print() const // __attribute__ ((noinline))
    {
        MutexLockGuard lock(mutex_);
    }

private:
    mutable MutexLock mutex_;
};

int main()
{
    Request req;
    req.process();
}

/*
#0  0x00007fc6b926665d in __lll_lock_wait () from /lib64/libpthread.so.0
#1  0x00007fc6b925f979 in pthread_mutex_lock () from /lib64/libpthread.so.0
#2  0x0000000000404559 in MutexLock::lock (this=0x7ffda27b35e0) at ./Mutex.h:37
#3  0x00000000004042e3 in MutexLockGuard::MutexLockGuard (this=0x7ffda27b3560, mutex=...) at ./Mutex.h:63
#4  0x0000000000407929 in Request::print (this=0x7ffda27b35e0) at ztest_10_SelfDeadLock.cpp:14
#5  0x00000000004078b6 in Request::process (this=0x7ffda27b35e0) at ztest_10_SelfDeadLock.cpp:9
#6  0x000000000040782e in main () at ztest_10_SelfDeadLock.cpp:24
*/