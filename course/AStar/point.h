#ifndef POINT_H
#define POINT_H

#include <QObject>

class Point
{
public:
    Point();
    int x,y; //点坐标，这里为了方便按照 C++的数组来计算，x 代表横排，y 代表竖列
    int F,G,H; //F=G+H
    Point *parent; //parent 的坐标
};

#endif // POINT_H
