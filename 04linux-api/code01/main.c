#include <stdio.h>
#include <stdlib.h>

#include "sqlist.h"

void func_pint(void *data)
{
    int *val = (int *)(data);
    printf("%d ", *val);
}

void func_free(void *data)
{
    free(data);
}

int main()
{
    SqlList *list = sqlist_create();

    for (int i = 0; i < 10; ++i)
    {
        int *val = malloc(sizeof(int));
        *val = i;
        sqlist_pushback(list, val);
    }

    sqlist_foreach(list, func_pint);
    puts("");

    sqlist_foreach(list, func_free);

    sqlist_destory(list);

    return 0;
}