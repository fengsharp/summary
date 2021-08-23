#ifndef DARRAY_H_
#define DARRAY_H_

#include "typedef.h"

DECLS_BEGIN

#include <stddef.h>
#include <stdbool.h>

struct _DArray;
typedef struct _DArray DArray;

DArray *darray_create(void);

Ret darray_insert(DArray *thiz, size_t index, void *data);
Ret darray_push_front(DArray *thiz, void *data);
Ret darray_push_back(DArray *thiz, void *data);

Ret darray_delete(DArray *thiz, size_t index);
Ret darray_pop_front(DArray *thiz);
Ret darray_pop_back(DArray *thiz);

void *darray_get(DArray *thiz, size_t index);
void *darray_get_back(DArray *thiz);
void *darray_get_front(DArray *thiz);

size_t darray_get_length(DArray *thiz);
bool darray_is_empty(DArray *thiz);
void darray_foreach(DArray *thiz, callback_foreach funcForeach, void *funcCtx);

void darray_destroy(DArray *thiz);

DECLS_END

#endif