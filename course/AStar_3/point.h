#ifndef POINT_H
#define POINT_H


class Point
{
public:
    Point();
    Point(int x,int y);
    int X;
    int Y;
    int G;
    int H;
    int F;
    Point* parent;
};

#endif // POINT_H
