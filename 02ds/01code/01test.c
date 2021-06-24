#include <stdio.h>
#include <stdlib.h>

#define ARR_LEN 101

void initArr(int *pArr, int arrLen);
int calArr(int *pArr, int arrLen);

int main()
{
    int arr[ARR_LEN];
    initArr(arr, ARR_LEN);
    int ret = calArr(arr, ARR_LEN);

    printf("result: %d\n", ret);

    return 0;
}

void initArr(int *pArr, int arrLen)
{
    for (int i = 0; i < arrLen; ++i)
    {
        pArr[i] = i;
    }
}

int calArr(int *pArr, int arrLen)
{
    if (arrLen == 1)
    {
        return pArr[0];
    }
    else
    {
        return pArr[arrLen - 1] + calArr(pArr, arrLen - 1);
    }
}