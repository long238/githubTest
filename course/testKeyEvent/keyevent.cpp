#include "keyevent.h"
#include "ui_keyevent.h"
#include <QPainter>
#include <QPen>

KeyEvent::KeyEvent(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::KeyEvent)
{
    ui->setupUi(this);
    setWindowTitle(QString("键盘事件"));
    setAutoFillBackground(true);

    setFixedSize(512,256);
    m_width=size().width();
    m_height=size().height();

    m_pix = new QPixmap(m_width,m_height);
    m_pix->fill(Qt::white);

    m_image.load("lena.gif");

    m_startX=100;
    m_startY=100;
    m_step=20;
    drawPix();


}

KeyEvent::~KeyEvent()
{
    delete ui;
}

void KeyEvent::drawPix()
{
    m_pix->fill(Qt::white);
    QPainter painter(this);
    QPen pen(Qt::DotLine);

    painter.begin(m_pix);//指定绘图设备
    painter.setPen(pen);

    //按照步长画纵向网格线
    for(int i=m_step; i<m_width;i+=m_step)
    {
        painter.drawLine(QPoint(i,0),QPoint(i,m_height));
    }
    //按照步长画横向网格线
    for(int i=m_step; i<m_height;i+=m_step)
    {
        painter.drawLine(QPoint(0,i),QPoint(m_width,i));
    }
    painter.end();

    painter.begin(m_pix);
    painter.drawImage(QPoint(m_startX,m_startY),m_image);
    painter.end();
}

void KeyEvent::keyPressEvent(QKeyEvent *event)
{
    //判断按下修饰键是否是ctrl,每次移动为一个像素位
    if(event->modifiers() == Qt::ControlModifier)
    {
        if(event->key() == Qt::Key_Left)
            m_startX=(m_startX - 1 ) < 0 ? m_startX : m_startX-1;
        if(event->key() == Qt::Key_Right)
            m_startX=(m_startX + 1 + m_image.width()) > m_width ? m_startX : m_startX+1;
        if(event->key() == Qt::Key_Up)
            m_startY=(m_startY - 1 ) < 0 ? m_startY : m_startY-1;
        if(event->key() == Qt::Key_Down)
            m_startY=(m_startY + 1 + m_image.height()) > m_height ? m_startY : m_startY+1;

    }else{//每次移动为一个步长
        //调整图标左上角位置到网格顶点上
        m_startX = m_startX - m_startX % m_step;
        m_startY = m_startY - m_startY % m_step;

        if(event->key() == Qt::Key_Left)
            m_startX=(m_startX - m_step ) < 0 ? m_startX : m_startX-m_step;
        if(event->key() == Qt::Key_Right)
            m_startX=(m_startX + m_step + m_image.width()) > m_width ? m_startX : m_startX+m_step;
        if(event->key() == Qt::Key_Up)
            m_startY=(m_startY - m_step ) < 0 ? m_startY : m_startY-m_step;
        if(event->key() == Qt::Key_Down)
            m_startY=(m_startY + m_step + m_image.height()) > m_height ? m_startY : m_startY+m_step;
    }

    drawPix();//根据调整后的位置重新在m_pix上绘制图形
    update();//重绘窗口
}

void KeyEvent::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.drawPixmap(QPoint(0,0),*m_pix);
    painter.end();
}

