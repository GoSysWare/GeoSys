
#ifndef DLGEVSHOW_H
#define DLGEVSHOW_H

#include <QDialog>
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QImage>
#include <QDialogButtonBox>
#include <QPainter>
#include "plevdata.h"

class DlgEvShow : public QDialog
{
    Q_OBJECT
public:
    DlgEvShow(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~DlgEvShow();
    void setTitle(QString title);
    void setValueData(QByteArray value);
    // void paintEvent(QPaintEvent *e);
    void setValueData(PLEVData ev);
private:
    QImage * img;
    QVBoxLayout *layout;
    QLabel *label;
    QLineEdit  *str_value;
    QLabel *img_value;
};

#endif // DLGOBJNAME_H
