#include <stdio.h>
#include <stdlib.h>

struct ListNode
{
    int val;
    struct ListNode *next;
};

struct ListNode *createList(int *arr, int arrSize);
void destroyList(struct ListNode *thiz);
void printList(struct ListNode *thiz);

int calListSize(struct ListNode *l1)
{
    int size = 0;
    while (l1 != NULL)
    {
        ++size;
        l1 = l1->next;
    }
    return size;
}

struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2)
{
    int l1Size = calListSize(l1);
    int l2Size = calListSize(l2);

    if (l1Size > l2Size)
    {
        struct ListNode *pTmp = l1;
        l1 = l2;
        l2 = pTmp;
    }

    struct ListNode *pCursor1 = l1;
    struct ListNode *pCursor2 = l2;
    int carryValue = 0;
    while (pCursor1 != NULL)
    {
        int sum = pCursor1->val + pCursor2->val + carryValue;
        carryValue = sum / 10;
        pCursor2->val = sum % 10;
        pCursor1 = pCursor1->next;
        pCursor2 = pCursor2->next;
    }

    if (carryValue > 0 && pCursor2 != NULL)
    {
        while (pCursor2 != NULL && carryValue > 0)
        {
            int sum = pCursor2->val + carryValue;
            carryValue = sum / 10;
            pCursor2->val = sum % 10;
            pCursor2 = pCursor2->next;
        }
    }
    if (carryValue > 0 && pCursor2 == NULL)
    {
        pCursor2 = l2;
        while (pCursor2->next != NULL)
        {
            pCursor2 = pCursor2->next;
        }
        pCursor2->next = malloc(sizeof(struct ListNode));
        pCursor2->next->next = NULL;
        pCursor2->next->val = carryValue;
    }
    return l2;
}

void test1();
void test2();
void test3();
void test4();

int main()
{
    test1();
    test2();
    test3();
    test4();

    return 0;
}

struct ListNode *createList(int *arr, int arrSize)
{
    struct ListNode *pHead = NULL;
    struct ListNode *pTail = NULL;
    for (int i = 0; i < arrSize; ++i)
    {
        struct ListNode *pCurr = malloc(sizeof(struct ListNode));
        pCurr->val = *arr;
        pCurr->next = NULL;
        ++arr;

        if (pTail == NULL)
        {
            pHead = pCurr;
            pTail = pCurr;
        }
        else
        {
            pTail->next = pCurr;
            pTail = pCurr;
        }
    }

    return pHead;
}

void destroyList(struct ListNode *thiz)
{
    struct ListNode *pCursor = thiz;
    while (pCursor != NULL)
    {
        struct ListNode *pCur = pCursor;
        pCursor = pCur->next;
        free(pCur);
    }
}

void printList(struct ListNode *thiz)
{
    struct ListNode *pCursor = thiz;
    while (pCursor != NULL)
    {
        struct ListNode *pCur = pCursor;
        pCursor = pCur->next;
        printf("%d ", pCur->val);
    }
    puts("");
}

void test1()
{
    int arr1[] = {2, 4, 3};
    struct ListNode *pList1 = createList(arr1, sizeof(arr1) / sizeof(int));

    int arr2[] = {5, 6, 4};
    struct ListNode *pList2 = createList(arr2, sizeof(arr2) / sizeof(int));

    struct ListNode *pResult = addTwoNumbers(pList1, pList2);
    printList(pResult);

    destroyList(pList1);
    destroyList(pList2);
}

void test2()
{
    int arr1[] = {0};
    struct ListNode *pList1 = createList(arr1, sizeof(arr1) / sizeof(int));

    int arr2[] = {0};
    struct ListNode *pList2 = createList(arr2, sizeof(arr2) / sizeof(int));

    struct ListNode *pResult = addTwoNumbers(pList1, pList2);
    printList(pResult);

    destroyList(pList1);
    destroyList(pList2);
}

void test3()
{
    int arr1[] = {9, 9, 9, 9, 9, 9, 9};
    struct ListNode *pList1 = createList(arr1, sizeof(arr1) / sizeof(int));

    int arr2[] = {9, 9, 9, 9};
    struct ListNode *pList2 = createList(arr2, sizeof(arr2) / sizeof(int));

    struct ListNode *pResult = addTwoNumbers(pList1, pList2);
    printList(pResult);

    destroyList(pList1);
    destroyList(pList2);
}

void test4()
{
    int arr1[] = {2, 4, 9};
    struct ListNode *pList1 = createList(arr1, sizeof(arr1) / sizeof(int));

    int arr2[] = {5, 6, 4, 9};
    struct ListNode *pList2 = createList(arr2, sizeof(arr2) / sizeof(int));

    struct ListNode *pResult = addTwoNumbers(pList1, pList2);
    printList(pResult);

    destroyList(pList1);
    destroyList(pList2);
}
