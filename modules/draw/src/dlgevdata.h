#ifndef DLGEVDATA_H
#define DLGEVDATA_H

#include <QDialog>
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QDialogButtonBox>
#include <QListWidget>
#include <QLayout>
#include "plevdata.h"

class DlgEVData : public QDialog
{
    Q_OBJECT
public:
    DlgEVData(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~DlgEVData();
    void setValue(PLEVData &ev, int m = 0);
    void getValue(PLEVData &ev);

private slots:
    void ok(bool check);
    void cancel(bool Check);

private:
    QLabel *labelName;
    QLabel *labelType;
    QLabel *labelValue;
    QLabel *labelComment;
    QLineEdit *textName;
    QListWidget *listType;
    QTextEdit *textValue;
    QLineEdit *textComment;
    QDialogButtonBox *buttonBox;
    QGridLayout *layout;
    int mode;
};

#endif // DLGEVDATA_H
