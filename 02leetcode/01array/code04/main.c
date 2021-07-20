#include <stdio.h>
#include <stdlib.h>

double findMedianSortedArrays(int *nums1, int nums1Size, int *nums2, int nums2Size)
{
    int totalNum = (nums1Size + nums2Size);
    int loopCnt = (totalNum + 1) / 2;
    const int MAX_VALUE = 1000 * 1000;

    const int *pCursor1 = nums1Size > 0 ? nums1 : &MAX_VALUE;
    const int *pCursor2 = nums2Size > 0 ? nums2 : &MAX_VALUE;
    for (int i = 1; i < loopCnt; ++i)
    {
        if (*pCursor1 < *pCursor2)
        {
            pCursor1 = (pCursor1 == (nums1 + nums1Size - 1)) ? &MAX_VALUE : (pCursor1 + 1);
        }
        else
        {
            pCursor2 = (pCursor2 == (nums2 + nums2Size - 1)) ? &MAX_VALUE : (pCursor2 + 1);
        }
    }

    double mindValue = 0;
    if (totalNum % 2 == 0)
    {
        for (int i = 0; i < 2; ++i)
        {
            if (*pCursor1 < *pCursor2)
            {
                mindValue += *pCursor1;
                pCursor1 = (pCursor1 == (nums1 + nums1Size - 1)) ? &MAX_VALUE : (pCursor1 + 1);
            }
            else
            {
                mindValue += *pCursor2;
                pCursor2 = (pCursor2 == (nums2 + nums2Size - 1)) ? &MAX_VALUE : (pCursor2 + 1);
            }
        }
        mindValue /= 2.0;
    }
    else
    {
        mindValue = (*pCursor1 < *pCursor2) ? *pCursor1 : *pCursor2;
    }

    return mindValue;
}

void test1();
void test2();
void test3();
void test4();
void test5();

int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();

    return 0;
}

void test1()
{
    int nums1[] = {1, 3};
    int nums2[] = {2};

    double ret = findMedianSortedArrays(nums1, sizeof(nums1) / sizeof(int), nums2, sizeof(nums2) / sizeof(int));
    // 2.00000
    printf("%f\n", ret);
}

void test2()
{
    int nums1[] = {1, 2};
    int nums2[] = {3, 4};

    double ret = findMedianSortedArrays(nums1, sizeof(nums1) / sizeof(int), nums2, sizeof(nums2) / sizeof(int));
    // 2.50000
    printf("%f\n", ret);
}

void test3()
{
    int nums1[] = {0, 0};
    int nums2[] = {0, 0};

    double ret = findMedianSortedArrays(nums1, sizeof(nums1) / sizeof(int), nums2, sizeof(nums2) / sizeof(int));
    // 0.0
    printf("%f\n", ret);
}

void test4()
{
    int nums1[] = {};
    int nums2[] = {1};

    double ret = findMedianSortedArrays(nums1, sizeof(nums1) / sizeof(int), nums2, sizeof(nums2) / sizeof(int));
    // 1.00000
    printf("%f\n", ret);
}

void test5()
{
    int nums1[] = {2};
    int nums2[] = {};

    double ret = findMedianSortedArrays(nums1, sizeof(nums1) / sizeof(int), nums2, sizeof(nums2) / sizeof(int));
    // 2.00000
    printf("%f\n", ret);
}
