#ifndef EVDATAMODEL_H
#define EVDATAMODEL_H

#include <QDebug>
#include <QAbstractTableModel>
#include <QList>
#include "plevdata.h"

class EVDataModel : public QAbstractTableModel
{
public:
    EVDataModel(QObject *parent = 0);
    void beginReset();
    void endReset();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role) const;
};

#endif // EVDATAMODEL_H
