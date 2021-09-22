#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_

#include "condition.h"

typedef struct _Task
{
    void *(*run)(void *args);
    void *args;
    struct _Task *next;
} Task;

typedef struct _ThreadPool
{
    Condition *ready;
    Task *first;
    Task *last;
    int counter;
    int idle;
    int max_threads;
    bool quit;
} ThreadPool;

void threadpool_int(ThreadPool *pool, int threads);
void threadpool_add_task(ThreadPool *thiz, void *(*run)(void *args), void *args);
void threadpool_destroy(ThreadPool *thiz);

#endif