#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdbool.h>

#include "common.h"

struct _Queue;
typedef struct _Queue Queue;

Queue* queue_create();

void* queue_get_frot(Queue *thiz);
void queue_pop_frot(Queue *thiz, FuncFreeElement callbackFree);
void queue_push_back(Queue *thiz, void *element);
bool queue_is_empty(Queue *thiz);

void queue_destory(Queue *thiz);

#endif