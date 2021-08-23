#include "dlist.h"

#include <stdlib.h>

typedef struct _DListNode
{
    struct _DListNode *prev;
    struct _DListNode *next;
    void *data;
} DListNode;

static DListNode *dlist_node_create(void *data)
{
    DListNode *pRet = malloc(sizeof(DListNode));
    if (pRet)
    {
        pRet->prev = NULL;
        pRet->next = NULL;
        pRet->data = data;
    }
    return pRet;
}

static void dlist_node_destroy(DListNode *thiz)
{
    free(thiz);
}

struct _DList
{
    DListNode *first;
    DListNode *tail;
    size_t length;
};

DList *dlist_create(void)
{
    DList *pRet = malloc(sizeof(DList));
    if (pRet)
    {
        pRet->first = NULL;
        pRet->tail = NULL;
        pRet->length = 0;
    }
    return pRet;
}

DListRet dlist_push_back(DList *thiz, void *data)
{
    DListNode *pNode = dlist_node_create(data);
    if (pNode == NULL)
    {
        return DLIST_RET_OOM;
    }

    if (thiz->tail != NULL)
    {
        thiz->tail->next = pNode;
        pNode->prev = thiz->tail;
        thiz->tail = pNode;
    }
    else
    {
        thiz->first = pNode;
        thiz->tail = pNode;
    }
    ++thiz->length;

    return DLIST_RET_OK;
}

DListRet dlist_push_front(DList *thiz, void *data)
{
    DListNode *pNode = dlist_node_create(data);
    if (pNode == NULL)
    {
        return DLIST_RET_OOM;
    }

    if (thiz->first != NULL)
    {
        pNode->next = thiz->first;
        thiz->first->prev = pNode;
        thiz->first = pNode;
    }
    else
    {
        thiz->first = pNode;
        thiz->tail = pNode;
    }
    ++thiz->length;

    return DLIST_RET_OK;
}

DListRet dlist_pop_back(DList *thiz)
{
    if (dlist_is_empty(thiz))
    {
        return DLIST_RET_FAIL;
    }

    DListNode *pCursor = thiz->tail;
    thiz->tail = pCursor->prev;
    dlist_node_destroy(pCursor);

    if (thiz->tail)
    {
        thiz->tail->next = NULL;
    }
    else
    {
        thiz->first = NULL;
    }

    --thiz->length;
    return DLIST_RET_OK;
}

DListRet dlist_pop_front(DList *thiz)
{
    if (dlist_is_empty(thiz))
    {
        return DLIST_RET_FAIL;
    }

    DListNode *pCursor = thiz->first;
    thiz->first = pCursor->next;
    dlist_node_destroy(pCursor);

    if (thiz->first)
    {
        thiz->first->prev = NULL;
    }
    else
    {
        thiz->tail = NULL;
    }

    --thiz->length;
    return DLIST_RET_OK;
}

void *dlist_get_back(DList *thiz)
{
    return thiz->tail ? thiz->tail->data : NULL;
}

void *dlist_get_front(DList *thiz)
{
    return thiz->first ? thiz->first->data : NULL;
}

size_t dlist_get_length(DList *thiz)
{
    return thiz->length;
}

bool dlist_is_empty(DList *thiz)
{
    return thiz->length == 0;
}

void dlist_foreach(DList *thiz, callback_foreach funcForeach)
{
    DListNode *pCursor = thiz->first;
    while (pCursor)
    {
        funcForeach(pCursor->data);

        pCursor = pCursor->next;
    }
}

void dlist_destroy(DList *thiz)
{
    DListNode *pCursor = thiz->first;
    while (pCursor)
    {
        pCursor = pCursor->next;
        dlist_node_destroy(thiz->first);
        thiz->first = pCursor;
    }
    free(thiz);
}