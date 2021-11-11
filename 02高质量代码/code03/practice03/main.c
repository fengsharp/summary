#include <stdio.h>
#include <stdlib.h>

// shape interface mouse down | area
// ret down(p1-left-top)   down(p2-right-bottom)    (0, 0)   (10, 10)    10 * 10
// circle down(center point)  down(radius point)    (0, 0)   (10, 10)    pi(3.14) * 10 * 10 

#include "shape.h"
#include "shape_rect.h"
#include "shape_circle.h"


int main()
{
    Shape *pRect = shape_create_rect();
    shape_mouse_down(pRect, 0.0f, 0.0f);
    shape_mouse_down(pRect, 10.0f, 10.0f);
    printf("rect area: %f\n", shape_area(pRect));
    shape_destroy(pRect);

    Shape *pCircle = shape_create_circle();
    shape_mouse_down(pCircle, 0.0f, 0.0f);
    shape_mouse_down(pCircle, 10.0f, 10.0f);
    printf("circle area: %f\n", shape_area(pCircle));
    shape_destroy(pCircle);

    return 0;
}