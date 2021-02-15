#include "widget.h"
#include "ui_widget.h"

const int gTcpPort = 8888;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_tcpSocket = new QTcpSocket(this);

    //socket有数据来了，做处理
    connect(m_tcpSocket,&QTcpSocket::readyRead,this,&Widget::onReadMessage);

    connect(m_tcpSocket,SIGNAL(QAbstractSocket::SocketError),this,SLOT(onDisplayError(QAbstractSocket::SpcketError)));

    ui->hostLineEdit->setText("127.0.0.1");
    ui->portLineEdit->setText(QString::number(gTcpPort));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::onReadMessage()
{
    QByteArray bt;
    bt.resize(m_tcpSocket->bytesAvailable());
    m_tcpSocket->read(bt.data(),bt.size());

    ui->messageLabel->setText(bt);

}

void Widget::onDisplayError(QAbstractSocket::SocketError e)
{
    qDebug() << "SocketError:" << e <<endl << m_tcpSocket->errorString();
}

void Widget::on_connectButton_clicked()
{
    m_tcpSocket->abort();

    m_tcpSocket->connectToHost(ui->hostLineEdit->text(),ui->portLineEdit->text().toInt());
}

void Widget::on_sendButton_clicked()
{
    m_tcpSocket->write(ui->sendButton->text().toUtf8());
    m_tcpSocket->flush();
}
