#include "astar.h"
//代价
const int cost1 = 10;
const int cost2 = 10;
AStar::AStar(int max_row,int max_col,QVector<QVector<int>> &p):
    MAX_ROW(max_row),MAX_COL(max_col),map(p)
{

}

AStar::~AStar()
{
    for(int i=0;i<open.size();i++)
    {
        delete open[i];
    }
    QVector<Point*> ().swap(open);
    for(int i=0;i<close.size();i++)
    {
        delete close[i];
    }
    QVector<Point*> ().swap(close);
    QVector<Point*> ().swap(s);
    delete start_point;
    delete end_point;
}

QVector<Point *> AStar::get_path(Point &temp_start, Point &temp_end)
{
    start_point =new Point(temp_start.X,temp_start.Y);
    end_point =new Point(temp_end.X,temp_end.Y);
    Point *result= find_path(start_point,end_point);
    while(result)
    {
        s.push_front(result);
        result = result->parent;
    }

    return s;
}
int AStar::calc_G(Point *temp_start, Point *point)
{
    int extraG = (abs(point->X - temp_start->X) + abs(point->Y - temp_start->Y)) == 1 ? cost1 : cost2;
    int parentG = point->parent == nullptr ? 0 : point->parent->G; //如果是初始节点，则其父节点是空
    return parentG + extraG;
}

int AStar::calc_H(Point *point, Point *end)
{
    int H = sqrt(abs(point->X - end->X)*abs(point->X - end->X)+ abs(point->Y - end->Y)*abs(point->Y - end->Y))*cost1;
    return H;
}

int AStar::calc_F(Point *point)
{
    int F = point->G + point->H;
    return F;
}

Point *AStar::find_path(Point *start, Point *end)
{
    open.push_back(new Point(start->X,start->Y));
    while(!open.empty())
    {
        auto curPoint=find_Fmin(open);//找到F值最小的点
        open.removeOne(curPoint);//从开启列表中删除
        close.push_back(curPoint);//放到关闭列表
        //1,找到当前周围八个格中可以通过的格子
        auto surroundingPoints = find_surrounding_points(curPoint);
        for(int i =0;i<surroundingPoints.size();i++)
        {
            //2,对某一个格子，如果它不在开启列表中，加入到开启列表，设置当前格为其父节点，计算F G H
            if(!in_list(open,surroundingPoints[i]))
            {
                surroundingPoints[i]->parent = curPoint;
                surroundingPoints[i]->G = calc_G(curPoint,surroundingPoints[i]);
                surroundingPoints[i]->H = calc_H(surroundingPoints[i],end);
                surroundingPoints[i]->F = calc_F(surroundingPoints[i]);
                open.push_back(surroundingPoints[i]);
            }else
                //3，对某一个格子，它在开启列表中，计算G值, 如果比原来的大, 就什么都不做, 否则设置它的父节点为当前点,并更新G和F
            {
                int tempG = calc_G(curPoint,surroundingPoints[i]);
                if(tempG<surroundingPoints[i]->G)
                {
                    surroundingPoints[i]->parent = curPoint;
                    surroundingPoints[i]->G =tempG;
                    surroundingPoints[i]->F =calc_F(surroundingPoints[i]);
                }
            }
            Point *resPoint = in_list(open,end);
            if(resPoint)
            {
                return resPoint;
            }
        }
    }
    return nullptr;
}

bool AStar::can_reach(Point *point, Point *target)
{
    if(target->X<0 || target->X>MAX_COL - 1
            || target->Y<0 || target->Y>MAX_ROW - 1
            || map[target->Y][target->X] == 1
            || ((target->X == point->X)&&(target->Y == point->Y))
            || in_list(close,target))//如果点与当前节点重合、超出地图、是障碍物、或者在关闭列表中，返回false
    {
        return false;
    }
    else
    {
        if(abs(point->X -target->X) + abs(point->Y -target->Y) == 1)
        {
            return true;
        }
        return false;
    }
}

Point* AStar::in_list(QVector<Point *> list, Point *point)
{
    for(int i=0;i<list.size();i++)
    {
        if(list[i]->X==point->X&&list[i]->Y==point->Y)
        {
            return list[i];
        }
    }
    return nullptr;
}

QVector<Point *> AStar::find_surrounding_points(Point *point)
{
    QVector<Point *> surrounding;
    for (int x = point->X - 1; x <= point->X + 1; x++)
    {
        for (int y = point->Y - 1; y <= point->Y + 1; y++)
        {
            Point  *pp = new Point(x,y);
            if (in_list(open, pp)!=nullptr)
            {
                surrounding.push_back(in_list(open, pp));
                delete pp;
            }else if (can_reach(point, pp))
            {
                surrounding.push_back(pp);
            }
            else {
                delete pp;
            }
        }

    }

    return surrounding;
}

Point *AStar::find_Fmin(QVector<Point *> &list)
{
 if(!list.isEmpty())
 {
     Point *point= 0;
     point=list.front();
     for(int i=1;i<list.size();i++)
     {
         if(point->F>list[i]->F)
         {
             point=list[i];
         }
     }
     return point;
 }
 return nullptr;
}
