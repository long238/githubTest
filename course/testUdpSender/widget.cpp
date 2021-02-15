#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_sender = new QUdpSocket(this);

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    QByteArray dataGram = ui->lineEdit->text().toUtf8();
    m_sender->writeDatagram(dataGram.data(),dataGram.size(),QHostAddress::Broadcast,6666);
}
