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

static int btree_num_node(BTreeNode *node)
{
    if (node == NULL)
    {
        return 0;
    }
    else
    {
        return btree_num_node(node->left) + 1 + btree_num_node(node->right);
    }
}

static BTreeNode* btree_find_left_min_node(BTreeNode *node)
{
    if (node->left == NULL)
    {
        return node;
    }

    return btree_find_left_min_node(node->left);
}

static void btree_rote_left_node(BTreeNode **root)
{
    BTreeNode *pCursor = *root;
    *root = pCursor->right;
    pCursor->right = NULL;

    BTreeNode *pLeftMinNode = btree_find_left_min_node((*root));
    pLeftMinNode->left = pCursor;
}

static BTreeNode* btree_find_right_max_node(BTreeNode *node)
{
    if (node->right == NULL)
    {
        return node;
    }

    return btree_find_right_max_node(node->right);
}

static void btree_rote_right_node(BTreeNode **root)
{
    BTreeNode *pCursor = *root;
    *root = pCursor->left;
    pCursor->left = NULL;

    BTreeNode *pRightMaxNode = btree_find_right_max_node((*root));
    pRightMaxNode->right = pCursor;
}

void btree_balance_node(BTreeNode **node)
{
    if ((*node) == NULL)
    {
        return;
    }

    while (1)
    {
        int factor = btree_num_node((*node)->left) - btree_num_node((*node)->right);
        if (factor < -1)
        {
            // rote left
            btree_rote_left_node(node);
        }
        else if (factor > 1)
        {
            // rote right
            btree_rote_right_node(node);
        }
        else
        {
            break;
        }
    }

    btree_balance_node(&(*node)->left);
    btree_balance_node(&(*node)->right);
}

void btree_balance(BTree *thiz)
{
    btree_balance_node(&thiz->root);
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

    btree_balance_node(&thiz->root);
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
