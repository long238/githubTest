#include "mythread.h"
#include <QDebug>
#include <QMutex>

int gPies = 0;
QMutex mutex;//互斥锁

MyThread::MyThread(QObject* parent):QThread(parent)
{
    m_isStopped =false;
}

void MyThread::stop()
{
    m_isStopped = true;
}

void MyThread::run()
{
    int i = 0;
    while(!m_isStopped && i++ < 200000)
    {
        mutex.lock();
        qDebug()<<QString("%1郭伟龙最帅").arg(++gPies);
        mutex.unlock();
    }
}
