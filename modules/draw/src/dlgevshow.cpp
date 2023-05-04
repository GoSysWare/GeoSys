
#include "dlgevshow.h"
#include "gdefine.h"
#include <QByteArray>
#include <QDebug>
#include <QMessageBox>

DlgEvShow::DlgEvShow(QWidget *parent, Qt::WindowFlags f) : QDialog(parent, f) {

  label = new QLabel(tr("Show Value Deatil:"));
  str_value = new QLineEdit;
  str_value->setReadOnly(true);
  img_value = new QLabel;
  img_value->setFixedSize(1000, 800);
  img_value->setStyleSheet("border:1px solid black");
  layout = new QVBoxLayout;
  layout->addWidget(label);
  layout->addWidget(str_value);
  layout->addWidget(img_value);
  setLayout(layout);
}

DlgEvShow::~DlgEvShow() {
  delete label;
  delete str_value;
  delete img_value;
}


void DlgEvShow::setTitle(QString title) { setWindowTitle(title); }


void DlgEvShow::setValueData(PLEVData ev) {
  std::string value;
  const char * ptr;
  QPixmap pixmap;
  QImage img;

  int height;
  int width;
  int index;
  int step;



  switch (ev.value.v().t()) {
  case v_type::T_BOOL:
    value = ev.value.v().b() ? "true" : "false";
    break;
  case v_type::T_INT32:
    value = std::to_string(ev.value.v().i());
    break;
  case v_type::T_UINT32:
    value = std::to_string(ev.value.v().ui());
    break;
  case v_type::T_INT64:
    value = std::to_string(ev.value.v().ll());
    break;
  case v_type::T_UINT64:
    value = std::to_string(ev.value.v().ull());
    break;
  case v_type::T_FLOAT32:
    value = std::to_string(ev.value.v().f());
    break;
  case v_type::T_FLOAT64:
    value = std::to_string(ev.value.v().d());
    break;
  case v_type::T_TIME:
    value = std::to_string(ev.value.v().tm());
    break;
  case v_type::T_STRING:
    value = ev.value.v().str();
    break;
  case v_type::T_BYTES:
    value = ev.value.v().blob();
    break;
  case v_type::T_IMAGE:
    value.clear();
    height = ev.value.v().img().height();
    width = ev.value.v().img().width();
    step = ev.value.v().img().step();
    ptr =  ev.value.v().img().data().c_str();
    img=QImage((const uchar*)ptr, width, height, QImage::Format_RGB888);
    pixmap = QPixmap::fromImage(img);
    // pixmap = pixmap.scaled(img_value->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    img_value->setPixmap(pixmap);
    break;
  case v_type::T_LIDAR:
    value = ev.value.v().lidar();
    break;
  case v_type::T_SONAR:
    value = ev.value.v().sonar();
    break;
  case v_type::T_FILE:
    value = ev.value.v().file();
    break;
  default:
    QMessageBox::critical(this, "Error", "Unknown data type");
  }
  if(!value.empty()){
    str_value->setText(QString::fromStdString(value));
  }
}