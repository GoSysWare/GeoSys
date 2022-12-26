#include "progpanel.h"
#include "gdefine.h"
#include "dlgaddprog.h"
#include <QMessageBox>
ListProgram::ListProgram()
{
}

void ListProgram::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    int sel = current.row();
    if(sel >= 0)
    {
        if(gMainModel->modCurrent)
        {
            gMainModel->prgCurrent = &gMainModel->modCurrent->prgList[sel];
            gMainFrame->updateCadView();
        }
        else{
            QMessageBox::critical(this, "Error", tr("Select Mod"));
            return;  
        }

    }
}

ProgPanel::ProgPanel()
{    
    listPrograms = new ListProgram;
    buttonAddProg = new QPushButton(tr("Add"));
    buttonRemoveProg = new QPushButton(tr("Remove"));
    buttonRenameProg = new QPushButton(tr("Rename"));
    layoutButton = new QHBoxLayout;
    layoutButton->addWidget(buttonAddProg);
    layoutButton->addWidget(buttonRemoveProg);
    layoutButton->addWidget(buttonRenameProg);
    layoutButton->setAlignment(Qt::AlignLeft);
    layout = new QVBoxLayout;
    layout->addWidget(listPrograms);
    layout->addLayout(layoutButton);
    setLayout(layout);

    listPrograms->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //kuo edit
    listPrograms->setModel(&gMainModel->modelProgram);

    connect(buttonAddProg, SIGNAL(clicked(bool)), this, SLOT(addProgram(bool)));
    connect(buttonRemoveProg, SIGNAL(clicked(bool)), this, SLOT(removeProgram(bool)));
    connect(buttonRenameProg, SIGNAL(clicked(bool)), this, SLOT(renameProgram(bool)));
}

void ProgPanel::updateState()
{
    if(gTarget->isMonitor()){
        buttonAddProg->setEnabled(false);
        buttonRemoveProg->setEnabled(false);
        buttonRenameProg->setEnabled(false);
    }else{
        buttonAddProg->setEnabled(true);
        if(listPrograms->selectionModel()->selectedIndexes().isEmpty()){
            buttonRemoveProg->setEnabled(false);
            buttonRenameProg->setEnabled(false);
        }else{
            buttonRemoveProg->setEnabled(true);
            buttonRenameProg->setEnabled(true);
        }
    }
}

void ProgPanel::addProgram(bool check)
{
    if(gTarget->isMonitor()){
        return;
    }
   if(!gMainModel->modCurrent){
         QMessageBox::critical(this, "Error", tr("Select Mod"));
        return;
    }
    
    DlgAddProg dlgAddProg(this);

    if(dlgAddProg.exec() != QDialog::Accepted){
        return;
    }

    PLCommand cmd;
    PLProgram prg;
    prg.name = dlgAddProg.prgName;
    prg.desc = dlgAddProg.prgDesc;
    prg.type  = dlgAddProg.prgType == -1 ? Bus::TaskType::PERIODIC : dlgAddProg.prgType;

    prg.idMod = gMainModel->modCurrent->id;


    gMainModel->makePrgNewCmd(cmd, prg);
    if(!gMainModel->exeCommand(cmd)){
         QMessageBox::critical(this, "Error", QString::fromStdString(cmd.editInfo.ShortDebugString()));
        return;
    }

    gMainModel->updateProgList(gMainModel->modCurrent->id);
}

void ProgPanel::removeProgram(bool check)
{
    if(gTarget->isMonitor()){
        return;
    }

    if(listPrograms->selectionModel()->selectedIndexes().isEmpty()){
        return;
    }

    int sel = listPrograms->currentIndex().row();
    PLProgram *prg = &gMainModel->modCurrent->prgList[sel];
    QString msg = "Confirm to delete program '";
    msg += prg->name;
    msg += "'";
    if(QMessageBox::Yes != QMessageBox::question(this, "Question", msg, QMessageBox::Yes | QMessageBox::No)){
        return;
    }

    PLCommand cmd;
    gMainModel->makePrgRemoveCmd(cmd, *prg);
    if(!gMainModel->exeCommand(cmd)){
         QMessageBox::critical(this, "Error", QString::fromStdString(cmd.editInfo.ShortDebugString()));
        return;
    }
    gMainModel->prgCurrent = NULL;
    gMainFrame->updateCadView();
    gMainModel->updateProgList(gMainModel->modCurrent->id);
}

void ProgPanel::renameProgram(bool check)
{
    if(gTarget->isMonitor()){
        return;
    }

    if(listPrograms->selectionModel()->selectedIndexes().isEmpty()){
        return;
    }

    DlgAddProg dlgAddProg(this);
    dlgAddProg.setWindowTitle("Rename program");
    dlgAddProg.indexEdit = listPrograms->currentIndex().row();
    if(dlgAddProg.exec() != QDialog::Accepted){
        return;
    }

    PLCommand cmd;
    PLProgram prg;
    prg.idMod = gMainModel->modCurrent->id;
    prg.id = gMainModel->modCurrent->prgList.at(listPrograms->currentIndex().row()).id;
    prg.name = dlgAddProg.prgName;
    prg.desc = dlgAddProg.prgDesc;
    prg.type  = dlgAddProg.prgType == -1 ? Bus::TaskType::PERIODIC : dlgAddProg.prgType;

    gMainModel->makePrgRenameCmd(cmd, prg);
    if(!gMainModel->exeCommand(cmd)){
         QMessageBox::critical(this, "Error", QString::fromStdString(cmd.editInfo.ShortDebugString()));
        return;
    }

    gMainModel->updateProgList(gMainModel->modCurrent->id);
}
