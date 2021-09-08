#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"
#include "tree.h"

void test_queue();
void test_tree();

int main()
{
    // test_queue();
    test_tree();

    return 0;
}

static void int_free(void *element)
{
    free(element);
}

void test_queue()
{
    Queue *queue = queue_create();
    for (int i = 0; i < 10; ++i)
    {
        int *ele = malloc(sizeof(int));
        *ele = i;
        queue_push_back(queue, ele);
    }

    void *element = NULL;
    while ((element = queue_get_frot(queue)) != NULL)
    {
        int *val = (int *)(element);
        printf("%d ", *val);

        queue_pop_frot(queue, int_free);
    }
    puts("");

    queue_destory(queue);
}

static int int_cmp(void *src, void *dest)
{
    int *intSrc = (void *)src;
    int *intDest = (void *)dest;

    return *intSrc - *intDest;
}

static void int_print(void *element)
{
    printf("%d ", *(int *)(element));
}

void test_tree()
{
    int arr[] = {1, 2, 3, 7, 6, 5, 4, 9, 8};

    BTree *tree = btree_create();

    for (int i = 0; i < sizeof(arr) / sizeof(int); ++i)
    {
        int *ele = malloc(sizeof(int));
        *ele = arr[i];
        btree_push(tree, ele, int_cmp);
    }

    btree_draw(tree, int_print);

    btree_balance(tree);
    btree_draw(tree, int_print);

    btree_destory(tree, int_free);
}