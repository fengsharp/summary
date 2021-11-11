#include "shape_circle.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct _ShapeCircle
{
    int mouseDown;
    float x1;
    float y1;
    float x2;
    float y2;
} ShapeCircle;

static void shape_circle_mouse_down(Shape *thiz, float x, float y)
{
    ShapeCircle *pCircle = (ShapeCircle*)(thiz->priv);
    if (pCircle->mouseDown % 2 == 0)
    {
        pCircle->x1 = x;
        pCircle->y1 = y;
    }
    else
    {
        pCircle->x2 = x;
        pCircle->y2 = y;
    }
    ++pCircle->mouseDown;
}

static float shape_circle_area(Shape *thiz)
{
    ShapeCircle *pCircle = (ShapeCircle*)(thiz->priv);

    float deltaX = fabs(pCircle->x1 - pCircle->x2);
    float deltaY = fabs(pCircle->y1 - pCircle->y2);
    float radius = sqrtf(deltaX * deltaX + deltaY * deltaY);
    return 3.14f * radius * radius;
}

static void shape_circle_destroy(Shape *thiz)
{
    free(thiz);
}

Shape *shape_create_circle(void)
{
    Shape *pResult = malloc(sizeof(Shape) + sizeof(ShapeCircle));
    if (pResult)
    {
        // ShapeCircle *pCircle = (ShapeCircle*)(pResult->priv);
        memset(pResult, 0, sizeof(ShapeCircle));
        pResult->func_mouse_down = shape_circle_mouse_down;
        pResult->func_area = shape_circle_area;
        pResult->func_destroy = shape_circle_destroy;
    }
    return pResult;
}