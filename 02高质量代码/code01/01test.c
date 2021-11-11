#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FileLine.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

const int MAX_RANGE = 10;

void done(int lineNum, const char *content, const char *errMsg);

int main()
{
    FileLine *pFileLine = openFile("./01data.txt");
    if (pFileLine == NULL)
    {
        exit(EXIT_FAILURE);
    }

    foreachLine(pFileLine, done);

    closeFile(pFileLine);

    printf("=== over! ===\n");

    return EXIT_SUCCESS;
}

typedef struct _Range
{
    int min;
    int max;
} Range;

Range arrRange[MAX_RANGE];
int rangeCnt = 0;

void done(int lineNum, const char *content, const char *errMsg)
{
    if (errMsg != NULL)
    {
        printf("%s\n", errMsg);
        exit(EXIT_FAILURE);
    }

    if (lineNum == 0)
    {
        // 4 9 12 20 -1
        char *pStr = strdup(content);

        const char *delimiters = " ";
        char *pToken = strtok(pStr, delimiters);
        while (pToken != NULL)
        {
            Range *pCurRange = &arrRange[rangeCnt];

            pCurRange->min = atoi(pToken);
            if (pCurRange->min < 0)
            {
                break;
            }

            pToken = strtok(NULL, delimiters);
            pCurRange->max = atoi(pToken);

            ++rangeCnt;
            pToken = strtok(NULL, delimiters);
        }
        free(pStr);
    }
    else
    {
        if (rangeCnt == 0)
        {
            return;
        }

        int strLen = (int)strlen(content);
        printf("Original input: %s\n", content);
        printf("Rearranged line: ");
        for (int i = 0; i < rangeCnt; ++i)
        {
            Range *pCursor = &arrRange[i];
            if (pCursor->min >= strLen)
            {
                break;
            }

            int len = MIN(strLen - 1, pCursor->max) - pCursor->min + 1;
            char *pSubStr = strndup(content + pCursor->min, len);
            printf("%s", pSubStr);
            free(pSubStr);
        }
        printf("\n");
    }
}
