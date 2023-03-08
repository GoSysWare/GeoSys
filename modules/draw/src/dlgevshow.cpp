
#include "dlgevshow.h"
#include <QDebug>
#include <QMessageBox>

DlgEvShow::DlgEvShow(QWidget *parent, Qt::WindowFlags f) : QDialog(parent, f) {

  img = new QImage(640, 480, QImage::Format_RGB888);
  resize(QSize(800, 600));
  qDebug() << "image size1:" << img->size();
}

DlgEvShow::~DlgEvShow() { delete img; }
void DlgEvShow::paintEvent(QPaintEvent *e) {
  QPainter painter(this);
  painter.drawImage(0, 0, *img);
}

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
