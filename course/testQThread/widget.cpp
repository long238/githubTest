#include "widget.h"
#include "ui_widget.h"

extern int gPies;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_startBtn_clicked()
{
    gPies = 0;
    m_myThread1.start();
    m_myThread2.start();
    m_myThread3.start();
}

void Widget::on_stopBtn_clicked()
{
    m_myThread1.stop();
    m_myThread2.stop();
    m_myThread3.stop();
}
