#include "darray.h"

#include <stdlib.h>

struct _DArray
{
    void **data;
    size_t size;
    size_t allocSize;
};

DArray *darray_create(void)
{
    DArray *thiz = malloc(sizeof(DArray));

    if (thiz != NULL)
    {
        thiz->data = NULL;
        thiz->size = 0;
        thiz->allocSize = 0;
    }

    return thiz;
}

#define MIN_PRE_ALLOCATE_NR 10
static Ret darray_expand(DArray *thiz, size_t need)
{
    return_val_if_fail(thiz != NULL, RET_INVALIDE_PARAMS);

    if ((thiz->size + need) > thiz->allocSize)
    {
        size_t alloc_size = thiz->allocSize + (thiz->allocSize >> 1) + MIN_PRE_ALLOCATE_NR;

        void **data = (void **)realloc(thiz->data, sizeof(void *) * alloc_size);
        if (data != NULL)
        {
            thiz->data = data;
            thiz->allocSize = alloc_size;
        }
    }

    return ((thiz->size + need) <= thiz->allocSize) ? RET_OK : RET_FAIL;
}

static Ret darray_shrink(DArray *thiz)
{
    return_val_if_fail(thiz != NULL, RET_INVALIDE_PARAMS);

    if ((thiz->size < (thiz->allocSize >> 1)) && (thiz->allocSize > MIN_PRE_ALLOCATE_NR))
    {
        size_t alloc_size = thiz->size + (thiz->size >> 1);

        void **data = (void **)realloc(thiz->data, sizeof(void *) * alloc_size);
        if (data != NULL)
        {
            thiz->data = data;
            thiz->allocSize = alloc_size;
        }
    }

    return RET_OK;
}

Ret darray_insert(DArray *thiz, size_t index, void *data)
{
    Ret ret = RET_OOM;
    size_t cursor = index;
    return_val_if_fail(thiz != NULL, RET_INVALIDE_PARAMS);

    cursor = cursor < thiz->size ? cursor : thiz->size;

    if (darray_expand(thiz, 1) == RET_OK)
    {
        size_t i = 0;
        for (i = thiz->size; i > cursor; i--)
        {
            thiz->data[i] = thiz->data[i - 1];
        }

        thiz->data[cursor] = data;
        ++thiz->size;

        ret = RET_OK;
    }

    return ret;
}

Ret darray_push_front(DArray *thiz, void *data)
{
    return darray_insert(thiz, 0, data);
}

Ret darray_push_back(DArray *thiz, void *data)
{
    return darray_insert(thiz, -1, data);
}

Ret darray_delete(DArray *thiz, size_t index)
{
    return_val_if_fail(thiz != NULL && thiz->size > index, RET_INVALIDE_PARAMS);

    for (int i = index; (i + 1) < thiz->size; i++)
    {
        thiz->data[i] = thiz->data[i + 1];
    }
    thiz->size--;

    darray_shrink(thiz);

    return RET_OK;
}

Ret darray_pop_front(DArray *thiz)
{
    return darray_delete(thiz, 0);
}

Ret darray_pop_back(DArray *thiz)
{
    return darray_delete(thiz, thiz->size - 1);
}

void *darray_get(DArray *thiz, size_t index)
{
    return_val_if_fail(thiz != NULL && index < thiz->size, NULL); 

	return thiz->data[index];
}

void *darray_get_back(DArray *thiz)
{
    return darray_get(thiz, thiz->size - 1);
}

void *darray_get_front(DArray *thiz)
{
    return darray_get(thiz, 0);
}

size_t darray_get_length(DArray *thiz)
{
    return thiz->size;
}

bool darray_is_empty(DArray *thiz)
{
    return thiz->size == 0;
}

void darray_foreach(DArray *thiz, callback_foreach funcForeach, void *funcCtx)
{
    for (int i = 0; i < thiz->size; ++i)
    {
        funcForeach(funcCtx, thiz->data[i]);
    }
}

void darray_destroy(DArray *thiz)
{
    free(thiz->data);
    free(thiz);
}
