#ifndef SQLIST_H_
#define SQLIST_H_

#include <stdbool.h>

#include "common.h"

struct _SqlList;
typedef struct _SqlList SqlList;

typedef void (*func_foreach)(void *ele);

SqlList *sqlist_create();
Ret sqlist_destory(SqlList *thiz);

Ret sqlist_insert(SqlList *thiz, size_t index, void *ele);
Ret sqlist_pushback(SqlList *thiz, void *ele);
Ret sqlist_delete(SqlList *thiz, size_t index);
Ret sqlist_popback(SqlList *thiz);
Ret sqlist_foreach(SqlList *thiz, func_foreach foreach);
bool sqlist_isempty(SqlList *thiz);
void *sqlist_get(SqlList *thiz, size_t index);
size_t sqlist_size(SqlList *thiz);

#endif