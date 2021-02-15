#include "pipeitem.h"
#include <QPainter>
#include <QPropertyAnimation>

#define PIPE_WIDTH 48

PipeItem::PipeItem(QGraphicsScene* scene)
    :m_scene(scene)
{
    //游戏场景中添加管道图形对象
    scene->addItem(this);
    createPipeHeight();
    startMove();

}

PipeItem::~PipeItem()
{

}

//重写绘图区域
QRectF PipeItem::boundingRect() const
{
    return QRectF(m_scene->width(),0,PIPE_WIDTH,m_scene->height());
}

//重写绘图事件
void PipeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

    //画上管道
    painter->drawImage(QRectF(m_scene->width(),0,PIPE_WIDTH,m_upPipeHeight),
                       QImage(":/BirdGame/Resources/image/tubeup.png"));

    painter->drawImage(QRectF(m_scene->width(),m_upPipeHeight+140,PIPE_WIDTH,m_downPipeHeight),
                       QImage(":/BirdGame/Resources/image/tubedown.png"));
}

QPainterPath PipeItem::shape() const
{
    QPainterPath path;
    path.addRect(QRectF(m_scene->width(),0,PIPE_WIDTH,m_upPipeHeight));
    path.addRect(QRectF(m_scene->width(),m_upPipeHeight+140,PIPE_WIDTH,m_downPipeHeight));
    return path;
}

void PipeItem::startMove()
{
    //移动的动画（位置属性动画）
    QPropertyAnimation *moveAnimation = new QPropertyAnimation(this,"pos");
    moveAnimation->setLoopCount(-1);    //无限循环
    moveAnimation->setDuration(3000);   //动画时长3秒
    moveAnimation->setEndValue(QPoint(0-m_scene->width()-PIPE_WIDTH,pos().y()));
    moveAnimation->setStartValue(QPoint(0,pos().y()));
    moveAnimation->start();

    //动画循环次数改变时则创建管道
    connect(moveAnimation,&QPropertyAnimation::currentLoopChanged,
            [this](){
            createPipeHeight();
    });

}

//创建管道高度
void PipeItem::createPipeHeight()
{
    m_upPipeHeight = qrand()%100+80;//上管道
    m_downPipeHeight = m_scene->height() - m_upPipeHeight - 168;//下管道的高度

}
