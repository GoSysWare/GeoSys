#ifndef DLGIPADDRESS_H
#define DLGIPADDRESS_H

#include <QDialog>
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>

class DlgIPAddress : public QDialog
{
    Q_OBJECT
public:
    DlgIPAddress(QWidget *parent = 0, Qt::WindowFlags f=0);
    ~DlgIPAddress();
    void setIP(QString ip);
    QString getIP();

private slots:
    void ok(bool check);
    void cancel(bool Check);

private:
    QLabel *label;
    QLineEdit *textIP;
    QDialogButtonBox *buttonBox;
    QVBoxLayout *layout;
};

#endif // DLGIPADDRESS_H
