#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#pragma execution_character_set("utf-8")
class MyThread : public QThread
{
    Q_OBJECT
public:
    MyThread(QObject* parent = nullptr);
    void stop();

protected:
    void run() override;//线程执行入口

private:
    bool m_isStopped;
};


#endif // MYTHREAD_H
