#ifndef MODULEPANEL_H
#define MODULEPANEL_H

#include <QDebug>
#include <QWidget>
#include <QListView>
#include <QPushButton>
#include <QBoxLayout>

class ListModule : public QListView
{
public:
    ListModule();

protected:
    void currentChanged(const QModelIndex &current, const QModelIndex &previous);
};

class ModulePanel : public QWidget
{
    Q_OBJECT
public:
    ModulePanel();
    void updateState();

private slots:
    void addModule(bool check);
    void removeModule(bool check);
    void renameModule(bool check);

private:
    ListModule *listModules;
    QPushButton *buttonAddMod;
    QPushButton *buttonRemoveMod;
    QPushButton *buttonRenameMod;
    QHBoxLayout *layoutButton;
    QVBoxLayout *layout;
};

#endif // PROGPANEL_H
