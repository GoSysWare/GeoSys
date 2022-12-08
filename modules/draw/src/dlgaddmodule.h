#ifndef DLGADDMODULE_H
#define DLGADDMODULE_H

#include <QDialog>
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>

class DlgAddMod : public QDialog
{
    Q_OBJECT
public:
    DlgAddMod(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~DlgAddMod();
    QString modName;

    int indexEdit;

private slots:
    void ok(bool check);
    void cancel(bool Check);

private:
    QLabel *label;
    QLineEdit *textName;
    QDialogButtonBox *buttonBox;
    QVBoxLayout *layout;
};

#endif // DLGADDPROG_H
