#ifndef ROADITEM_H
#define ROADITEM_H

#include <QGraphicsObject>
#include <QGraphicsScene>

//道路图形项
class RoadItem : public QGraphicsObject
{
    Q_OBJECT
public:
    RoadItem(QGraphicsScene *scene);
    ~RoadItem();

protected:
    //重写图形项的绘图区域
    QRectF boundingRect() const;

    //重写图形项的绘图区域
    void paint(QPainter* painter,const QStyleOptionGraphicsItem*,QWidget*);

private:
    void startMove();//开始移动

private:
    QGraphicsScene *m_scene;
};

#endif // ROADITEM_H
