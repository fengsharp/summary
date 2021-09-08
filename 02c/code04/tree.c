#include "tree.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct _BTreeNode
{
    void *data;
    struct _BTreeNode *left;
    struct _BTreeNode *right;
} BTreeNode;

static BTreeNode *btree_node_create(void *element)
{
    BTreeNode *node = malloc(sizeof(BTreeNode));
    if (node)
    {
        node->data = element;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

static void btree_node_destroy(BTreeNode *thiz, FuncFreeElement callbackFree)
{
    if (callbackFree)
    {
        callbackFree(thiz->data);
    }

    free(thiz);
}

struct _BTree
{
    BTreeNode *root;
};

BTree *btree_create()
{
    BTree *tree = malloc(sizeof(BTree));
    if (tree)
    {
        tree->root = NULL;
    }
    return tree;
}

static void btree_insert_node(BTreeNode *node, void *element, FuncCmpElement callbackCmp)
{
    if (node == NULL)
    {
        return;
    }

    if (callbackCmp(element, node->data) < 0)
    {
        if (node->left == NULL)
        {
            node->left = btree_node_create(element);
        }
        else
        {
            btree_insert_node(node->left, element, callbackCmp);
        }
    }
    else
    {
        if (node->right == NULL)
        {
            node->right = btree_node_create(element);
        }
        else
        {
            btree_insert_node(node->right, element, callbackCmp);
        }
    }
}

void btree_push(BTree *thiz, void *element, FuncCmpElement callbackCmp)
{
    if (thiz->root == NULL)
    {
        thiz->root = btree_node_create(element);
    }
    else
    {
        btree_insert_node(thiz->root, element, callbackCmp);
    }
}

static void btree_draw_node(BTreeNode *node, FuncPrintElement callbackPrint, int level)
{
    if (node == NULL)
    {
        return;
    }

    btree_draw_node(node->right, callbackPrint, level + 1);
    
    for (int i = 0; i < level; ++i)
    {
        printf("-");
    }
    callbackPrint(node->data);
    printf("\n");

    btree_draw_node(node->left, callbackPrint, level + 1);
}

void btree_draw(BTree *thiz, FuncPrintElement callbackPrint)
{
    if (thiz->root)
    {
        puts("===================================================");
        btree_draw_node(thiz->root, callbackPrint, 0);
        puts("===================================================");
    }
}

static void btree_destroy_all(BTreeNode *node, FuncFreeElement callbackFree)
{
    if (node == NULL)
    {
        return;
    }

    btree_destroy_all(node->left, callbackFree);
    btree_destroy_all(node->right, callbackFree);
    btree_node_destroy(node, callbackFree);
}

void btree_destory(BTree *thiz, FuncFreeElement callbackFree)
{
    btree_destroy_all(thiz->root, callbackFree);
}
