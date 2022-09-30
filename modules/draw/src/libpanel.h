#ifndef LIBPANEL_H
#define LIBPANEL_H

#include <QWidget>
#include <QComboBox>
#include <QListView>
#include <QVBoxLayout>
#include <QListWidget>

class ListFunctions : public QListView
{
public:    
    ListFunctions();
    QString libName;
protected:
    void mousePressEvent(QMouseEvent * event);
};

class LibPanel : public QWidget
{
    Q_OBJECT
public:
    LibPanel();
private slots:
    void selLibrary(int id);
private:
    QVBoxLayout *layout;
    QComboBox *cmbLib;
    ListFunctions *listFunctions;
};

#endif // LIBPANEL_H
