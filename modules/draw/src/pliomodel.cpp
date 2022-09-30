#include "gdefine.h"
#include "pliomodel.h"
#include "k_config.h"
#include "k_io.h"

PLIOModel::PLIOModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    rootNode = new PLIONode(PLIONode::Root, -1, -1);

    PLIONode *nodeStation, *nodeModule;
    int i, j;
    for(i=0; i<IOSTATIONCOUNT; i++){
        nodeStation = new PLIONode(PLIONode::Station, i, -1);
        rootNode->children.append(nodeStation);
        nodeStation->parent = rootNode;
        for(j=0; j<IOCELLCOUNT; j++){
            nodeModule = new PLIONode(PLIONode::Module, i, j);
            nodeStation->children.append(nodeModule);
            nodeModule->parent = nodeStation;
        }
    }

}

PLIOModel::~PLIOModel()
{
    delete rootNode;
}

QModelIndex PLIOModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!rootNode || row < 0 || column < 0){
        return QModelIndex();
    }

    PLIONode *parentNode = nodeFromIndex(parent);
    PLIONode *childNode = parentNode->children.value(row);
    if (!childNode){
        return QModelIndex();
    }

    return createIndex(row, column, childNode);
}

QModelIndex PLIOModel::parent(const QModelIndex &child) const
{

    PLIONode *node = nodeFromIndex(child);
    if (!node){
        return QModelIndex();
    }
    PLIONode *parentNode = node->parent;
    if (!parentNode){
        return QModelIndex();
    }
    PLIONode *grandparentNode = parentNode->parent;
    if (!grandparentNode){
        return QModelIndex();
    }

    int row = grandparentNode->children.indexOf(parentNode);
    return createIndex(row, 0, parentNode);
}

int PLIOModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0){
        return 0;
    }
    PLIONode *parentNode = nodeFromIndex(parent);
    if (!parentNode){
        return 0;
    }
    return parentNode->children.count();
}

int PLIOModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant PLIOModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole){
        return QVariant();
    }

    PLIONode *node = nodeFromIndex(index);
    if (!node){
        return QVariant();
    }

    iocell_t *cellIn, *cellOut;
    if(node->idStation >=0 && node->idModule >=0){
//        cellIn = io_getcellin(node->idStation, node->idModule);
//        cellOut = io_getcellout(node->idStation, node->idModule);
    }
    QString str, str1;
    char temp[128];
    int i;
    if(index.column() == 0){
        switch (node->type) {
        case PLIONode::Station:
            str = QString::asprintf("Station %2d", node->idStation);
            break;
        case PLIONode::Module:
            str= QString::asprintf("Module %2d", node->idModule);
            break;
        default:
            str = "Unknown";
        }
        return str;
    }else if (index.column() == 1){
        if(!gTarget->isMonitor()){
            return QVariant();
        }
        if(node->type != PLIONode::Module){
            return QVariant();
        }
        memset(temp, 0, sizeof(temp));
        for(i=0; i<IOIDSIZE; i++){
            if(cellOut->id[i] != 0){
                temp[i] = cellOut->id[i];
            }else{
                temp[i] = '-';
            }
        }
        str  += QString(temp);
        str  += " | ";
        memset(temp, 0, sizeof(temp));
        for(i=0; i<IOIDSIZE; i++){
            if(cellIn->id[i] != 0){
                temp[i] = cellIn->id[i];
            }else{
                temp[i] = '-';
            }
        }
        str  += QString(temp);
        return str;

    }else if (index.column() == 2){
        if(!gTarget->isMonitor()){
            return QVariant();
        }
        if(node->type != PLIONode::Module){
            return QVariant();
        }
        for(i=0; i<IODATASIZE; i++){
            str1 = QString::asprintf("%02X", (unsigned char)cellIn->data[i]);
            str += str1;
            if(i%2 && i!=(IODATASIZE-1)){
                str += " ";
            }
        }
        return str;
    }else if (index.column() == 3){
        if(!gTarget->isMonitor()){
            return QVariant();
        }
        if(node->type != PLIONode::Module){
            return QVariant();
        }
        for(i=0; i<IODATASIZE; i++){
            str1 = QString::asprintf("%02X", (unsigned char)cellOut->data[i]);
            str += str1;
            if(i%2 && i!=(IODATASIZE-1)){
                str += " ";
            }
        }
        return str;
    }

    return QVariant();
}

QVariant PLIOModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch(section){
        case 0:
            return tr("Station / Module");
        case 1:
            return tr("Id ( config | target )");
        case 2:
            return tr("Input");
        case 3:
            return tr("Output");
        default:
            return QVariant();
        }
    }

    return QVariant();
}


PLIONode *PLIOModel::nodeFromIndex(const QModelIndex &index) const
{
    if (index.isValid()) {
        return static_cast<PLIONode *>(index.internalPointer());
    } else {
        return rootNode;
    }
}

