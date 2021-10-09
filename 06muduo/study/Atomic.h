#ifndef ATOMIC_H_
#define ATOMIC_H_

#include "noncopyable.h"

#include <stdint.h>

// __ATOMIC_SEQ_CST 最严格的模式

template <typename T>
class AtomicIntegerT : private noncopyable
{
public:
    AtomicIntegerT()
        : value_(0)
    {
    }

    T get()
    {
        return __atomic_load_n(&value_, __ATOMIC_SEQ_CST);
    }

    T getAndAdd(T x)
    {
        return __atomic_fetch_add(&value_, x, __ATOMIC_SEQ_CST);
    }

    T addAndGet(T x)
    {
        return getAndAdd(x) + x;
    }

    T incrementAddGet()
    {
        return addAndGet(1);
    }

    T decrementAndGet()
    {
        return addAndGet(-1);
    }

    void add(T x)
    {
        getAndAdd(x);
    }

    void increment()
    {
        getAndAdd(1);
    }

    void decrement()
    {
        getAndAdd(-1);
    }

    T getAndSet(T newValue)
    {
        return __atomic_exchange_n(&value_, newValue, __ATOMIC_SEQ_CST);
    }

private:
    volatile T value_;
};

typedef AtomicIntegerT<int32_t> AtomicInt32;
typedef AtomicIntegerT<int64_t> AtomicInt64;

#endif