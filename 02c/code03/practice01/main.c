#include <stdio.h>
#include <stdlib.h>

#include "dlist.h"

void dlist_int_print(void *data)
{
    int *pNum = (int *)(data);
    printf("%d ", *pNum);
}

void dlist_int_destroy(void *data)
{
    int *pNum = (int *)(data);
    free(pNum);
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
    dlist_foreach(dlist, dlist_int_print);

    // release
    dlist_foreach(dlist, dlist_int_destroy);

    dlist_destroy(dlist);

    puts("--- end ---");

    return 0;
}