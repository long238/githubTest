#include "myaction.h"
#include<QSplitter>
#include<QLabel>

MyAction::MyAction(QObject *parent):QWidgetAction(parent)
{
    lineEdit = new QLineEdit;
    connect(lineEdit,&QLineEdit::returnPressed,this,&MyAction::sendText);
}

QWidget *MyAction::createWidget(QWidget *parent)
{
    //判断父部件是否继承自菜单或者工具栏
    //如果是，则创建父部件的子部件并放回子部件
    if(parent->inherits("QMenu") || parent->inherits("QToolBar"))
    {
        QSplitter *splitter = new QSplitter(parent);
        QLabel *label = new QLabel("插入文本:");
        QSplitter *splitter2 = new QSplitter(parent);
        QLabel *label2 = new QLabel("文本:");
        splitter->addWidget(label);
        splitter->addWidget(lineEdit);
        splitter2->addWidget(label2);
        return splitter;
    }
    return 0;
}

void MyAction::sendText()
{
    emit getText(lineEdit->text());
    lineEdit->clear();

}
