#ifndef WEAPONMODEL_H
#define WEAPONMODEL_H
#include <QAbstractTableModel>

class WeaponModel : public QAbstractTableModel
{
public:
    WeaponModel(QObject *parent);

    virtual int rowCount(const QModelIndex &parent = QModelIndex());
    virtual int columnCount(const QModelIndex &parent = QModelIndex());
    QVariant data(const QModelIndex &index,int role)const;
    QVariant headerDate(int section,Qt::Orientation orientation,int role) const;

private:
    QVector<short> army;                //军队
    QVector<short> weaponType;          //武器类型
    QMap<short,QString> armyMap;        //军队映射
    QMap<short,QString> weaponMap;      //武器映射

    QStringList weapon;     //武器
    QStringList header;     //表头

    void populateModel();   //表格数据的初始化

};

#endif // WEAPONMODEL_H
