#ifndef BIRDITEM_H
#define BIRDITEM_H

#include <QGraphicsObject>

class QPropertyAnimation;

//游戏中的鸟儿对象（图形像），自定义图形项时，需重写paint,boundingRect
class BirdItem:public QGraphicsObject
{
    Q_OBJECT
public:
    BirdItem(QGraphicsScene* scene);
    ~BirdItem();

public:
    QRectF boundingRect() const;        //重写绘图区域
    void flyRaiseAnimation();           //上升动画
    void flyLandfallAnimation();        //下降动画
    bool checkIsCollided();             //碰撞检测

private slots:
    void onRefreshBird();   //定时刷新小鸟
    void onFlyRaiseAnimationFinished();//上升动画结束


private:
    //重写绘图事件
    void paint(QPainter*,const QStyleOptionGraphicsItem*,QWidget*);
public:
    //重写键盘事件，空格键控制小鸟
    void keyPressEvent(QKeyEvent* event);

private:
    QTimer *m_birdRefreshTimer; //刷新小鸟的计时器
    QGraphicsScene* m_scene;    //所在场景
    QPropertyAnimation *m_flyAnimation;//飞行动画
    int m_curflyStatus; //当前飞行状态
    bool m_IsLandFall;  //下降标志
    bool m_IsRaise;     //上升标志


};

#endif // BIRDITEM_H



