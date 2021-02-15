#include "astar.h"

Astar::Astar()
{

}

Astar::~Astar()
{
    maze = NULL;
    lines = 0;
    cols = 0;
    QList<Point*>::iterator itor;
    //清除 openList 中的元素
    for (itor = openList.begin(); itor != openList.end();) {
        delete *itor;
        itor = openList.erase(itor);//获取到下一个节点
    }
    //清理 closeList 中的元素
    for (itor = closeList.begin(); itor != closeList.end();) {
        delete *itor;
        itor = closeList.erase(itor);
    }
}

Point *Astar::AllocPoint(int x, int y)
{
    Point *temp = new Point;
    memset(temp, 0, sizeof(Point));//初始值清零
    temp->x = x;
    temp->y = y;
    return temp;
}

void Astar::InitAstarMaze(int *_maze, int _lines, int _colums)
{
    maze = _maze;
    lines = _lines;
    cols = _colums;
}

QList<Point*> Astar::GetPath(Point *startPoint, Point *endPoint,bool isBox)
{
    Point *result = findPath(startPoint, endPoint);
    QList<Point *> path; //返回路径，如果没找到路径，返回空链表
    while(result)
    {
        path.push_front(result);
        result=result->parent;
    }
    return path;
}


Point *Astar::findPath(Point *startPoint, Point *endPoint)
{
    openList.push_back(AllocPoint(startPoint->x, startPoint->y));//置入起点,拷贝开辟一个节点，内外隔离
        while(!openList.empty()){
            //第一步，从开放列表中取最小 F 的节点
            Point *curPoint = getLeastFpoint();//找到 F 值最小的点

            //第二步，把当前节点放到关闭列表中
            openList.removeOne(curPoint);

            closeList.push_back(curPoint);

            //第三步，找到当前节点周围可达的节点，并计算 F 值
            QList<Point *> surroundPoints = getSurroundPoints(curPoint);

            QList<Point *>::const_iterator iter;
            for (iter = surroundPoints.begin(); iter != surroundPoints.end(); iter++) {
                Point *target = *iter;
                //对某一个格子，如果它不在开放列表中，加入到开启列表，设置 当前格为其父节点，计算 F G H
                Point *exist = isInList(openList, target);
                if(!exist){
                    target->parent=curPoint;
                    target->G=calcG(curPoint,target);
                    target->H=calcH(target,endPoint);
                    target->F=calcF(target);
                    openList.push_back(target);
                }else {
                    int tempG = calcG(curPoint, target);
                    if(tempG<target->G){
                        exist->parent = curPoint;
                        exist->G=tempG;
                        exist->F=calcF(target);
                    }
                    delete target;
                }
            }//end for
            surroundPoints.clear();
            Point *resPoint = isInList(openList, endPoint);
            if(resPoint){
                return resPoint;
            }
        }
        return NULL;
}

Point *Astar::getLeastFpoint()
{
    if (!openList.empty()) {
            Point *resPoint = openList.front();
            QList<Point *>::const_iterator itor;
            for (itor = openList.begin(); itor != openList.end(); itor++) {
                if ((*itor)->F < resPoint->F) {
                    resPoint = *itor;
                }
            }
            return resPoint;
        }
    return NULL;
}

QList<Point *> Astar::getSurroundPoints(const Point *point)
{
     QList<Point *> surroundPoints;
        for (int x = point->x - 1; x <= point->x + 1; x++) {
            for (int y = point->y - 1; y <= point->y + 1; y++) {
                if( (x==point->x && y != point->y) || (x!=point->x && y == point->y)  )
                {
                    Point *target = AllocPoint(x, y);
                    if (isCanreach(point, target))//判断该点是否可以移动
                    {
                        if(isBox )//是箱子，要判断人物是否可以在推箱子的位置上
                        {
                            if(isArrive(point,target))
                                surroundPoints.push_back(target);
                        }else{
                            //用来判断人物是否可以到达对应的位置，及正常的自动寻路
                            surroundPoints.push_back(target);

                        }

                    } else {
                        delete target;
                    }
                }

            }
        }
        return surroundPoints;
}

bool Astar::isCanreach(const Point *point, const Point *target)
{
    if (target->x<0 || target->x>(lines)
            || target->y<0 || target->y>(cols)
            || maze[target->x *cols + target->y] == 1
            || maze[target->x *cols + target->y] == 4
            || (target->x == point->x && target->y == point->y)
            ) {
            return false;
        }

        if (abs(point->x - target->x) + abs(point->y - target->y) == 1) {
            return true;
        } else {
            return false;
        }
}

Point *Astar::isInList(const QList<Point *> &list, const Point *point)
{
    //判断某个节点是否在列表中，这里不能比较指针，因为每次加入列表是新 开辟的节点，只能比较坐标
        QList<Point *>::const_iterator itor;
        for (itor = list.begin(); itor != list.end();itor++){
            if ((*itor)->x == point->x && (*itor)->y == point->y) {
                return *itor;
            }
        }
        return NULL;
}

bool Astar::isArrive(const Point *point, const Point *target)
{
    if(target->x > point->x && target->y == point->y)//箱子向左移动
    {
        if(maze[target->x *cols + target->y +2] != 2)
        {
            delete target;
            return false;

        }
    }else if(target->x < point->x && target->y == point->y )//箱子向右移动
    {
        if(maze[target->x *cols + target->y -2] != 2)
        {
            delete target;
            return false;

        }
    }else if(target->x == point->x && target->y < point->y)//箱子向下移动
    {
        if(maze[(target->x +2)*cols + target->y ] != 2)
        {
            delete target;
            return false;

        }
    }else if(target->x == point->x && target->y > point->y)//箱子向上移动
    {
        if(maze[(target->x -2) *cols + target->y ] != 2)
        {
            delete target;
            return false;

        }
    }
    return true;


}

int Astar::calcG(Point *temp_start, Point *point)
{
        int parentG = (point->parent == NULL ? NULL : point->parent->G);
        //如果是 初始节点，则其父节点是空
        return parentG+kCost1;
}

int Astar::calcH(Point *point, Point *end)
{
    //用简单的欧几里得距离计算(勾股定理) H，可以用多中方式实现
        return static_cast<int>(sqrt(static_cast<double>(end->x-point->x)*static_cast<double>(end->x-point->x)+
            static_cast<double>(end->y-point->y)*static_cast<double>(end->y-point->y))
            *kCost1);
}

int Astar::calcF(Point *point)
{
    return point->G+ point->H;
}

















