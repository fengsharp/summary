#include "shape_rect.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct _ShapeRect
{
    int mouseDown;
    float x1;
    float y1;
    float x2;
    float y2;
} ShapeRect;

static void shape_rect_mouse_down(Shape *thiz, float x, float y)
{
    ShapeRect *pRect = (ShapeRect*)(thiz->priv);
    if (pRect->mouseDown % 2 == 0)
    {
        pRect->x1 = x;
        pRect->y1 = y;
    }
    else
    {
        pRect->x2 = x;
        pRect->y2 = y;
    }
    ++pRect->mouseDown;
}

static float shape_rect_area(Shape *thiz)
{
    ShapeRect *pRect = (ShapeRect*)(thiz->priv);
    float width = fabs(pRect->x1 - pRect->x2);
    float height = fabs(pRect->y1 - pRect->y2);
    return width * height;
}

static void shape_rect_destroy(Shape *thiz)
{
    free(thiz);
}

Shape *shape_create_rect(void)
{
    Shape *pResult = malloc(sizeof(Shape) + sizeof(ShapeRect));
    if (pResult)
    {
        // ShapeRect *pRect = (ShapeRect*)(pResult->priv);
        memset(pResult, 0, sizeof(ShapeRect));
        pResult->func_mouse_down = shape_rect_mouse_down;
        pResult->func_area = shape_rect_area;
        pResult->func_destroy = shape_rect_destroy;
    }
    return pResult;
}