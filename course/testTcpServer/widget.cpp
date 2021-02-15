#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_tcpServer = new QTcpServer(this);

    //监听客户端发来的请求
    if(m_tcpServer->listen(QHostAddress::Any,8888))
    {
        qDebug()<<m_tcpServer->errorString();
        close();
    }

    connect(m_tcpServer,&QTcpServer::newConnection,this,&Widget::onNewConnect);

    connect(m_tcpServer,&QTcpServer::newConnection,this,&Widget::onSendMessage);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onNewConnect()
{
    //当前连接来的客户端
    m_tcpSocket = m_tcpServer->nextPendingConnection();

    //断开连接
    connect(m_tcpSocket,&QTcpSocket::disconnected,m_tcpSocket,&QTcpSocket::deleteLater);

    //socket有数据时则会发射readyRead信号
    connect(m_tcpSocket,&QTcpSocket::readyRead,this,&Widget::onReadMessage);

}

void Widget::onSendMessage()
{
    QString str = "你好，客户端";

    m_tcpSocket->write(str.toUtf8());
    ui->label->setText("发送信息成功");
}

void Widget::onReadMessage()
{
    QByteArray bt = m_tcpSocket->readAll();
    ui->readLabel->setText(bt);
}
























