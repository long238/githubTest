#include <QApplication>
#include "weaponmodel.h"
#include <QTableView>

int main(int argc,char* argv[])
{
    QApplication a(argc,argv);

    WeaponModel  model;
    QTableView view;
    view.setModel(&model);
    view.setWindowTitle(QString("表格视图"));
    view.resize(600,400);
    view.show();

    return a.exec();
}
