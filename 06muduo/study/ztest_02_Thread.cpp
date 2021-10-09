#include <iostream>

#include "Thread.h"

int main()
{
    Thread task1([] () {
        std::cout << "task1 " << CurrentThread::name() << std::endl;
    }, "xxxTask1");
    Thread task2([] () {
        std::cout << "task2 " << CurrentThread::name() << std::endl;
    }, "xxxTask2");

    task1.start();
    task2.start();
    task1.join();
    task2.join();

    std::cout << " === over. === " << std::endl;

    return 0;
}