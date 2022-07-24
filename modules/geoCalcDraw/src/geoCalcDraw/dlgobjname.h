#ifndef DLGOBJNAME_H
#define DLGOBJNAME_H

#include <QDialog>
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>

class DlgObjName : public QDialog
{
    Q_OBJECT
public:
    DlgObjName(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~DlgObjName();
    void setTitle(QString title);
    void setName(QString name);
    QString getName();

private slots:
    void ok(bool check);
    void cancel(bool Check);

private:
    QLabel *label;
    QLineEdit *textName;
    QDialogButtonBox *buttonBox;
    QVBoxLayout *layout;
};

#endif // DLGOBJNAME_H
