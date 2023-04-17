#include "dlgpinset.h"
#include "dlgevdata.h"
#include <QMessageBox>
#include "gdefine.h"




TableEVView::TableEVView()
{
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
}

DlgPinSet::DlgPinSet(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f)
{
    setWindowTitle(tr("Pin set"));

    rbConst = new QRadioButton(tr("Const"));
    rbVariable = new QRadioButton(tr("Variable"));
    textConst = new QLineEdit;
    textConst->setMaxLength(1024);
    textVariable = new QLineEdit;
    textVariable->setMaxLength(32);
    buttonBox = new QDialogButtonBox;
    QPushButton *buttonOk = buttonBox->addButton(QDialogButtonBox::Ok);
    QPushButton *buttonCancel = buttonBox->addButton(QDialogButtonBox::Cancel);
    tableView = new TableEVView;
    //tableView->setMinimumWidth(640);
    //tableView->setMinimumHeight(320);
    tableView->setModel(&gMainModel->modelEVData);
    tableView->setColumnHidden(2, true);
    tableView->setColumnHidden(4, true);
    tableView->setColumnHidden(5, true);
    layout = new QGridLayout;

    layout->addWidget(rbConst, 0, 0);
    layout->addWidget(textConst, 0, 1);
    layout->addWidget(rbVariable, 1, 0);
    layout->addWidget(textVariable, 1, 1);
    layout->addWidget(buttonBox, 0, 2);
    layout->addWidget(tableView, 2, 0, 2, 3);
    setLayout(layout);

    connect(buttonOk, SIGNAL(clicked(bool)), this, SLOT(ok(bool)));
    connect(buttonCancel, SIGNAL(clicked(bool)), this, SLOT(cancel(bool)));
    connect(tableView, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(tableDoubleClicked(const QModelIndex &)));
    connect(tableView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(tableClicked(const QModelIndex &)));
    connect(rbConst, SIGNAL(clicked(bool)), this, SLOT(onConst(bool)));
    connect(rbVariable, SIGNAL(clicked(bool)), this, SLOT(onVariable(bool)));
}

DlgPinSet::~DlgPinSet()
{

}

void DlgPinSet::exchangeValue(QString &constValue, PLEVData &ev, bool &isConst, bool isInput, bool set)
{
    if(set){
        evData = ev;
        if(isInput){
            if(isConst){
                rbConst->setChecked(true);
                textConst->setText(constValue);
                textVariable->setEnabled(false);
                textConst->setFocus();
                textConst->selectAll();
            }else{
                rbVariable->setChecked(true);
                textVariable->setText(ev.name);
                textConst->setEnabled(false);
                textVariable->setFocus();
                textVariable->selectAll();
            }
        }else{
            rbVariable->setChecked(true);
            rbConst->setEnabled(false);
            textConst->setEnabled(false);
            textVariable->setFocus();
            textVariable->selectAll();
        }
    }else{
        ev = evData;
        if(rbConst->isChecked()){
            isConst = true;
            constValue = textConst->text();
        }else{
            isConst = false;
        }
    }
}

void DlgPinSet::ok(bool check)
{
    if(rbConst->isChecked()){
        if(textConst->text().isEmpty()){
            QMessageBox::warning(this, tr("Warning"), tr("Const is empty"));
            return;
        }else{
            accept();
            return;
        }
    }

    if(textVariable->text().isEmpty()){
        QMessageBox::warning(this, tr("Warning"), tr("Variable is empty"));
        return;
    }
    for(int i=0; i<gMainModel->evList.size(); i++){
        if(gMainModel->evList.at(i).name == textVariable->text()){
            if(evData.initValue.v().t() == gMainModel->evList.at(i).initValue.v().t()){
                evData = gMainModel->evList.at(i);
                accept();
                return;
            }else{
                QMessageBox::critical(this, tr("Error"), tr("Data type mismatch"));
                return;
            }
        }
    }
    DlgEVData dlgEVData(this);
    evData.name = textVariable->text();
    switch(evData.initValue.v().t()){
    case T_BOOL:
        evData.initValue.mutable_v()->set_b(0);
        break;
    case T_INT32:
        evData.initValue.mutable_v()->set_i(0);
        break;
    case T_UINT32:
        evData.initValue.mutable_v()->set_ui(0);
        break;
    case T_INT64:
        evData.initValue.mutable_v()->set_ll(0);
        break;
    case T_UINT64:
        evData.initValue.mutable_v()->set_ull(0);
        break;
    case T_FLOAT32:
        evData.initValue.mutable_v()->set_f(0);
        break;
    case T_FLOAT64:
        evData.initValue.mutable_v()->set_d(0);
        break;
    case T_TIME:
        evData.initValue.mutable_v()->set_ull(0);
        break;
    case T_STRING:
        evData.initValue.mutable_v()->set_str("");
        break;
    default:
        QMessageBox::critical(this, "Error", "Unknown data type");
    }
    dlgEVData.setValue(evData, 1);
    if(dlgEVData.exec() != QDialog::Accepted){
        return;
    }
    dlgEVData.getValue(evData);

    gMainModel->modelEVData.beginReset();
    PLCommand cmd;
    gMainModel->makeEvNewCmd(cmd, evData);
    if(!gMainModel->exeCommand(cmd)){
         QMessageBox::critical(this, "Error", QString::fromStdString(cmd.editInfo.ShortDebugString()));
        gMainModel->modelEVData.endReset();
        return;
    }
    gMainModel->modelEVData.endReset();
    accept();
}

void DlgPinSet::cancel(bool Check)
{
    reject();
}

void DlgPinSet::tableDoubleClicked(const QModelIndex &index)
{
    int row = index.row();
    if(gMainModel->evList.at(row).initValue.v().t() == evData.initValue.v().t()){
        rbVariable->setChecked(true);
        evData = gMainModel->evList.at(row);
        accept();
    }else{
        QMessageBox::critical(this, tr("Error"), tr("Data type mismatch"));
    }
}

void DlgPinSet::tableClicked(const QModelIndex & index)
{
    int row = index.row();
    if(gMainModel->evList.at(row).initValue.v().t() == evData.initValue.v().t()){
        rbVariable->setChecked(true);
        textConst->setEnabled(false);
        textVariable->setEnabled(true);
        textVariable->setText(gMainModel->evList.at(row).name);
    }
}

void DlgPinSet::onConst(bool check)
{
    textConst->setEnabled(check);
    textVariable->setEnabled(!check);
    textConst->setFocus();
    textConst->selectAll();
}

void DlgPinSet::onVariable(bool check)
{
    textConst->setEnabled(!check);
    textVariable->setEnabled(check);
    textVariable->setFocus();
    textVariable->selectAll();
}
