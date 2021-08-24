#ifndef SHAPE_H_
#define SHAPE_H_

#ifdef __cplusplus
extern "C"
{
#endif

    struct _Shape;
    typedef struct _Shape Shape;

    typedef void (*ShapeFuncMouseDown)(Shape *thiz, float x, float y);
    typedef float (*ShapeFuncArea)(Shape *thiz);
    typedef void (*ShapeDestroy)(Shape *thiz);

    struct _Shape
    {
        ShapeFuncMouseDown func_mouse_down;
        ShapeFuncArea func_area;
        ShapeDestroy func_destroy;

        char priv[0];
    };

    static inline void shape_mouse_down(Shape *thiz, float x, float y)
    {
        thiz->func_mouse_down(thiz, x, y);
    }

    static inline float shape_area(Shape *thiz)
    {
        return thiz->func_area(thiz);
    }

    static inline void shape_destroy(Shape *thiz)
    {
        thiz->func_destroy(thiz);
    }

#ifdef __cplusplus
}
#endif

#endif