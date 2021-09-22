#include "threadpool.h"
#include <pthread.h>
#include <memory>
#include <iostream>

// 初始化线程池
void threadpool_init(ThreadPool *pool, int threads)
{
   // pool = (threadpool_t*)malloc(sizeof(pool));
    pool->ready = condition_create();
    pool->first = NULL;
    pool->last = NULL;
    pool->counter = 0;
    pool->idle = 0;
    pool->max_threads = threads;
    pool->quit = 0;
}

// 销毁线程池
void threadpool_destroy(ThreadPool *thiz)
{
    if (thiz->quit)
    {
        return;
    }
    condition_lock(thiz->ready);
    thiz->quit = true;
    if (thiz->counter > 0)
    {
        if (thiz->idle > 0)
        {
            condition_broadcast(thiz->ready);
        }
        // 处于执行任务状态中的线程，不会收到广播
        // 线程池需要等执行任务状态中的线程全部退出
        while (thiz->counter > 0)
        {
            condition_wait(thiz->ready);
        }
    }
    condition_unlock(thiz->ready);
    condition_destroy(thiz->ready);
}

void *thread_routine(void *args)
{
    ThreadPool *pool = (ThreadPool*)args;
    while (true)
    {
        condition_lock(pool->ready);
        ++pool->idle;
        // 等待队列有任务到来或者线程池销毁通知
        while (pool->first == NULL && pool->quit == false)
        {
            printf("thread 0x%x is waiting\n", (int)pthread_self());
            condition_wait(pool->ready);
        }

        --pool->idle;
        if (pool->first != NULL)
        {
            Task *t = pool->first;
            pool->first = t->next;
            condition_unlock(pool->ready);
            t->run(t->args);
            free(t);
            condition_lock(pool->ready);
        }

        if (pool->quit && pool->first == NULL)
        {
            --pool->counter;
            if (pool->counter == 0)
            {
                condition_signal(pool->ready);
            }
            condition_unlock(pool->ready);
            break;
        }

        if (pool->first == NULL)
        {
            condition_unlock(pool->ready);
            break;
        }
        condition_unlock(pool->ready);
    }

    printf("thread 0x%x is exiting \n", (int)pthread_self());
    return NULL;
}

void threadpool_add_task(ThreadPool *thiz, void *(*run)(void *args), void *args)
{
    Task *newTask = (Task*)malloc(sizeof(Task));
    newTask->run = run;
    newTask->args = args;
    newTask->next = NULL;

    condition_lock(thiz->ready);
    if (thiz->first == NULL)
    {
        thiz->first = newTask;
    }
    else
    {
        thiz->last->next = newTask;
    }
    thiz->last = newTask;

    if (thiz->idle > 0)
    {
        condition_signal(thiz->ready);
    }
    else if (thiz->counter < thiz->max_threads)
    {
        // 没有等待线程，并且当前线程数不超过最大线程数,则创建一个新线程
        pthread_t tid;
        pthread_create(&tid, NULL, thread_routine, thiz);
        ++thiz->counter;
    }
    condition_unlock(thiz->ready);
}