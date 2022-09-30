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
    if(sel >0)
    {
        gMainModel->prgCurrent = &gMainModel->prgList[sel];
        gMainFrame->updateCadView();
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

    DlgAddProg dlgAddProg(this);

    if(dlgAddProg.exec() != QDialog::Accepted){
        return;
    }

    PLCommand cmd;
    PLProgram prg;
    prg.name = dlgAddProg.prgName;
    gMainModel->makePrgNewCmd(cmd, prg);
    if(!gMainModel->exeCommand(cmd)){
         QMessageBox::critical(this, "Error", cmd.cmdLine);
        return;
    }

    gMainModel->updateProgList();
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
    PLProgram *prg = &gMainModel->prgList[sel];
    QString msg = "Confirm to delete program '";
    msg += prg->name;
    msg += "'";
    if(QMessageBox::Yes != QMessageBox::question(this, "Question", msg, QMessageBox::Yes | QMessageBox::No)){
        return;
    }

    PLCommand cmd;
    gMainModel->makePrgRemoveCmd(cmd, *prg);
    if(!gMainModel->exeCommand(cmd)){
         QMessageBox::critical(this, "Error", cmd.cmdLine);
        return;
    }
    gMainModel->prgCurrent = NULL;
    gMainFrame->updateCadView();
    gMainModel->updateProgList();
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
    prg.id = gMainModel->prgList.at(listPrograms->currentIndex().row()).id;
    prg.name = dlgAddProg.prgName;
    gMainModel->makePrgRenameCmd(cmd, prg);
    if(!gMainModel->exeCommand(cmd)){
         QMessageBox::critical(this, "Error", cmd.cmdLine);
        return;
    }

    gMainModel->updateProgList();
}
