#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QStyleOption>
#include <QFile>
#include <QMessageBox>
#include <QComboBox>

#define  WIDTH     60
#define  HEIGHT    60

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    initControl();
    ui->stackedWidget->setCurrentIndex(0);
    //ziDoXunLu();

    for(int i=1;i<9;i++)
        ui->comboBox->addItem(QString("map%1.txt").arg(i));
    ui->comboBox->setCurrentIndex(0);

}

Widget::~Widget()
{
    delete ui;
}

bool Widget::InitMaze(const QString &name)
{
    for(int i=0;i<20;i++)
        for(int j=0;j<10;j++)
            map[i][j]=-1;
    QFile file(name);
    QString str="";
    mapy=0,mapx=0;
    file.open(QFile::ReadOnly);
    str=file.readLine();
    while(!str.isEmpty())
    {
        int i=0;
        std::string str2 = str.toStdString();
        //分析地图数据
        for(i=0;i<str2.length();i++)
        {
            switch (str2[i]) {
            case ' '://可移动 0
                map[i][mapy]=0;
                break;
            case 'X'://箱子 1
                map[i][mapy]=1;
                box_x=i;
                box_y=mapy;
                break;
            case 'A'://人物 2
                map[i][mapy]=2;
                manx=i;
                many=mapy;
                break;
            case 'O'://需要移动到的位置3
                map[i][mapy]=3;
                goal_x=i;
                goal_y=mapy;
                break;
            case '-'://障碍物4
                map[i][mapy]=4;
                break;
            default:
                break;
            }
        }
        if(mapx<i)
            mapx=i;
        mapy++;
        str=file.readLine();
    }
    mapx-=2;
    file.close();
    setFixedSize(WIDTH*mapx,HEIGHT*mapy);
    return true;
}

void Widget::InitMusic()
{
    m_welcomePlayer = new QMediaPlayer(this);

    //循环播放
    m_welcomePlayerList = new QMediaPlaylist(this);
    m_welcomePlayerList->addMedia(QUrl("qrc:/sound/welcome.mp3"));
    //...添加其他播放音乐
    //...添加其他播放音乐
    //...添加其他播放音乐

    m_welcomePlayerList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);//循环播放当前列表中的曲目
    m_welcomePlayer->setPlaylist(m_welcomePlayerList);//设置播放列表
    m_welcomePlayer->play();//播放
}

void Widget::ziDoXunLu()
{

        x.InitAstarMaze(&map[0][0], mapx, mapy); //设置起始和结束点
            Point* start = x.AllocPoint(box_x,box_y);
            Point* end = x.AllocPoint(goal_x,goal_y);
            //A*算法找寻路径
            QList<Point*> path = x.GetPath(start, end,true);
            qDebug()<<"寻路结果:";
            QList<Point*>::const_iterator iter;
            for(iter=path.begin(); iter!=path.end(); iter++){
                Point *cur = *iter;
                qDebug()<<'('<<cur->x<<','<<cur->y<< ',' << cur->F << ')';
            }
}

void Widget::initControl()
{
    InitMusic();
    ground.load(":/image/ground.png");
    box.load(":/image/box.png");
    man.load(":/image/man.png");
    goal.load(":/image/goal.png");
    wall.load(":/image/wall.png");
    InitMaze(":/data/map5.txt");
    isok = false;




}

bool Widget::judge(const int &x,const int &y)
{
    if(map[manx+x][many+y] != 4)
    {
        //人物移动，碰到的是箱子，且不能超出界面的长度
        if(map[manx+x][many+y] == 1 && (many+y*2)<(mapy-1)
                && (manx+x*2)<(mapx-1) && (many+y*2)>=0 && (manx+x*2)>=0)
        {
            //箱子的x或y方向不能是墙
            if(map[manx+x*2][many+y*2] == 4 )
            {
                return false;
            }
            map[manx+x*2][many+y*2]=1;
//            box_x=manx+x*2;
//            box_y=many+y*2;
            map[manx+x][many+y]=2;
            map[manx][many]=0;
            many+=y;
            manx+=x;
            //箱子向下移动，箱子是否到达目的地
            if(manx+x == goal_x && many+y == goal_y)
            {
                return true;
            }
        }else{

            //人物移动,碰到的是空地或目的地
            map[manx+x][many+y]=2;
            if(manx != goal_x || many != goal_y)
                map[manx][many]=0;
            many+=y;
            manx+=x;
        }
//

    }
    return false;
}




void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    if(!isok)//未启动游戏
    {
        painter.drawPixmap(0,0,WIDTH*mapx,HEIGHT*mapy,QPixmap(":/image/start.png"));
        //清空之前绘制的东西
        painter.end();
        return;
    }
    for (int i=0;i<mapx;i++) {
        for (int j=0 ;j<mapy;j++) {
            switch(map[i][j])
            {
            case 0://可移动
                painter.drawPixmap(i*WIDTH,j*HEIGHT,WIDTH,HEIGHT,ground);
                break;
            case 1://箱子 1
                painter.drawPixmap(i*WIDTH,j*HEIGHT,WIDTH,HEIGHT,box);
                break;
            case 2://人物 2
                painter.drawPixmap(i*WIDTH,j*HEIGHT,WIDTH,HEIGHT,man);
                break;
            case 3://需要移动到的位置 3
                painter.drawPixmap(i*WIDTH,j*HEIGHT,WIDTH,HEIGHT,goal);
                break;
            case 4://障碍物 4
                painter.drawPixmap(i*WIDTH,j*HEIGHT,WIDTH,HEIGHT,wall);
                break;
            default:
                break;
            }

        }
    }


}

void Widget::keyPressEvent(QKeyEvent *event)
{
    map[goal_x][goal_y]=3;
    switch(event->key())
    {
    case Qt::Key_Down:
        if(judge(0,1))
        {
            update();
            QMessageBox::information(this,"提示","闯关成功");
            isok=false;
            ui->stackedWidget->setCurrentIndex(1);
        }
        break;
    case Qt::Key_Left:
        if(judge(-1,0))
        {
            update();
            QMessageBox::information(this,"提示","闯关成功");
            isok=false;
            ui->stackedWidget->setCurrentIndex(1);
        }
        break;
    case Qt::Key_Right:
        if(judge(1,0))
        {
            update();
            QMessageBox::information(this,"提示","闯关成功");
            isok=false;
            ui->stackedWidget->setCurrentIndex(1);
        }
        break;
    case Qt::Key_Up:
        if(judge(0,-1))
        {
            update();
            QMessageBox::information(this,"提示","闯关成功");
            isok=false;
            ui->stackedWidget->setCurrentIndex(1);
        }
        break;
    default:
        break;

    }
    update();
}


void Widget::on_pushButton_clicked()
{

    ui->pushButton->setVisible(false);

    ui->stackedWidget->setCurrentIndex(1);
}

void Widget::on_pushButton_2_clicked()
{
    isok=true;

    QString str = ui->comboBox->currentText();
    InitMaze(QString(":/data/%1").arg(str));
    update();
    ui->stackedWidget->setCurrentIndex(2);
    qDebug()<<str<<QString(":/data/%1").arg(str);
}
