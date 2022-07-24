#include <QMessageBox>
#include "dlgipaddress.h"

DlgIPAddress::DlgIPAddress(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f)
{
    setWindowTitle(tr("Target IP address"));
    label = new QLabel(tr("IP Address:"));
    textIP = new QLineEdit;
    textIP->setInputMask("000.000.000.000");
    buttonBox = new QDialogButtonBox;
    QPushButton *buttonOk = buttonBox->addButton(QDialogButtonBox::Ok);
    QPushButton *buttonCancel = buttonBox->addButton(QDialogButtonBox::Cancel);
    layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(textIP);
    layout->addWidget(buttonBox);
    setLayout(layout);

    connect(buttonOk, SIGNAL(clicked(bool)), this, SLOT(ok(bool)));
    connect(buttonCancel, SIGNAL(clicked(bool)), this, SLOT(cancel(bool)));
}

DlgIPAddress::~DlgIPAddress()
{

}

void DlgIPAddress::setIP(QString ip)
{
    textIP->setText(ip);
}

QString DlgIPAddress::getIP()
{
    return textIP->text();
}

void DlgIPAddress::ok(bool check)
{
    QString ip = textIP->text();
    QStringList list = ip.split(".");
    QString v;
    for(int i=0; i<4; i++){
        v = list.at(i);
        if(v.isEmpty() || v.toInt()>254){
            QMessageBox::warning(this, "Warining", tr("IP Address invalid"));
            return;
        }
    }


    accept();

}

void DlgIPAddress::cancel(bool Check)
{
    reject();
}
