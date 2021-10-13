#include <stdio.h>

#include "EventLoop.h"
#include "Thread.h"

void work()
{
    EventLoop loop;
    loop.loop();
}

int main()
{
    EventLoop loop;
    loop.loop();

    Thread t(std::bind(work), "work");
    t.start();
    t.join();

    puts("=== over. ===");

    return 0;
}

// EventLoop *g_loop = NULL;

// void work()
// {
//     g_loop->loop();
// }

// int main()
// {
//     EventLoop loop;
//     g_loop = &loop;

//     Thread t(std::bind(work), "work");
//     t.start();
//     t.join();

//     puts("=== over. ===");

//     return 0;
// }
