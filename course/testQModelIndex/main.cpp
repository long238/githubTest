#include <QApplication>
#include <QTreeView>
#include <QStandardItemModel>
#include <QDebug>
#pragma execution_character_set("utf-8")
int main(int argc,char* argv[])
{
    QApplication a(argc,argv);

    //创建标准项模型
    QStandardItemModel model;

    //获取标准项模型的根项，根项是不可见的
    QStandardItem* parentItem = model.invisibleRootItem();

    //创建标准项item0
    QStandardItem *item0 = new QStandardItem;
    item0->setText(QString("A"));

    QPixmap pixmap0(50,50);
    pixmap0.fill(Qt::red);
    item0->setIcon(pixmap0);
    //设置工具提示
    item0->setToolTip(QString("A项"));


    QStandardItem *item4 = new QStandardItem;
    item4->setText(QString("D"));

    QPixmap pixmap4(50,50);
    pixmap4.fill(Qt::red);

    item4->setIcon(pixmap4);
    //将item0作为父项的子项
    parentItem->appendRow(item0);
    parentItem->appendRow(item4);
    parentItem = item0;

    //创建item0的子项
    QStandardItem *item1 = new QStandardItem;
    item1->setText(QString("B"));

    QPixmap pixmap1(50,50);
    pixmap1.fill(Qt::blue);

    item1->setIcon(pixmap1);
    item1->setToolTip(QString("B项"));

    parentItem->appendRow(item1);

    QStandardItem *item2 = new QStandardItem;
    QPixmap pixmap2(50,50);
    pixmap2.fill(Qt::green);

    item2->setData("C",Qt::EditRole);
    item2->setData("indexC",Qt::ToolTipRole);
    item2->setData(QIcon(pixmap2),Qt::DecorationRole);
    item2->setData("dsfsd",Qt::UserRole);


    parentItem->appendRow(item2);

    //在树视图中显示
    QTreeView view;
    view.setModel(&model);
    view.show();

    QModelIndex indexA = model.index(0,0,QModelIndex());
    qDebug() << "indexA row coutm:"
             <<model.rowCount(indexA);

    QModelIndex indexB = model.index(0,0,indexA);
    qDebug() << "indexB row coutm:"
             <<model.data(indexB,Qt::EditRole).toString();
    qDebug() << "indexB tooltip:"
             <<model.data(indexB,Qt::ToolTipRole).toString();

    QModelIndex indexC = model.index(1,0,indexA);
    qDebug() << "indexC row coutm:"
             <<model.data(indexC,Qt::EditRole).toString();
    qDebug() << "indexC tooltip:"
             <<model.data(indexC,Qt::ToolTipRole).toString();
    qDebug() << "indexC UserRolr:"
             <<model.data(indexC,Qt::UserRole).toString();



    return a.exec();

}




