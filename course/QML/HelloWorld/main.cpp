#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    //支持高分屏（高分辨率的屏幕）
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    //创建qml引擎
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));

    //连接qml引擎的信号槽
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);//如果qml文件是空或错误，就直接退出
    }, Qt::QueuedConnection);

    //引擎加载qml文件
    engine.load(url);

    return app.exec();
}
