#ifndef DLIST_H_
#define DLIST_H_

#include <stdbool.h>
#include <stddef.h>

typedef enum _DListRet
{
    DLIST_RET_OK,
    DLIST_RET_FAIL,
    DLIST_RET_PARAMS,
    DLIST_RET_OOM,
} DListRet;

struct _DList;
typedef struct _DList DList;

typedef void (*callback_foreach)(void *ctx, void *data);

DList *dlist_create(void);

DListRet dlist_push_back(DList *thiz, void *data);
DListRet dlist_push_front(DList *thiz, void *data);
DListRet dlist_pop_back(DList *thiz);
DListRet dlist_pop_front(DList *thiz);
void *dlist_get_back(DList *thiz);
void *dlist_get_front(DList *thiz);
size_t dlist_get_length(DList *thiz);
bool dlist_is_empty(DList *thiz);
void dlist_foreach(DList *thiz, callback_foreach funcForeach, void *funcCtx);

void dlist_destroy(DList *thiz);

#endif