#include "plpoint.h"

PLPoint::PLPoint()
{
    mark = false;
}

PLPoint::PLPoint(int xx, int yy)
{
    x = xx;
    y = yy;
    mark = false;
}

PLPoint::PLPoint(const PLPoint &pt){
    x = pt.x;
    y = pt.y;
    mark = pt.mark;
}
