#include "dlgsaveproj.h"

DlgSaveProj::DlgSaveProj(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f)
{
    setWindowTitle(tr("Save project as..."));

    dlgFile = new QFileDialog(NULL, tr("Save project as..."), tr("/calchome/config/logic"), tr("Type  (*.cl)"));
    dlgFile->setAcceptMode(QFileDialog::AcceptSave);
    cbCompatible = new QCheckBox(tr("Version comatible"));
    //cbCompatible->setChecked(false);
    layout = new QVBoxLayout;
    layout->addWidget(dlgFile);
    layout->addWidget(cbCompatible);
    setLayout(layout);

    connect(dlgFile, SIGNAL(accepted()), this, SLOT(ok()));
    connect(dlgFile, SIGNAL(rejected()), this, SLOT(reject()));
    connect(dlgFile, SIGNAL(fileSelected(QString)), this, SLOT(fileSelected(QString)));
}

DlgSaveProj::~DlgSaveProj()
{

}

void DlgSaveProj::ok()
{
    bCompatible = cbCompatible->isChecked();
    accept();
}

void DlgSaveProj::fileSelected(const QString &file)
{
    fileName = file;
    if(fileName.right(3) != ".cl"){
        fileName += ".cl";
    }
}
