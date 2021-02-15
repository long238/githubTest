#include "widget.h"
#include "ui_widget.h"
#include <QTreeWidget>
#include <QTreeWidgetItem>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->treeWidget->setColumnCount(2);

    QStringList m_Header;

    m_Header <<QString("学号")<<QString("年龄");

    //ui->treeWidget->setHeaderLabels(m_Header);
    //ui->treeWidget->header()->setVisible(false);

    QStringList zhangsan;

    zhangsan<<QString("张三");

    QTreeWidgetItem *zhangsanroot = new QTreeWidgetItem(ui->treeWidget,zhangsan);
    QStringList zhangsanContent;
    zhangsanContent<<QString("dssd")<<QString("54");
    QTreeWidgetItem *p = new QTreeWidgetItem(zhangsanContent);
    zhangsanroot->addChild(p);

    zhangsan.clear();
    zhangsan<<QString("guo");
    QTreeWidgetItem *zhangsanroot2 = new QTreeWidgetItem(zhangsan);
    zhangsanroot2->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
    ui->treeWidget->insertTopLevelItem(0,zhangsanroot2);
}

Widget::~Widget()
{
    delete ui;
}

