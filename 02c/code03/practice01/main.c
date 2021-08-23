#include <stdio.h>
#include <stdlib.h>

#include "dlist.h"

void dlist_int_print(void *ctx, void *data)
{
    int *pNum = (int *)(data);
    printf("%d ", *pNum);
}

void dlist_int_destroy(void *ctx, void *data)
{
    int *pNum = (int *)(data);
    free(pNum);
}

void dlist_int_sum(void *ctx, void *data)
{
    int *pTotal = (int *)(ctx);
    int *pNum = (int *)(data);
    *pTotal += *pNum;
}

void dlist_int_max(void *ctx, void *data)
{
    int *pMax = (int*)(ctx);
    int *pNum = (int*)(data);
    if (*pMax < *pNum)
    {
        *pMax = *pNum;
    }
}

int main()
{
    puts("--- start ---");

    // 10 num
    DList *dlist = dlist_create();
    if (dlist == NULL)
    {
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 10; ++i)
    {
        int *pNum = malloc(sizeof(int));
        *pNum = i;
        dlist_push_back(dlist, pNum);
    }

    // print num
    dlist_foreach(dlist, dlist_int_print, NULL);
    puts("");

    // sum
    int sum = 0;
    dlist_foreach(dlist, dlist_int_sum, &sum);
    printf("sum: %d\n", sum);

    // max
    int max = 0;
    dlist_foreach(dlist, dlist_int_max, &max);
    printf("max: %d\n", max);
    
    // release
    dlist_foreach(dlist, dlist_int_destroy, NULL);
    dlist_destroy(dlist);

    puts("--- end ---");

    return 0;
}