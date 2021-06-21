#ifndef FILE_LINE_H_
#define FILE_LINE_H_

typedef struct _FileLine FileLine;

FileLine *openFile(const char *fileName);
void closeFile(FileLine *thiz);

void foreachLine(FileLine *thiz, void (*callbak)(int lineNum, const char *content, const char *errMsg));

#endif