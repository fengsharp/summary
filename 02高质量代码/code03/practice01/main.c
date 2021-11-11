#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
    int *pMax = (int *)(ctx);
    int *pNum = (int *)(data);
    if (*pMax < *pNum)
    {
        *pMax = *pNum;
    }
}

void dlist_int_test()
{
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
}

void dlist_str_print(void *ctx, void *data)
{
    char *str = (char *)(data);
    printf("%s ", str);
}

void dlist_str_destry(void *ctx, void *data)
{
    free(data);
}

void dlist_str_toupper(void *ctx, void *data)
{
    char *str = (char *)(data);
    char *pCursor = str;
    while (*pCursor != '\0')
    {
        if (islower(*pCursor))
        {
            *pCursor = toupper(*pCursor);
        }
        ++pCursor;
    }
}

void dlist_str_test()
{
    DList *dlist = dlist_create();

    dlist_push_back(dlist, strdup("hello"));
    dlist_push_back(dlist, strdup("world"));

    dlist_foreach(dlist, dlist_str_print, NULL);
    puts("");

    dlist_foreach(dlist, dlist_str_toupper, NULL);
    dlist_foreach(dlist, dlist_str_print, NULL);
    puts("");

    // release
    dlist_foreach(dlist, dlist_str_destry, NULL);
    dlist_destroy(dlist);
}

int main()
{
    puts("--- start ---");
    dlist_str_test();
    puts("--- end ---");

    return 0;
}