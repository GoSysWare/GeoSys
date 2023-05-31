#ifndef EVDATAPANEL_H
#define EVDATAPANEL_H

#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <QBoxLayout>
#include <QByteArray>

#include "plevdata.h"

class TableEVData : public QTableView
{
public:
    TableEVData();
    bool setSelect();
};

class EVDataPanel : public QWidget
{
    Q_OBJECT
public:
    EVDataPanel();
    void updateState();

private slots:
    void addEVData(bool check);
    void editEVData(bool check);
    void removeEVData(bool check);
    void tableDoubleClicked(const QModelIndex & index);
    void showEVData(bool check);
private:
    TableEVData *tableData;
    QPushButton *buttonAddData;
    QPushButton *buttonEditData;
    QPushButton *buttonRemoveData;
    QHBoxLayout *layoutButton;
    QVBoxLayout *layout;
    PLEVData evLast;
};

#endif // EVDATAPANEL_H
