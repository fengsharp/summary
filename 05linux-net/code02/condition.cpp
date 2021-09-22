#include "condition.h"

#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>
#include <errno.h>

void err_exit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

struct _Condition
{
    pthread_mutex_t pmutex;
    pthread_cond_t pcond;
};

Condition *condition_create()
{
    Condition *pRet = (Condition *)malloc(sizeof(Condition));
    pthread_cond_init(&pRet->pcond, NULL);
    pthread_mutex_init(&pRet->pmutex, NULL);
    return pRet;
}

void condition_destroy(Condition *thiz)
{
    pthread_cond_destroy(&thiz->pcond);
    pthread_mutex_destroy(&thiz->pmutex);
    free(thiz);
}

void condition_lock(Condition *thiz)
{
    pthread_mutex_lock(&thiz->pmutex);
}

void condition_unlock(Condition *thiz)
{
    pthread_mutex_unlock(&thiz->pmutex);
}

void condition_wait(Condition *thiz)
{
    pthread_cond_wait(&thiz->pcond, &thiz->pmutex);
}

void condition_signal(Condition *thiz)
{
    pthread_cond_signal(&(thiz->pcond));
}

void condition_broadcast(Condition *thiz)
{
    pthread_cond_broadcast(&(thiz->pcond));
}
