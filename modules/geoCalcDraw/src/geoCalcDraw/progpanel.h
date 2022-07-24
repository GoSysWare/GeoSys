#ifndef PROGPANEL_H
#define PROGPANEL_H

#include <QDebug>
#include <QWidget>
#include <QListView>
#include <QPushButton>
#include <QBoxLayout>

class ListProgram : public QListView
{
public:
    ListProgram();

protected:
    void currentChanged(const QModelIndex &current, const QModelIndex &previous);
};

class ProgPanel : public QWidget
{
    Q_OBJECT
public:
    ProgPanel();
    void updateState();

private slots:
    void addProgram(bool check);
    void removeProgram(bool check);
    void renameProgram(bool check);

private:
    ListProgram *listPrograms;
    QPushButton *buttonAddProg;
    QPushButton *buttonRemoveProg;
    QPushButton *buttonRenameProg;
    QHBoxLayout *layoutButton;
    QVBoxLayout *layout;
};

#endif // PROGPANEL_H
