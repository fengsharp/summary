#include "queue.h"

#include <stdlib.h>
#include <assert.h>

typedef struct _QueueNode
{
    void *data;
    struct _QueueNode *next;
} QueueNode;

static QueueNode *queue_node_create(void *element)
{
    QueueNode *ret = malloc(sizeof(QueueNode));
    if (ret)
    {
        ret->data = element;
        ret->next = NULL;
    }
    return ret;
}

static void queue_node_destroy(QueueNode *thiz, FuncFreeElement callbackFree)
{
    if (callbackFree)
    {
        callbackFree(thiz->data);
    }

    free(thiz);
}

struct _Queue
{
    QueueNode *head;
    QueueNode *tail;
};


Queue* queue_create()
{
    Queue* ret = malloc(sizeof(Queue));
    if (ret)
    {
        ret->head = NULL;
        ret->tail = NULL;
    }
    return ret;
}

void* queue_get_frot(Queue *thiz)
{
    if (queue_is_empty(thiz))
    {
        return NULL;
    }
    return thiz->head->data;
}

void queue_pop_frot(Queue *thiz, FuncFreeElement callbackFree)
{
    if (queue_is_empty(thiz))
    {
        return;
    }

    QueueNode* head = thiz->head;
    thiz->head = head->next;
    if (queue_is_empty(thiz))
    {
        thiz->tail = NULL;
    }

    queue_node_destroy(head, callbackFree);
}

void queue_push_back(Queue *thiz, void *element)
{
    QueueNode *node = queue_node_create(element);
    if (node)
    {
        if (queue_is_empty(thiz))
        {
            thiz->head = thiz->tail = node;
        }
        else
        {
            thiz->tail->next = node;
            thiz->tail = node;
        }
    }
}

bool queue_is_empty(Queue *thiz)
{
    return thiz->head == NULL;
}

void queue_destory(Queue *thiz)
{
    assert(queue_is_empty(thiz));

    free(thiz);
}
