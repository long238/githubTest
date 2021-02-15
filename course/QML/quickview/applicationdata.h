#ifndef APPLICATIONDATA_H
#define APPLICATIONDATA_H

#include <QObject>
#include <QDateTime>

class ApplicationData : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationData(QObject *parent = nullptr);

    //QML中调用C++函数，这个函数需以Q_INVOKABLE进行标记
    //或者该函数是一个Qt槽函数
    Q_INVOKABLE QDateTime getCurrentDateTime() const{
        return QDateTime::currentDateTime();
    }
signals:

};

#endif // APPLICATIONDATA_H
