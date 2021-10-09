#ifndef THREAD_LOCAL_H_
#define THREAD_LOCAL_H_

#include "noncopyable.h"

#include <pthread.h>

template <typename T>
class ThreadLocal : private noncopyable
{
public:
    ThreadLocal()
    {
        pthread_key_create(&pkey_, &ThreadLocal::destructor);
    }

    ~ThreadLocal()
    {
        pthread_key_delete(pkey_);
    }

    T &value()
    {
        T *perThreadValue = static_cast<T *>(pthread_getspecific(pkey_));
        if (!perThreadValue)
        {
            T *newObj = new T();
            pthread_setspecific(pkey_, newObj);
            perThreadValue = newObj;
        }
        return *perThreadValue;
    }

private:
    static void destructor(void *x)
    {
        T *obj = static_cast<T *>(x);
        delete obj;
    }

private:
    pthread_key_t pkey_;
};

#endif