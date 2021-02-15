#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>

int main(int argc,char* argv[])
{
    QApplication app(argc,argv);

    //新建场景
    QGraphicsScene scene;

    //创建矩形图形项
    QGraphicsRectItem *item = new QGraphicsRectItem(0,0,100,100);
    scene.addItem(item);

    QGraphicsView view(&scene);//为场景创建视图
    view.setForegroundBrush(QColor(255,25,28,100));//设置场景前景色
    view.setBackgroundBrush(QPixmap("2.jpg"));//设置背景刷
    view.resize(400,400);
    view.show();

    return app.exec();

}
