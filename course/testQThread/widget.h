#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mythread.h"
#pragma execution_character_set("utf-8")
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_startBtn_clicked();

    void on_stopBtn_clicked();

private:
    Ui::Widget *ui;
    MyThread m_myThread1,m_myThread2,m_myThread3;

};
#endif // WIDGET_H
