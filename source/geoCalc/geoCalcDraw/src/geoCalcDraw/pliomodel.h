#ifndef PLIOMODEL_H
#define PLIOMODEL_H

#include <QAbstractItemModel>
#include "plionode.h"

class PLIOModel : public QAbstractItemModel
{
public:
    PLIOModel(QObject *parent = 0);
    ~PLIOModel();

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    PLIONode *nodeFromIndex(const QModelIndex &index) const;
    PLIONode *rootNode;
};

/*
class BooleanModel : public QAbstractItemModel
{
public:
    BooleanModel(QObject *parent = 0);
    ~BooleanModel();

    void setRootNode(Node *node);

    QModelIndex index(int row, int column,
                      const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role) const;
private:
    Node *nodeFromIndex(const QModelIndex &index) const;

    Node *rootNode;
};
*/
#endif // PLIOMODEL_H
