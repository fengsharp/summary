#include "Thread.h"

#include <cassert>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>

#include <sys/prctl.h>
#include <linux/unistd.h>

namespace CurrentThread
{
    __thread const char *t_threadName = "unnamedThread";
}

pid_t gettid()
{
    return static_cast<pid_t>(::syscall(SYS_gettid));
}

__thread pid_t t_cachedTid = 0;

void afterFork()
{
    t_cachedTid = gettid();
    CurrentThread::t_threadName = "main";
}

class ThreadNameInitializer
{
public:
    ThreadNameInitializer()
    {
        CurrentThread::t_threadName = "main";
        pthread_atfork(NULL, NULL, &afterFork);
    }
};

ThreadNameInitializer init;

struct ThreadData
{
    Thread::ThreadFunc func_;
    std::string name_;
    std::weak_ptr<pid_t> wkTid_;

    ThreadData(const Thread::ThreadFunc &func,
               const std::string &name,
               const std::shared_ptr<pid_t> &tid)
        : func_(func),
          name_(name),
          wkTid_(tid)
    {
    }

    void runInThread()
    {
        pid_t tid = CurrentThread::tid();
        std::shared_ptr<pid_t> ptid = wkTid_.lock();

        if (ptid)
        {
            *ptid = tid;
            ptid.reset();
        }

        if (!name_.empty())
        {
            CurrentThread::t_threadName = name_.c_str();
        }
        ::prctl(PR_SET_NAME, CurrentThread::t_threadName);
        func_();
        CurrentThread::t_threadName = "finished";
    }
};

void *startThread(void *obj)
{
    ThreadData *data = static_cast<ThreadData *>(obj);
    data->runInThread();
    delete data;
    return NULL;
}

pid_t CurrentThread::tid()
{
    if (t_cachedTid == 0)
    {
        t_cachedTid = gettid();
    }
    return t_cachedTid;
}

const char *CurrentThread::name()
{
    return t_threadName;
}

bool CurrentThread::isMainThread()
{
    return tid() == ::getpid();
}

AtomicInt32 Thread::numCreated_;

Thread::Thread(const ThreadFunc &func, const std::string &n)
    : started_(false),
      joined_(false),
      pthreadId_(0),
      tid_(new pid_t(0)),
      func_(func),
      name_(n)
{
    numCreated_.increment();
}

Thread::~Thread()
{
    if (started_ && !joined_)
    {
        pthread_detach(pthreadId_);
    }
}

void Thread::start()
{
    assert(!started_);
    started_ = true;

    ThreadData *data = new ThreadData(func_, name_, tid_);
    if (pthread_create(&pthreadId_, NULL, &startThread, data))
    {
        started_ = false;
        delete data;
        abort();
    }
}

void Thread::join()
{
    assert(started_);
    assert(!joined_);
    joined_ = true;
    pthread_join(pthreadId_, NULL);
}