#include "mouseevent.h"
#include "ui_mouseevent.h"
#include <QMouseEvent>
#include <QMessageBox>

MouseEvent::MouseEvent(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MouseEvent)
{
    ui->setupUi(this);
    setWindowTitle(QString("鼠标事件"));

    m_statuslabel = new QLabel(QString("当前位置:"));
    m_statuslabel->setFixedWidth(100);

    m_posLabel = new QLabel(QString(""));
    m_posLabel->setFixedWidth(100);

    statusBar()->addPermanentWidget(m_statuslabel);
    statusBar()->addPermanentWidget(m_posLabel);
    resize(400,200);

    this->setCentralWidget(ui->centralwidget);
    ui->centralwidget->setMouseTracking(true);
}

MouseEvent::~MouseEvent()
{
    delete ui;
}

void MouseEvent::mousePressEvent(QMouseEvent *e)
{
    QString str = "(" + QString::number(e->x()) + "," + QString::number(e->y()) + ")";
    if(e->button() == Qt::LeftButton){
        //QMessageBox::information(NULL,"左键:",str);
        statusBar()->showMessage("左键:"+str);//状态栏的提示信息
    } else if(e->button() == Qt::MidButton){
        //QMessageBox::information(NULL,"中键:",str);
        statusBar()->showMessage("中键:"+str);
    } else if(e->button() == Qt::RightButton){
        //QMessageBox::information(NULL,"右键:",str);
        statusBar()->showMessage("右键:"+str);
    }
    e->accept();

}

void MouseEvent::mouseMoveEvent(QMouseEvent *e)
{
    //this->setcentralWidget(true);
    //ui->centralWidget->setcentralWidget(true);
    QString posStr = "(" + QString::number(e->x()) + "," + QString::number(e->y()) + ")";
    m_posLabel->setText(posStr);

}

void MouseEvent::mouseReleaseEvent(QMouseEvent *e)
{
    QString str = "(" + QString::number(e->x()) + "," + QString::number(e->y()) + ")";
    statusBar()->showMessage(QString("释放在:")+str,3000);
}

