
#ifndef DLGOBJNAME_H
#define DLGOBJNAME_H

#include <QDialog>
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QImage>
#include <QDialogButtonBox>
#include <QPainter>

class DlgEvShow : public QDialog
{
    Q_OBJECT
public:
    DlgEvShow(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~DlgEvShow();
    void setTitle(QString title);
    void setValueData(QByteArray value);
    void paintEvent(QPaintEvent *e);

private:
    QImage * img;
    QVBoxLayout *layout;
};

#endif // DLGOBJNAME_H
