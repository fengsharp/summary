#include <iostream>

#include "Atomic.h"

int main()
{
    AtomicInt32 atomicValue;
    atomicValue.getAndSet(30);
    atomicValue.increment();
    std::cout << atomicValue.getAndAdd(5) << std::endl;
    std::cout << atomicValue.get() << std::endl;

    return 0;
}