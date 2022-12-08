#include "modulepanel.h"
#include "gdefine.h"
#include "dlgaddmodule.h"
#include <QMessageBox>
ListModule::ListModule()
{
}

void ListModule::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    int sel = current.row();
    if(sel >0)
    {
        gMainModel->modCurrent = &gMainModel->modList[sel];
    }
}

ModulePanel::ModulePanel()
{    
    listModules = new ListModule;
    buttonAddMod = new QPushButton(tr("Add"));
    buttonRemoveMod = new QPushButton(tr("Remove"));
    buttonRenameMod = new QPushButton(tr("Rename"));
    layoutButton = new QHBoxLayout;
    layoutButton->addWidget(buttonAddMod);
    layoutButton->addWidget(buttonRemoveMod);
    layoutButton->addWidget(buttonRenameMod);
    layoutButton->setAlignment(Qt::AlignLeft);
    layout = new QVBoxLayout;
    layout->addWidget(listModules);
    layout->addLayout(layoutButton);
    setLayout(layout);

    listModules->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //kuo edit
    listModules->setModel(&gMainModel->modelModule);

    connect(buttonAddMod, SIGNAL(clicked(bool)), this, SLOT(addModule(bool)));
    connect(buttonRemoveMod, SIGNAL(clicked(bool)), this, SLOT(removeModule(bool)));
    connect(buttonRenameMod, SIGNAL(clicked(bool)), this, SLOT(renameModule(bool)));
}

void ModulePanel::updateState()
{
    if(gTarget->isMonitor()){
        buttonAddMod->setEnabled(false);
        buttonRemoveMod->setEnabled(false);
        buttonRenameMod->setEnabled(false);
    }else{
        buttonAddMod->setEnabled(true);
        if(listModules->selectionModel()->selectedIndexes().isEmpty()){
            buttonRemoveMod->setEnabled(false);
            buttonRenameMod->setEnabled(false);
        }else{
            buttonRemoveMod->setEnabled(true);
            buttonRenameMod->setEnabled(true);
        }
    }
}

void ModulePanel::addModule(bool check)
{
    if(gTarget->isMonitor()){
        return;
    }

    DlgAddMod dlgAddMod(this);

    if(dlgAddMod.exec() != QDialog::Accepted){
        return;
    }

    PLCommand cmd;
    PLModule mod;
    mod.name = dlgAddMod.modName;
    gMainModel->makeModNewCmd(cmd, mod);
    if(!gMainModel->exeCommand(cmd)){
         QMessageBox::critical(this, "Error", QString::fromStdString(cmd.editInfo.ShortDebugString()));
        return;
    }

    gMainModel->updateModuleList();
}

void ModulePanel::removeModule(bool check)
{
    if(gTarget->isMonitor()){
        return;
    }

    if(listModules->selectionModel()->selectedIndexes().isEmpty()){
        return;
    }

    int sel = listModules->currentIndex().row();
    PLModule *mod = &gMainModel->modList[sel];
    QString msg = "Confirm to delete module '";
    msg += mod->name;
    msg += "'";
    if(QMessageBox::Yes != QMessageBox::question(this, "Question", msg, QMessageBox::Yes | QMessageBox::No)){
        return;
    }

    PLCommand cmd;
    gMainModel->makeModRemoveCmd(cmd, *mod);
    if(!gMainModel->exeCommand(cmd)){
         QMessageBox::critical(this, "Error", QString::fromStdString(cmd.editInfo.ShortDebugString()));
        return;
    }
    gMainModel->modCurrent = NULL;
    gMainModel->updateModuleList();
}

void ModulePanel::renameModule(bool check)
{
    if(gTarget->isMonitor()){
        return;
    }

    if(listModules->selectionModel()->selectedIndexes().isEmpty()){
        return;
    }

    DlgAddMod dlgAddMod(this);
    dlgAddMod.setWindowTitle("Rename module");
    dlgAddMod.indexEdit = listModules->currentIndex().row();
    if(dlgAddMod.exec() != QDialog::Accepted){
        return;
    }

    PLCommand cmd;
    PLModule mod;
    mod.id = gMainModel->modList.at(listModules->currentIndex().row()).id;
    mod.name = dlgAddMod.modName;
    gMainModel->makeModRenameCmd(cmd, mod);
    if(!gMainModel->exeCommand(cmd)){
         QMessageBox::critical(this, "Error", QString::fromStdString(cmd.editInfo.ShortDebugString()));
        return;
    }

    gMainModel->updateModuleList();
}
