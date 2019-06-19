#include "DrawPoint.h"


void DrawPoint(int *py,int x, int y, int color)
{
    if(x >= 0 && x < PWIDTH && y >= 0 && y < PHIGH)
    {
        *(py + PWIDTH* y + x) = color;
    }
}