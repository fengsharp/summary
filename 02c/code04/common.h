#ifndef COMMON_H_
#define COMMON_H_

typedef void (*FuncFreeElement)(void *element);
typedef int (*FuncCmpElement)(void *src, void *dest);
typedef void (*FuncPrintElement)(void *element);

#endif