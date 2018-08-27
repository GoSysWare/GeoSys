#include "evdatamodel.h"
#include "gdefine.h"

EVDataModel::EVDataModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

void EVDataModel::beginReset()
{
    beginResetModel();
    //qDebug() << "begin reset";
}

void EVDataModel::endReset()
{
    endResetModel();
    //qDebug() << "end reset";
}

int EVDataModel::rowCount(const QModelIndex &parent) const
{
    return gMainModel->evList.size();
}

int EVDataModel::columnCount(const QModelIndex &parent) const
{
    return 6;
}

QVariant EVDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole){
        return QVariant();
    }

    if(orientation == Qt::Vertical){
        return section + 1;
    }

    switch(section){
    case 0:
        return tr("Name");
        break;
    case 1:
        return tr("Type");
        break;
    case 2:
        return tr("Comment");
        break;
    case 3:
        return tr("Initial value");
        break;
    case 4:
        return tr("Current Value");
        break;
    case 5:
        return tr("Refrence");
        break;
    default:
        return QVariant();
    }
}

QVariant EVDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()){
        return QVariant();
    }

    if (role == Qt::TextAlignmentRole) {
        switch(index.column()){
        case 0:
            return int(Qt::AlignLeft | Qt::AlignVCenter);
        case 1:
            return int(Qt::AlignLeft | Qt::AlignVCenter);
        case 2:
            return int(Qt::AlignLeft | Qt::AlignVCenter);
        case 3:
            return int(Qt::AlignRight | Qt::AlignVCenter);
        case 4:
            return int(Qt::AlignRight | Qt::AlignVCenter);
        case 5:
            return int(Qt::AlignLeft | Qt::AlignVCenter);
        default:
            return QVariant();
        }
    } else if (role == Qt::DisplayRole) {
        PLEVData ev = gMainModel->evList.at(index.row());
        char type[128], value[128];
        type2str(type, ev.initValue.t);
        var2str(value, ev.initValue.v, ev.value.t);
        QString sType = type;
        QString sInitValue = value;
        var2str(value, ev.value.v, ev.value.t);
        QString sValue = value;
        QString sRef;
        sRef.sprintf("In:%d / Out:%d", ev.refIn, ev.refOut);
        switch(index.column()){
        case 0:
            return ev.name;
        case 1:
            return sType;
        case 2:
            return ev.comment;
        case 3:
            return sInitValue;
        case 4:
            return sValue;
        case 5:
            return sRef;
        default:
            return QVariant();
        }
    }

    return QVariant();
}
