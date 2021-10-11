#include <stdio.h>
#include <string>
#include <unistd.h>

#include "ThreadPool.h"
#include "CountDownLatch.h"

void task(const std::string &msg)
{
    printf("tid=%d, str=%s\n", CurrentThread::tid(), msg.c_str());
    usleep(20);
}

int main()
{
    ThreadPool pool("main pool");
    pool.start(5);

    for (int i = 0; i < 100; ++i)
    {
        char buf[32];
        snprintf(buf, sizeof buf, "task %d", i);
        pool.run(std::bind(task, std::string(buf)));
    }

    CountDownLatch latch(1);
    pool.run(std::bind(&CountDownLatch::countDown, &latch));
    latch.wait();
    pool.stop();

    puts("=== over. ===");

    return 0;
}