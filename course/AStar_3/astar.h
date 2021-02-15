#ifndef ASTAR_H
#define ASTAR_H

#include "point.h"
#include <QVector>
#include <cmath>

class AStar
{
public:
    AStar(int max_row,int max_col,QVector<QVector<int>> &p);
    ~AStar();
    //获取路径
    QVector<Point*> get_path(Point &temp_start, Point &temp_end);
    //计算G,H,F值
    int calc_G(Point *temp_start, Point *point);
    int calc_H(Point *point,Point *end);
    int calc_F(Point *point);
    //寻路
    Point* find_path(Point *start,Point *end);
    //检测点是否能到达目标点
    bool can_reach(Point *point,Point *target);
    //检测点是否在QVector中，若在返回这个点，若不在，返回空指针
    Point *in_list(QVector<Point*> list,Point *point);
    //寻找周围的点
    QVector<Point*> find_surrounding_points(Point *point);
    //寻找QVector中f值最小的点
    Point* find_Fmin(QVector<Point*> &list);

private:
    Point *start_point;
    Point *end_point;
    //地图长宽
    int MAX_ROW;
    int MAX_COL;
    QVector<QVector<int>> map;
    //储存路径
    QVector<Point*> s;
    QVector<Point*> open;
    QVector<Point*> close;
};

#endif // ASTAR_H
