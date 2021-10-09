#ifndef SINGLETON_H_
#define SINGLETON_H_

#include "noncopyable.h"

#include <stdlib.h>

#include <pthread.h>

template <typename T>
class Singleton : private noncopyable
{
public:
    static T &instance()
    {
        pthread_once(&ponce_, &Singleton::init);
        return *value_;
    }

private:
    Singleton() = delete;
    ~Singleton() = delete;

    static void init()
    {
        value_ = new T();
        ::atexit(destroy);
    }

    static void destroy()
    {
        delete value_;
    }

private:
    static pthread_once_t ponce_;
    static T *value_;
};

template <typename T>
pthread_once_t Singleton<T>::ponce_ = PTHREAD_ONCE_INIT;

template <typename T>
T *Singleton<T>::value_ = NULL;

#endif