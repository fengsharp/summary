#ifndef TYPE_DEF_H_
#define TYPE_DEF_H_

#include <stdio.h>

typedef enum _Ret
{
    RET_OK,
    RET_OOM,
    RET_STOP,
    RET_INVALIDE_PARAMS,
    RET_FAIL,
} Ret;

#ifdef __cplusplus
#define DECLS_BEGIN \
    extern "C"      \
    {
#define DECLS_END }
#else
#define DECLS_BEGIN
#define DECLS_END
#endif

#define return_if_fail(p) if (!(p)) \
    {printf("%s:%d Warning: "#p" failed.\n", __func__, __LINE__);}

#define return_val_if_fail(p, ret) if (!(p)) \
    {printf("%s:%d Warning: "#p" failed.\n", __func__, __LINE__); return (ret);}

#define SAFE_FREE(p) if ((p) != NULL) {free(p); p = NULL;}

typedef void (*callback_foreach)(void *ctx, void *data);

#endif