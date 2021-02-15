#include <QApplication>
#include <QQuickView>
#include "applicationdata.h"
#include<QQmlContext>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QDebug>
#include <QQuickItem>
#include "myclass.h"

int main(int argc,char* argv[])
{
    QApplication app(argc,argv);

    //1.加载qml文件到视图，并显示
//    QQuickView view;
//    view.setSource(QUrl("practice.qml"));
//    view.show();

    //2.qml调用C++函数
//    QQuickView view;
//    ApplicationData data;
//    //将C++对象作为属性注册到QML
//    view.rootContext()->setContextProperty("applicationData",&data);
//    view.setSource(QUrl("practice.qml"));
//    view.show();

    //3.调用qml函数
//    QQmlApplicationEngine engine;
//    QQmlComponent component(&engine,"practice.qml");
//    QObject * object =component.create();
//    QVariant msg="Hello qml world";
//    QVariant returnedValue;
//    //invokeMethod的Q_RETURN_ARG，Q_ARG参数必须指定为QVariant类型
//    QMetaObject::invokeMethod(object,"qmlFunction",
//                              Q_RETURN_ARG(QVariant,returnedValue),//用于接收函数返回值
//                              Q_ARG(QVariant,msg));//用于传递函数参数

//    qDebug()<<"QML function returned"<<returnedValue.toString();

    //4.qml与C++实现信号与槽函数的调用
    QQuickView view(QUrl::fromLocalFile("practice.qml"));
    QObject * item = view.rootObject();

    MyClass myClass;
    QObject::connect(item,SIGNAL(qmlSignal(QString)),&myClass,SLOT(slotPrint(QString)));

    view.show();
    return app.exec();
}










