#include "weaponmodel.h"

WeaponModel::WeaponModel(QObject *parent):QAbstractTableModel(parent)
{
    armyMap[1] = QString("空军");
    armyMap[2] = QString("海军");
    armyMap[3] = QString("陆军");
    armyMap[4] = QString("海军路战队");

    weaponMap[1] = QString("轰炸机");
    weaponMap[2] = QString("战斗机");
    weaponMap[3] = QString("航空母舰");
    weaponMap[4] = QString("驱逐舰");
    weaponMap[5] = QString("直升级");
    weaponMap[6] = QString("坦克");
    weaponMap[7] = QString("两栖攻击舰");
    weaponMap[8] = QString("两栖战车");

    populateModel();
}

int WeaponModel::rowCount(const QModelIndex &parent)
{
    return army.size();
}

int WeaponModel::columnCount(const QModelIndex &parent)
{
    return 3;
}

//返回指定的数据，将数据映射成文字
QVariant WeaponModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole)
    {
        switch(index.column())
        {
        case 0:
            return armyMap[army[index.row()]];
            break;
        case 1:
            return weaponMap[weaponType[index.row()]];
            break;
        case 2:
            return weapon[index.row()];
            break;
        default:
            return QVariant();

        }
    }
    return QVariant();
}

QVariant WeaponModel::headerDate(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        return header[section];
    }

    return QAbstractTableModel::headerData(section,orientation,role);
}

void WeaponModel::populateModel()
{
    header << QString("军种") << QString("种类") << QString("武器");
    army << 1 << 2 << 3 << 4 << 2 << 4 << 3 << 1;
    weaponType << 1 << 3 << 5 << 7 << 4 << 8 << 6 << 2;
    weapon << QString("B-2") <<QString("dd") << QString("阿帕奇") << QString("黄蜂级")
           << QString("比例帕克级") << QString("AAAV") << QString("M1A1") << QString("F-22");
}


