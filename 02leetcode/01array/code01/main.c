#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
    for (int i = 0; i < numsSize - 1; i++)
    {
        for (int j = i + 1; j < numsSize; j++)
        {
            if ((nums[i] + nums[j]) == target)
            {
                *returnSize = 2;

                int *pResult = malloc(sizeof(int) * (*returnSize));
                pResult[0] = i;
                pResult[1] = j;
                
                return pResult;
            }
        }
    }

    *returnSize = 0;
    return NULL;
}

void printResult(int *results, int resultsSize)
{
    int *pCursor = results;
    for (int i = 0; i < resultsSize; ++i)
    {
        printf("%d ", *pCursor);
        ++pCursor;
    }
    puts("");
}

int main()
{
    int returnSize = 0;
    int *results = NULL;

    int nums1[] = {2, 7, 11, 15};
    int target1 = 9;
    results = twoSum(nums1, sizeof(nums1) / sizeof(int), target1, &returnSize);
    printResult(results, returnSize);
    free(results);

    int nums2[] = {3, 2, 4};
    int target2 = 6;
    results = twoSum(nums2, sizeof(nums2) / sizeof(int), target2, &returnSize);
    printResult(results, returnSize);
    free(results);

    int nums3[] = {3, 3};
    int target3 = 6;
    results = twoSum(nums3, sizeof(nums3) / sizeof(int), target3, &returnSize);
    printResult(results, returnSize);
    free(results);

    return 0;
}