#include <QMessageBox>
#include "dlgevdata.h"
#include "gdefine.h"

DlgEVData::DlgEVData(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f)
{
    setWindowTitle(tr("Variable property"));

    labelName = new QLabel(tr("Name"));
    labelType = new QLabel(tr("Type"));
    labelValue = new QLabel(tr("Value"));
    labelComment = new QLabel(tr("Comment"));
    textName = new QLineEdit;
    textName->setMaxLength(32);
    listType = new QListWidget;
    listType->addItem(tr("BOOL"));
    listType->addItem(tr("INT"));
    listType->addItem(tr("REAL"));
    listType->addItem(tr("LREAL"));
    listType->addItem(tr("TIME"));
    listType->setMaximumHeight(120);
    listType->setBatchSize(5);
    textValue = new QLineEdit;
    textValue->setMaxLength(32);
    //textValue->setInputMask("################################");
    textComment = new QLineEdit;
    textComment->setMaxLength(32);
    buttonBox = new QDialogButtonBox;
    QPushButton *buttonOk = buttonBox->addButton(QDialogButtonBox::Ok);
    QPushButton *buttonCancel = buttonBox->addButton(QDialogButtonBox::Cancel);
    layout = new QGridLayout;
    layout->addWidget(labelName, 0, 0);
    layout->addWidget(labelType, 1, 0, Qt::AlignTop);
    layout->addWidget(labelValue, 2, 0);
    layout->addWidget(labelComment, 3, 0);
    layout->addWidget(textName, 0, 1);
    layout->addWidget(listType, 1, 1);
    layout->addWidget(textValue, 2, 1);
    layout->addWidget(textComment, 3, 1);
    layout->addWidget(buttonBox, 5, 1);
    setLayout(layout);

    connect(buttonOk, SIGNAL(clicked(bool)), this, SLOT(ok(bool)));
    connect(buttonCancel, SIGNAL(clicked(bool)), this, SLOT(cancel(bool)));
}

DlgEVData::~DlgEVData(){

}

void DlgEVData::ok(bool check)
{
    QString name = textName->text();
    if(name.isEmpty()){
        QMessageBox::warning(this, tr("Warning"), tr("Name is empty"));
        return;
    }

    if(name.indexOf(",") != -1){
        QMessageBox::warning(this, "Warining", tr("Name can't contains ','"));
        return;
    }

    if(name.indexOf(";") != -1){
        QMessageBox::warning(this, "Warining", tr("Name can't contains ';'"));
        return;
    }

    if(mode == 0){
        for(int i=0; i<gMainModel->evList.size(); i++){
            if(gMainModel->evList.at(i).name == name){
                QString msg = "Variable '";
                msg += name;
                msg += "' already exist";
                QMessageBox::warning(this, "Warining", msg);
                return;
            }
        }
    }

    accept();
}

void DlgEVData::cancel(bool Check)
{
    reject();
}

void DlgEVData::setValue(PLEVData &ev, int m)
{
    mode = m;
    if(mode != 0){
        listType->setEnabled(false);
    }

    textName->setText(ev.name);
    textComment->setText(ev.comment);
    switch(ev.initValue.t){
    case T_BOOL:
        listType->setCurrentRow(0);
        break;
    case T_INT:
        listType->setCurrentRow(1);
        break;
    case T_REAL:
        listType->setCurrentRow(2);
        break;
    case T_LREAL:
        listType->setCurrentRow(3);
        break;
    case T_TIME:
        listType->setCurrentRow(4);
        break;
    default:
        QMessageBox::critical(this, "Error", "Unknown data type");
    }
    char value[128];
    var2str(value, ev.initValue, ev.initValue.t);
    textValue->setText(QString(value));
}

void DlgEVData::getValue(PLEVData &ev)
{
    ev.name = textName->text();
    ev.comment = textComment->text();
    switch(listType->currentIndex().row()){
    case 0:
        ev.initValue.t = T_BOOL;
        break;
    case 1:
        ev.initValue.t = T_INT;
        break;
    case 2:
        ev.initValue.t = T_REAL;
        break;
    case 3:
        ev.initValue.t = T_LREAL;
        break;
    case 4:
        ev.initValue.t = T_TIME;
        break;
    default:
        ;
    }
    char value[128];
    strcpy(value, textValue->text().toStdString().c_str());
    str2var(value, &ev.initValue, ev.initValue.t);
}
