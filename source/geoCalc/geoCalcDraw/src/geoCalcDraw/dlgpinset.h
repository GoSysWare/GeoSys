#ifndef DLGPINSET_H
#define DLGPINSET_H

#include <QDialog>
#include <QRadioButton>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QTableView>
#include <QBoxLayout>
#include "plevdata.h"

class TableEVView : public QTableView
{
public:
    TableEVView();

private:
    QDialog *dlgParent;
};

class DlgPinSet : public QDialog
{
    Q_OBJECT
public:
    DlgPinSet(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~DlgPinSet();
    void exchangeValue(QString &constValue, PLEVData &ev, bool &isConst, bool isInput, bool set);

private slots:
    void ok(bool check);
    void cancel(bool Check);
    void tableDoubleClicked(const QModelIndex & index);
    void tableClicked(const QModelIndex & index);
    void onConst(bool check);
    void onVariable(bool check);

private:
    QRadioButton *rbConst;
    QRadioButton *rbVariable;
    QLineEdit *textConst;
    QLineEdit *textVariable;
    QDialogButtonBox *buttonBox;
    TableEVView *tableView;
    QGridLayout *layout;

    PLEVData evData;
};

#endif // DLGPINSET_H
