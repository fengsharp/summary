#ifndef TREE_H_
#define TREE_H_

#include "common.h"

struct _BTree;
typedef struct _BTree BTree;

BTree* btree_create();

void btree_push(BTree *thiz, void *element, FuncCmpElement callbackCmp);
void btree_draw(BTree *thiz, FuncPrintElement callbackPrint);
void btree_balance(BTree *thiz);

void btree_destory(BTree *thiz, FuncFreeElement callbackFree);

#endif