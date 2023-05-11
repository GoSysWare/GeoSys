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
    labelComment = new QLabel(tr("Desc"));
    textName = new QLineEdit;
    textName->setMaxLength(32);
    listType = new QListWidget;
    listType->addItem(QString::fromStdString(v_type_Name(v_type::T_BOOL)));
    listType->addItem(QString::fromStdString(v_type_Name(v_type::T_INT32)));
    listType->addItem(QString::fromStdString(v_type_Name(v_type::T_UINT32)));
    listType->addItem(QString::fromStdString(v_type_Name(v_type::T_INT64)));
    listType->addItem(QString::fromStdString(v_type_Name(v_type::T_UINT64)));
    listType->addItem(QString::fromStdString(v_type_Name(v_type::T_FLOAT32)));
    listType->addItem(QString::fromStdString(v_type_Name(v_type::T_FLOAT64)));
    listType->addItem(QString::fromStdString(v_type_Name(v_type::T_TIME)));
    listType->addItem(QString::fromStdString(v_type_Name(v_type::T_STRING)));
    listType->addItem(QString::fromStdString(v_type_Name(v_type::T_BYTES)));
    listType->addItem(QString::fromStdString(v_type_Name(v_type::T_IMAGE)));
    listType->addItem(QString::fromStdString(v_type_Name(v_type::T_LIDAR)));
    listType->addItem(QString::fromStdString(v_type_Name(v_type::T_SONAR)));
    listType->addItem(QString::fromStdString(v_type_Name(v_type::T_FILE)));
    listType->addItem(QString::fromStdString(v_type_Name(v_type::T_ANY)));
    listType->setMaximumHeight(120);
    listType->setBatchSize(5);
    textValue = new QTextEdit;
    // textValue->setMaxLength(32);
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
    textComment->setText(ev.desc);
    std::string value;
    switch(ev.initValue.t()){
    case v_type::T_BOOL:
        listType->setCurrentRow(0);
        value = ev.initValue.v().b()?"true":"false";
        break;
    case v_type::T_INT32:
        listType->setCurrentRow(1);
        value = std::to_string(ev.initValue.v().i());
        break;
    case v_type::T_UINT32:
        listType->setCurrentRow(2);
        value = std::to_string(ev.initValue.v().ui());
        break;
    case v_type::T_INT64:
        listType->setCurrentRow(3);
        value = std::to_string(ev.initValue.v().ll());
        break;
    case v_type::T_UINT64:
        listType->setCurrentRow(4);
        value = std::to_string(ev.initValue.v().ull());
        break;
    case v_type::T_FLOAT32:
        listType->setCurrentRow(5);
        value = std::to_string(ev.initValue.v().f());
        break;
    case v_type::T_FLOAT64:
        listType->setCurrentRow(6);
        value = std::to_string(ev.initValue.v().d());
        break;
    case v_type::T_TIME:
        listType->setCurrentRow(7);
        value = std::to_string(ev.initValue.v().tm());
        break;
    case v_type::T_STRING:
        listType->setCurrentRow(8);
        value = ev.initValue.v().str();
        break;
    case v_type::T_BYTES:
        listType->setCurrentRow(9);
        value = ev.initValue.v().blob();
        break;
    case v_type::T_IMAGE:
        listType->setCurrentRow(10);
         ev.initValue.v().img().SerializeToString(&value);
        break;
    case v_type::T_LIDAR:
        listType->setCurrentRow(11);
        value = ev.initValue.v().lidar();
        break;
    case v_type::T_SONAR:
        listType->setCurrentRow(12);
        value = ev.initValue.v().sonar();
        break;
    case v_type::T_FILE:
        listType->setCurrentRow(13);
        value = ev.initValue.v().file();
        break;
    case v_type::T_ANY:
        listType->setCurrentRow(14);
         ev.initValue.v().any().SerializeToString(&value);
        break;
    default:
        QMessageBox::critical(this, "Error", "Unknown data type");
    }
    textValue->setText( QString::fromStdString(value));

}

void DlgEVData::getValue(PLEVData &ev)
{
    ev.name = textName->text();
    ev.desc = textComment->text();
    const std::string value = textValue->toPlainText().toStdString();
    ev.initValue.set_tm(apollo::cyber::Time::Now().ToNanosecond());
    switch(listType->currentIndex().row()){
    case 0:
        ev.type = v_type::T_BOOL;
        ev.initValue.set_t(v_type::T_BOOL);
        ev.initValue.mutable_v()->set_b(value == "false" || value == "0"? false:true);
        break;
    case 1:
        ev.type = v_type::T_INT32;
        ev.initValue.set_t(v_type::T_INT32);
        ev.initValue.mutable_v()->set_i(std::stoi(value));
        break;
    case 2:
        ev.type = v_type::T_UINT32;
        ev.initValue.set_t(v_type::T_UINT32);
        ev.initValue.mutable_v()->set_ui((uint32_t)std::stoul(value));
        break;
    case 3:
        ev.type = v_type::T_INT64;
        ev.initValue.set_t(v_type::T_INT64);
        ev.initValue.mutable_v()->set_ll(std::stoll(value));
        break;
    case 4:
        ev.type = v_type::T_UINT64;
        ev.initValue.set_t(v_type::T_UINT64);
        ev.initValue.mutable_v()->set_ull((uint32_t)std::stoull(value));
        break;
    case 5:
        ev.type = v_type::T_FLOAT32;
        ev.initValue.set_t(v_type::T_FLOAT32);
        ev.initValue.mutable_v()->set_f((float)std::stof(value));
        break;
    case 6:
        ev.type = v_type::T_FLOAT64;
        ev.initValue.set_t(v_type::T_FLOAT64);
        ev.initValue.mutable_v()->set_d(std::stof(value));
        break;
    case 7:
        ev.type = v_type::T_TIME;
        ev.initValue.set_t(v_type::T_TIME);
        ev.initValue.mutable_v()->set_tm(std::stoull(value));
        break;
    case 8:
        ev.type = v_type::T_STRING;
        ev.initValue.set_t(v_type::T_STRING);
        ev.initValue.mutable_v()->set_str(value);
        break;
    case 9:
        ev.type = v_type::T_BYTES;
        ev.initValue.set_t(v_type::T_BYTES);
        ev.initValue.mutable_v()->set_blob(value);
        break;
    case 10:
        ev.type = v_type::T_IMAGE;
        ev.initValue.set_t(v_type::T_IMAGE);
        ev.initValue.mutable_v()->mutable_img()->ParseFromString(value);
        break;
    case 11:
        ev.type = v_type::T_LIDAR;
        ev.initValue.set_t(v_type::T_LIDAR);
        ev.initValue.mutable_v()->set_lidar(value);
        break;
    case 12:
        ev.type = v_type::T_SONAR;
        ev.initValue.set_t(v_type::T_SONAR);
        ev.initValue.mutable_v()->set_sonar(value);
        break;
    case 13:
        ev.type = v_type::T_FILE;
        ev.initValue.set_t(v_type::T_FILE);
        ev.initValue.mutable_v()->set_file(value);
        break;
    case 14:
        ev.type = v_type::T_ANY;
        ev.initValue.set_t(v_type::T_ANY);
        ev.initValue.mutable_v()->mutable_any()->ParseFromString(value);
        break;
    default:
        ;
    }
}
