#ifndef BUTTONITEM_H
#define BUTTONITEM_H

#include <QGraphicsObject>

class ButtonItem : public QGraphicsObject
{
    Q_OBJECT
public:
    ButtonItem(const QPixmap& pixmap,QGraphicsScene* scene);
    ~ButtonItem();

protected:
    //重写图形项的绘图区域
    QRectF boundingRect()const;

private:
    //鼠标按下事件
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

    //绘图
    void paint(QPainter*,const QStyleOptionGraphicsItem* ,QWidget*);

signals:
    void clicked();//点击信号

private:
    QPixmap m_pix;//按钮位图
};

#endif // BUTTONITEM_H
