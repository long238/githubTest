#ifndef PAINTAREA_H
#define PAINTAREA_H
#pragma execution_character_set("utf-8")
#include <QWidget>
#include <QPen>

class PaintArea : public QWidget
{
    Q_OBJECT
public:
    enum Shape{Line,Rectangle,RoundRect,
               Ellipse,Polygon,Polyline,Points,
               Arc,Path,Text,Pixmap};
    PaintArea(QWidget *parent = nullptr);

public:
    void setShape(Shape shape);
    void setPen(QPen pen);
    void setBrush(QBrush brush);
    void setFillRule(Qt::FillRule rule);

protected:
    void paintEvent(QPaintEvent *event) override;

public:
    QPen m_pen;

private:
    Shape m_shape;

    QBrush m_brush;
    Qt::FillRule m_fillrule;

signals:



};

#endif // PAINTAREA_H
