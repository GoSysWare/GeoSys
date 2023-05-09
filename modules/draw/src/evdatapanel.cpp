#include "evdatapanel.h"
#include "dlgevdata.h"
#include<QMessageBox>
#include "gdefine.h"
#include "dlgevshow.h"
#include "cyber/time/time.h"

TableEVData::TableEVData()
{
    //setEditTriggers(QAbstractItemView::NoEditTriggers);
    //setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
}

bool TableEVData::setSelect()
{
    if(selectionModel()->selectedRows(0).isEmpty()){
        return false;
    }else{
        int i, row;
        for(i=0; i<gMainModel->evList.size(); i++){
            gMainModel->evList[i].isSelected = false;
        }
        //qDebug() << "select begin";
        for(int i=0; i<selectionModel()->selectedRows(0).size(); i++){
            row = selectionModel()->selectedRows(0).at(i).row();
            //qDebug() << i << "- " << selectionModel()->selectedRows(0).at(i).row();
            if(gMainModel->evList.at(row).refIn !=0 || gMainModel->evList.at(row).refOut != 0){
                QMessageBox::critical(this, tr("Error"), tr("Can't remove variable with in/out refrence"));
                return false;
            }
            gMainModel->evList[row].isSelected = true;
        }
        //qDebug() << "select end";
        return true;
    }
}

EVDataPanel::EVDataPanel()
{
    tableData = new TableEVData;
    tableData->setModel(&gMainModel->modelEVData);

    buttonAddData = new QPushButton(tr("Add"));
    buttonEditData = new QPushButton(tr("Edit"));
    buttonRemoveData = new QPushButton(tr("Remove"));
    buttonShowValue = new QPushButton(tr("Show"));

    layoutButton = new QHBoxLayout;
    layoutButton->setAlignment(Qt::AlignLeft);
    layoutButton->addWidget(buttonAddData);
    layoutButton->addWidget(buttonEditData);
    layoutButton->addWidget(buttonRemoveData);
    layoutButton->addWidget(buttonShowValue);

    layout = new QVBoxLayout;
    layout->addWidget(tableData);
    layout->addLayout(layoutButton);
    setLayout(layout);

    connect(buttonAddData, SIGNAL(clicked(bool)), this, SLOT(addEVData(bool)));
    connect(buttonEditData, SIGNAL(clicked(bool)), this, SLOT(editEVData(bool)));
    connect(buttonRemoveData, SIGNAL(clicked(bool)), this, SLOT(removeEVData(bool)));
    connect(buttonShowValue, SIGNAL(clicked(bool)), this, SLOT(showEVData(bool)));

    connect(tableData, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(tableDoubleClicked(const QModelIndex &)));

    evLast.name = "EV";
    evLast.desc = "Desc";
    evLast.type = v_type::T_INT32;
    evLast.initValue.set_t(T_INT32);
    evLast.initValue.mutable_v()->set_i(0);
}

void EVDataPanel::updateState()
{
    if(gTarget->isMatch()){
        buttonAddData->setEnabled(false);
        buttonEditData->setEnabled(false);
        buttonRemoveData->setEnabled(false);
    }else{
        buttonAddData->setEnabled(true);
        if(tableData->selectionModel()->selectedIndexes().isEmpty()){
            buttonEditData->setEnabled(false);
            buttonRemoveData->setEnabled(false);
        }else{
            buttonEditData->setEnabled(true);
            buttonRemoveData->setEnabled(true);
        }
    }
}

void EVDataPanel::addEVData(bool check)
{
    if(gTarget->isMonitor()){
        return;
    }

    DlgEVData dlgEVData(this);
    dlgEVData.setValue(evLast);
    if(dlgEVData.exec() != QDialog::Accepted){
        return;
    }
    dlgEVData.getValue(evLast);

    gMainModel->modelEVData.beginReset();
    PLCommand cmd;
    gMainModel->makeEvNewCmd(cmd, evLast);
    if(!gMainModel->exeCommand(cmd)){
         QMessageBox::critical(this, "Error", QString::fromStdString(cmd.editInfo.ShortDebugString()));
        gMainModel->modelEVData.endReset();
        return;
    }
    gMainModel->modelEVData.endReset();
}

void EVDataPanel::editEVData(bool check)
{
    if(gTarget->isMonitor()){
        return;
    }

    if(tableData->selectionModel()->selectedIndexes().isEmpty()){
        return;
    }

    evLast = gMainModel->evList.at(tableData->currentIndex().row());

    DlgEVData dlgEVData(this);
    dlgEVData.setValue(evLast, 1);
    if(dlgEVData.exec() != QDialog::Accepted){
        return;
    }
    dlgEVData.getValue(evLast);

    gMainModel->modelEVData.beginReset();
    PLCommand cmd;
    gMainModel->makeEvSetCmd(cmd, evLast);
    if(!gMainModel->exeCommand(cmd)){
         QMessageBox::critical(this, "Error", QString::fromStdString(cmd.editInfo.ShortDebugString()));
        gMainModel->modelEVData.endReset();
        return;
    }
    gMainModel->modelEVData.endReset();
}

void EVDataPanel::showEVData(bool check)
{

    if(tableData->selectionModel()->selectedIndexes().isEmpty()){
        return;
    }

    PLEVData evCur = gMainModel->evList.at(tableData->currentIndex().row());

    DlgEvShow dlgShow(this);
    dlgShow.setTitle(evCur.name);
    dlgShow.setValueData(evCur);
    if(IS_NOT_UPLOAD_TYPE(evCur.value.t())){
        gTarget->ev_ids.push_back(evCur.id);
    }
    if (dlgShow.exec() != QDialog::Accepted) {
        gTarget->ev_ids.clear();
    }

    // gMainModel->modelEVData.beginReset();
    // gMainModel->modelEVData.endReset();
}
void EVDataPanel::tableDoubleClicked(const QModelIndex & index)
{
    editEVData(true);
}

void EVDataPanel::removeEVData(bool check)
{
    if(gTarget->isMonitor()){
        return;
    }

    if(tableData->selectionModel()->selectedRows(0).isEmpty()){
        return;
    }

    if(QMessageBox::Yes != QMessageBox::question(this, "Question", tr("Confirm to delete"), QMessageBox::Yes | QMessageBox::No)){
        return;
    }

    if(!tableData->setSelect()){
        return;
    }

    gMainModel->modelEVData.beginReset();
    PLCommand cmd;
    for(int i=gMainModel->evList.size()-1; i>=0; i--){
        if(gMainModel->evList.at(i).isSelected){
            gMainModel->makeEvRemoveCmd(cmd, gMainModel->evList[i]);
            //qDebug() << cmd.cmdLine;
            if(!gMainModel->exeCommand(cmd)){
                 QMessageBox::critical(this, "Error", QString::fromStdString(cmd.editInfo.ShortDebugString()));
                gMainModel->modelEVData.endReset();
                return;
            }
        }
    }
    gMainModel->modelEVData.endReset();
    gMainFrame->updateCadView();
}
