#include "FileLine.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int ARR_LINE_LEN_MAX = 512;

struct _FileLine
{
    FILE *pFile;
};

FileLine *openFile(const char *fileName)
{
    FILE *pFile = fopen("./01data.txt", "r");
    if (pFile == NULL)
    {
        perror("open file");
        return NULL;
    }
    else
    {
        FileLine *pRet = (FileLine *)malloc(sizeof(FileLine));
        pRet->pFile = pFile;
        return pRet;
    }
}

void closeFile(FileLine *thiz)
{
    if (thiz->pFile)
    {
        fclose(thiz->pFile);
    }
    free(thiz);
}

void foreachLine(FileLine *thiz, void (*callbak)(int lineNum, const char *content, const char *errMsg))
{
    char arrLine[ARR_LINE_LEN_MAX] = {0};
    int lineNum = 0;
    while (1)
    {
        char *pRet = fgets(arrLine, ARR_LINE_LEN_MAX, thiz->pFile);
        if (pRet == NULL)
        {
            break;
        }

        size_t strLen = strlen(pRet);
        if (arrLine[strLen - 1] != '\n')
        {
            callbak(lineNum, NULL, "read line not enough");
            break;
        }
        else
        {
            arrLine[strLen - 1] = '\0';
            callbak(lineNum, arrLine, NULL);
        }
        ++lineNum;
    }
}