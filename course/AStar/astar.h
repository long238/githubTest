#ifndef ASTAR_H
#define ASTAR_H

#include <QObject>
#include "Point.h"

const int kCost1 = 10;//直移一格消耗

class Astar
{
public:
    Astar();
    ~Astar();

public:
    /*分配一个节点(格子)*/
    Point* AllocPoint(int x, int y);

    /*初始化地图*/
    void InitAstarMaze(int *_maze, int _lines, int _colums);

    /*通过 A* 算法寻找路径*/
    QList<Point *> GetPath(Point *startPoint, Point *endPoint,bool isBox);


private:
    /*搜索从起点到终点的最佳路径*/
     Point* findPath(Point *startPoint, Point *endPoint);

    /*从开启列表中返回 F 值最小的节点*/
     Point *getLeastFpoint();

    /*获取当前点周围可达的节点*/
     QList<Point *> getSurroundPoints(const Point *point);

    /*判断某点是否可以用于下一步判断 */
    bool isCanreach(const Point *point, const Point *target);

    /*判断开放/关闭列表中是否包含某点*/
    Point *isInList(const QList<Point *> &list, const Point *point);

    //判断人物是否可以到达
    bool isArrive(const Point *point, const Point *target);

    //计算 FGH 值
    int calcG(Point *temp_start , Point *point);
    int calcH(Point *point, Point *end);
    int calcF(Point *point);

private:
    int *maze; //迷宫对应的二维数组，使用一级指针表示
    int cols; //二维数组对应的列数
    int lines; //二维数组对应的行数
    bool isBox;//是否是箱子

    QList<Point *>openList; //开放列表
    QList<Point *>closeList; //关闭列表
};

#endif // ASTAR_H
