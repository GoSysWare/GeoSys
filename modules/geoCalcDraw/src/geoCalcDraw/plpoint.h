#ifndef PLPOINT_H
#define PLPOINT_H

class PLPoint
{
public:
    PLPoint();
    PLPoint(int xx, int yy);
    PLPoint(const PLPoint &pt);

    int x;
    int y;
    bool mark;
};

#endif // PLPOINT_H
