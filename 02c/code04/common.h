#ifndef COMMON_H_
#define COMMON_H_

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

typedef void (*FuncFreeElement)(void *element);
typedef int (*FuncCmpElement)(void *src, void *dest);
typedef void (*FuncPrintElement)(void *element);

#endif