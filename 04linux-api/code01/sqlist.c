#include "sqlist.h"

#include <stdlib.h>

#define MINSIZE 10

struct _SqlList
{
    void **data;
    size_t capacity;
    size_t size;
};

SqlList *sqlist_create()
{
    SqlList *ret = malloc(sizeof(SqlList));
    if (ret)
    {
        ret->data = NULL;
        ret->capacity = 0;
        ret->size = 0;
    }
    return ret;
}

Ret sqlist_destory(SqlList *thiz)
{
    if (thiz->data)
    {
        free(thiz->data);
    }
    return RET_OK;
}

Ret sqlist_insert(SqlList *thiz, size_t index, void *ele)
{
    if (!thiz->data)
    {
        thiz->data = malloc(sizeof(void*) * MINSIZE);
        thiz->capacity = MINSIZE;
    }

    if (thiz->size == thiz->capacity)
    {
        thiz->capacity = thiz->capacity + thiz->capacity > 1;
        thiz->data = realloc(thiz->data, thiz->capacity);
    }

    if (index > thiz->size)
    {
        index = thiz->size;
    }

    for (size_t i = thiz->size; i > index; --i)
    {
        thiz->data[i] = thiz->data[i-1];
    }
    thiz->data[index] = ele;

    ++thiz->size;

    return RET_OK;
}

Ret sqlist_pushback(SqlList *thiz, void *data)
{
    return sqlist_insert(thiz, thiz->size, data);
}

Ret sqlist_delete(SqlList *thiz, size_t index)
{
    if (index >= thiz->size)
    {
        return RET_PARAM;
    }

    for (size_t i = index; i < thiz->size - 1; ++i)
    {
        thiz->data[i] = thiz->data[i+1];
    }

    --thiz->size;

    return RET_OK;
}

Ret sqlist_popback(SqlList *thiz)
{
    return sqlist_delete(thiz, thiz->size-1);
}

Ret sqlist_foreach(SqlList *thiz, func_foreach foreach)
{
    if (sqlist_isempty(thiz))
    {
        return RET_ERROR;
    }

    for (size_t i = 0; i < thiz->size; ++i)
    {
        foreach(thiz->data[i]);
    }
    
    return RET_OK;
}

bool sqlist_isempty(SqlList *thiz)
{
    return thiz->size == 0;
}

void *sqlist_get(SqlList *thiz, size_t index)
{
    if (thiz->size <= index)
    {
        return NULL;
    }

    return thiz->data[index];
}

size_t sqlist_size(SqlList *thiz)
{
    return thiz->size;
}
