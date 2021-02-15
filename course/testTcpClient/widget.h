#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void onReadMessage();
    void onDisplayError(QAbstractSocket::SocketError);
    void on_connectButton_clicked();

    void on_sendButton_clicked();

private:
    Ui::Widget *ui;
    QTcpSocket *m_tcpSocket;
};
#endif // WIDGET_H
