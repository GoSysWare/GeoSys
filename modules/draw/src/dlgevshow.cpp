
#include "dlgevshow.h"
#include "gdefine.h"
#include <QByteArray>
#include <QDebug>
#include <QMessageBox>

DlgEvShow::DlgEvShow(QWidget *parent, Qt::WindowFlags f) : QDialog(parent, f) {

  // label = new QLabel(tr("Show Value Deatil:"));
  str_value = new QTextEdit;
  str_value->setFixedSize(500,400);
  img_value = new QLabel;
  img_value->setFixedSize(500, 400);
  img_value->setStyleSheet("border:1px solid black");
  layout = new QHBoxLayout;
  // layout->addWidget(label);
  layout->addWidget(str_value);
  layout->addWidget(img_value);
  setLayout(layout);
}

DlgEvShow::~DlgEvShow() {
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



  switch (ev.value.t()) {
  case v_type::T_BOOL:
  case v_type::T_INT32:
  case v_type::T_UINT32:
  case v_type::T_INT64:
  case v_type::T_UINT64:
  case v_type::T_FLOAT32:
  case v_type::T_FLOAT64:
  case v_type::T_TIME:
  case v_type::T_STRING:
  case v_type::T_BYTES:
  case v_type::T_LIDAR:
  case v_type::T_SONAR:
  case v_type::T_FILE:
  case v_type::T_ANY:
   value = ev.value.DebugString();
    break;
  case v_type::T_IMAGE:
    value.clear();
    height = ev.value.v().img().height();
    width = ev.value.v().img().width();
    step = ev.value.v().img().step();
    ptr =  ev.value.v().img().data().c_str();
    img=QImage((const uchar*)ptr, width, height, QImage::Format_RGB888);
    pixmap = QPixmap::fromImage(img);
    pixmap = pixmap.scaled(img_value->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    img_value->setPixmap(pixmap);
    break;
  default:
    QMessageBox::critical(this, "Error", "Unknown data type");
  }
  if(!value.empty()){
    str_value->setText(QString::fromStdString(value));
  }
}