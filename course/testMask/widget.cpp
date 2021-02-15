#include "widget.h"
#include "ui_widget.h"
#include <QBitmap>
#include <QPixmap>
#include <QPainter>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QPixmap pixmap;
    pixmap.load(":/lena.gif");

    ui->label->resize(pixmap.size());
    resize(pixmap.size());
    //设置遮罩
    setMask(pixmap.mask());
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,QPixmap(":/lena.gif"));
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    close();
}

