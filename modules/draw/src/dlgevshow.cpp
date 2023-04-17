
#include "dlgevshow.h"
#include <QByteArray>
#include <QDebug>
#include <QMessageBox>

DlgEvShow::DlgEvShow(QWidget *parent, Qt::WindowFlags f) : QDialog(parent, f) {

  img = new QImage(640, 480, QImage::Format_RGB888);
  // resize(QSize(800, 600));
  // qDebug() << "image size1:" << img->size();
  label = new QLabel(tr("Show Value Deatil:"));
  str_value = new QLineEdit;
  str_value->setReadOnly(true);
  img_value = new QLabel;
  img_value->setFixedSize(640, 480);
  img_value->setStyleSheet("border:1px solid black");
  layout = new QVBoxLayout;
  layout->addWidget(label);
  layout->addWidget(str_value);
  layout->addWidget(img_value);
  setLayout(layout);
}

DlgEvShow::~DlgEvShow() {
  delete img;
  delete label;
  delete str_value;
  delete img_value;
}
// void DlgEvShow::paintEvent(QPaintEvent *e) {
//   // QPainter painter(this);
//   // painter.drawImage(0, 0, *img);
// }

void DlgEvShow::setTitle(QString title) { setWindowTitle(title); }

void DlgEvShow::setValueData(QByteArray value) {

  int height = 480;
  int width = 640;
  int index;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      index = i * width + j;
      img->setPixel(--width, height - i - 1,
                    qRgb(value[index * 3 + 0], value[index * 3 + 1],
                         value[index * 3 + 2]));
    }
  }
}

void DlgEvShow::setValueData(PLEVData ev) {
  std::string value;
  const char * ptr;
  QPixmap pixmap;
  int height = 480;
  int width = 640;
  int index;

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

    ptr =  ev.value.v().img().data();
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        index = i * width + j;
        img->setPixel(--width, height - i - 1,
                      qRgb(*(ptr+ index * 3 + 0), *(ptr+ index * 3 + 1),
                           *(ptr+ index * 3 + 2)));
      }
    }
    pixmap = QPixmap::fromImage(*img);
    pixmap = pixmap.scaled(img_value->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
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