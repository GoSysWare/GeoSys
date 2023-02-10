//#include <QValidator>
#include <QMessageBox>
#include "dlgaddprog.h"
#include "gdefine.h"

DlgAddProg::DlgAddProg(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f)
{
    setWindowTitle(tr("Add program"));

    lblProgNmae = new QLabel(tr("Program name:"));
    txtProgName = new QLineEdit;

    lblInterval = new QLabel(tr("Interval"));
    txtInterval = new QLineEdit;

    txtProgName->setMaxLength(15);

    buttonBox = new QDialogButtonBox;
    QPushButton *buttonOk = buttonBox->addButton(QDialogButtonBox::Ok);
    QPushButton *buttonCancel = buttonBox->addButton(QDialogButtonBox::Cancel);
    layout = new QVBoxLayout;
    layout->addWidget(lblProgNmae);
    layout->addWidget(txtProgName);
    layout->addWidget(lblInterval);
    layout->addWidget(txtInterval);
    layout->addWidget(buttonBox);
    setLayout(layout);

    connect(buttonOk, SIGNAL(clicked(bool)), this, SLOT(ok(bool)));
    connect(buttonCancel, SIGNAL(clicked(bool)), this, SLOT(cancel(bool)));

    indexEdit = -1;
    prgType =  -1;
}

DlgAddProg::~DlgAddProg()
{
    delete lblProgNmae;
    delete txtProgName;
    delete lblInterval;
    delete txtInterval;
    delete buttonBox;
    delete layout;
}

void DlgAddProg::ok(bool check)
{
    prgName = txtProgName->text();
  

    if(prgName.isEmpty()){
        return;
    }
    if(txtInterval->text().isEmpty()){
        interval = 1000;
    }else{
        interval = txtInterval->text().toInt();
    }
    if(prgName.indexOf(";") != -1){
        QMessageBox::warning(this, "Warining", tr("Program name can't contains ';'"));
        return;
    }
    for(int m = 0; m < gMainModel->modList.size(); m++){
        PLModule * mod = &gMainModel->modList[m];
        for(int i=0; i< mod->prgList.size(); i++){
            if(mod->prgList.at(i).name == prgName && i!=indexEdit){
                QString msg = "Program '";
                msg += prgName;
                msg += "' already exist";
                QMessageBox::warning(this, "Warining", msg);
                return;
            }
        }
    }


    accept();
}

void DlgAddProg::cancel(bool Check)
{
    reject();
}
