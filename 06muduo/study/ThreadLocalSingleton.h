#ifndef THREAD_LOCAL_SINGLETON_H_
#define THREAD_LOCAL_SINGLETON_H_

#include "noncopyable.h"

template <typename T>
class ThreadLocalSingleton : private noncopyable
{
public:
    static T &instance()
    {
        if (!t_value_)
        {
            t_value_ = new T();
        }
        return *t_value_;
    }

    static void destroy()
    {
        delete t_value_;
        t_value_ = NULL;
    }

private:
    ThreadLocalSingleton() = delete;
    ~ThreadLocalSingleton() = delete;

    static __thread T *t_value_;
};

template <typename T>
__thread T *ThreadLocalSingleton<T>::t_value_ = 0;

#endif