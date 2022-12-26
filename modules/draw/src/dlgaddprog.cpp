//#include <QValidator>
#include <QMessageBox>
#include "dlgaddprog.h"
#include "gdefine.h"

DlgAddProg::DlgAddProg(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f)
{
    setWindowTitle(tr("Add program"));

    label = new QLabel(tr("Program name:"));
    textName = new QLineEdit;
    //QRegExp rx("-?\\d{1,3}");
    //QValidator *validator = new QRegExpValidator(rx, this);
    //textName->setValidator(validator);
    textName->setMaxLength(15);
    //textName->setInputMask("nnnnnnnnnnnnnnn");
    buttonBox = new QDialogButtonBox;
    QPushButton *buttonOk = buttonBox->addButton(QDialogButtonBox::Ok);
    QPushButton *buttonCancel = buttonBox->addButton(QDialogButtonBox::Cancel);
    layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(textName);
    layout->addWidget(buttonBox);
    setLayout(layout);

    connect(buttonOk, SIGNAL(clicked(bool)), this, SLOT(ok(bool)));
    connect(buttonCancel, SIGNAL(clicked(bool)), this, SLOT(cancel(bool)));

    indexEdit = -1;
    prgType =  -1;
}

DlgAddProg::~DlgAddProg()
{
    delete label;
    delete textName;
    delete buttonBox;
    delete layout;
}

void DlgAddProg::ok(bool check)
{
    prgName = textName->text();

    if(prgName.isEmpty()){
        return;
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
