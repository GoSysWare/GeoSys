#ifndef DLGADDPROG_H
#define DLGADDPROG_H

#include <QDialog>
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>

class DlgAddProg : public QDialog
{
    Q_OBJECT
public:
    DlgAddProg(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~DlgAddProg();
    QString prgName;
    QString prgDesc;
    int prgType;
    int indexEdit;
    int interval;

private slots:
    void ok(bool check);
    void cancel(bool Check);

private:
    QLabel *lblProgNmae;
    QLineEdit * txtProgName;
    QLabel *lblInterval;
    QLineEdit *txtInterval;
    QDialogButtonBox *buttonBox;
    QVBoxLayout *layout;
};

#endif // DLGADDPROG_H
