//#include <QValidator>
#include "dlgaddmodule.h"
#include "gdefine.h"
#include <QMessageBox>

DlgAddMod::DlgAddMod(QWidget *parent, Qt::WindowFlags f) : QDialog(parent, f) {
  setWindowTitle(tr("Add Mudule"));

  label = new QLabel(tr("Mudule name:"));
  textName = new QLineEdit;
  // QRegExp rx("-?\\d{1,3}");
  // QValidator *validator = new QRegExpValidator(rx, this);
  // textName->setValidator(validator);
  textName->setMaxLength(15);
  // textName->setInputMask("nnnnnnnnnnnnnnn");
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
}

DlgAddMod::~DlgAddMod() {
  delete label;
  delete textName;
  delete buttonBox;
  delete layout;
}

void DlgAddMod::ok(bool check) {
  modName = textName->text();

  if (modName.isEmpty()) {
    return;
  }

  if (modName.indexOf(";") != -1) {
    QMessageBox::warning(this, "Warining",
                         tr("Module name can't contains ';'"));
    return;
  }
  for (int m = 0; m < gMainModel->modList.size(); m++) {
    PLModule *mod = &gMainModel->modList[m];
    if (mod->name == modName && m != indexEdit) {
      QString msg = "Module '";
      msg += modName;
      msg += "' already exist";
      QMessageBox::warning(this, "Warining", msg);
      return;
    }
  }

  accept();
}

void DlgAddMod::cancel(bool Check) { reject(); }
