#include <stdio.h>
#include <stdlib.h>

#define ARR_LEN 10

void initArr(int *pArr, int arrLen);
void printArr(int *pArr, int arrLen);
void change(int *pArr, int lo, int hi);

int main()
{
    int arr[ARR_LEN];
    initArr(arr, ARR_LEN);
    printArr(arr, ARR_LEN);

    change(arr, 0, ARR_LEN - 1);
    printArr(arr, ARR_LEN);

    return 0;
}

void initArr(int *pArr, int arrLen)
{
    for (int i = 0; i < arrLen; ++i)
    {
        pArr[i] = i;
    }
}

void printArr(int *pArr, int arrLen)
{
    for (int i = 0; i < arrLen; ++i)
    {
        printf("%d ", pArr[i]);
    }
    printf("\n");
}

void change(int *pArr, int lo, int hi)
{
    if (lo >= hi)
    {
        return;
    }
    else
    {
        int tmp = pArr[lo];
        pArr[lo] = pArr[hi];
        pArr[hi] = tmp;
        change(pArr, lo + 1, hi - 1);
    }
}