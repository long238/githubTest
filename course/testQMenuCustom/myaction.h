#ifndef MYACTION_H
#define MYACTION_H
#pragma execution_character_set("utf-8")
#include<QWidgetAction>
#include<QLineEdit>

class MyAction : public QWidgetAction
{
    Q_OBJECT
public:
    MyAction(QObject *parent = 0);

protected:
    //重载父类的虚函数，跟重载鼠标事件一样
    QWidget* createWidget(QWidget *parent);

signals:
    void getText(const QString &string);

private slots:
    void sendText();

private:
    QLineEdit *lineEdit;
};

#endif // MYACTION_H
