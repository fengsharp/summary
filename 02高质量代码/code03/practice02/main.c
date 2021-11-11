#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "typedef.h"
#include "darray.h"

void darray_int_print(void *ctx, void *data)
{
    int *pNum = (int *)(data);
    printf("%d ", *pNum);
}

void darray_int_destroy(void *ctx, void *data)
{
    int *pNum = (int *)(data);
    free(pNum);
}

void darray_int_sum(void *ctx, void *data)
{
    int *pTotal = (int *)(ctx);
    int *pNum = (int *)(data);
    *pTotal += *pNum;
}

void darray_int_max(void *ctx, void *data)
{
    int *pMax = (int *)(ctx);
    int *pNum = (int *)(data);
    if (*pMax < *pNum)
    {
        *pMax = *pNum;
    }
}

void darray_int_test()
{
    // 10 num
    DArray *darray = darray_create();
    if (darray == NULL)
    {
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 10; ++i)
    {
        int *pNum = malloc(sizeof(int));
        *pNum = i;
        darray_push_back(darray, pNum);
    }

    // print num
    darray_foreach(darray, darray_int_print, NULL);
    puts("");

    // sum
    int sum = 0;
    darray_foreach(darray, darray_int_sum, &sum);
    printf("sum: %d\n", sum);

    // max
    int max = 0;
    darray_foreach(darray, darray_int_max, &max);
    printf("max: %d\n", max);

    // release
    darray_foreach(darray, darray_int_destroy, NULL);
    darray_destroy(darray);
}

void darray_str_print(void *ctx, void *data)
{
    char *str = (char *)(data);
    printf("%s ", str);
}

void darray_str_destry(void *ctx, void *data)
{
    free(data);
}

void darray_str_toupper(void *ctx, void *data)
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

void darray_str_test()
{
    DArray *darray = darray_create();

    darray_push_back(darray, strdup("hello"));
    darray_push_back(darray, strdup("world"));

    darray_foreach(darray, darray_str_print, NULL);
    puts("");

    darray_foreach(darray, darray_str_toupper, NULL);
    darray_foreach(darray, darray_str_print, NULL);
    puts("");

    // release
    darray_foreach(darray, darray_str_destry, NULL);
    darray_destroy(darray);
}

int main()
{
    puts("--- start ---");
    darray_int_test();
    // darray_str_test();
    puts("--- end ---");

    return 0;
}