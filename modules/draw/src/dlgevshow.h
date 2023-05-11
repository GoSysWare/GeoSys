
#ifndef DLGEVSHOW_H
#define DLGEVSHOW_H

#include <QDialog>
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
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
    void setValueData(PLEVData ev);
private:
    QVBoxLayout *layout;
    QLabel *label;
    QTextEdit  *str_value;
    QLabel *img_value;
};

#endif // DLGOBJNAME_H
