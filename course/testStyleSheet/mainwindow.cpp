#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QGraphicsOpacityEffect>
#include <QGraphicsDropShadowEffect>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置样式按钮设置背景为红色
    //ui->pushButton->setStyleSheet("background:red");
    //设置所有按钮的背景为红色，前景色（颜色）为黄色
    //setStyleSheet("QPushButton{background:red;color:yellow}");
    //设置横向滑动条背景色为蓝色
    //ui->horizontalSlider->setStyleSheet("background:blue");

    //窗口透明属性,取值0~1,0表示完全透明，1表示完全不透明
    //setWindowOpacity(0.5);

    //部件不透明，窗体背景完全透明，WIndows下需要配合无边框风格FramelessWindowHint
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    //标签设置透明
//    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect();
//    opacityEffect->setOpacity(0.9);
//    ui->label->setGraphicsEffect(opacityEffect);

//    //部件阴影效果
//    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect();
//    //阴影色，透明度
//    shadowEffect->setColor(QColor(100,100,100));
//    shadowEffect->setBlurRadius(20);    //阴影模糊半径
//    shadowEffect->setXOffset(20);       //阴影偏移值
//    ui->label->setGraphicsEffect(shadowEffect);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(),QColor(255,255,255,200));


}

