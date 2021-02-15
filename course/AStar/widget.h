#ifndef WIDGET_H
#define WIDGET_H
#pragma execution_character_set("utf-8")
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QPainter>
#include <QPaintEvent>
#include <QPixmap>
#include "astar.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:

    //加载地图
    bool InitMaze(const QString &name);

    //加载音乐
    void InitMusic();

    //自动寻路
    void ziDoXunLu();
    
    //初始化
    void initControl();

    //移动判读
    bool judge(const int &x=0,const int &y=0);


private:
    void paintEvent(QPaintEvent *event);
    
    void keyPressEvent(QKeyEvent *event);
    
private:
    Ui::Widget *ui;

    Astar x;

    int map[20][10];
    int mapx,mapy;

    int manx,many;

    int goal_x,goal_y;

    int box_x,box_y;
    //游戏常用的图片
    QPixmap ground;
    QPixmap box;
    QPixmap man;
    QPixmap goal;
    QPixmap wall;

    //判断是否开始游戏
    bool isok;

    QMediaPlayer *m_welcomePlayer;  //欢迎音乐
    QMediaPlaylist *m_welcomePlayerList;


};
#endif // WIDGET_H
