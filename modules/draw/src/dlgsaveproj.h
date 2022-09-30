#ifndef DLGSAVEPROJ_H
#define DLGSAVEPROJ_H

#include <QFileDialog>
#include <QCheckBox>
#include <QLayout>

class DlgSaveProj : public QDialog
{
    Q_OBJECT
public:
    DlgSaveProj(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~DlgSaveProj();
    QString fileName;
    bool bCompatible;

private slots:
    void ok();
    void fileSelected(const QString &file);

private:
    QFileDialog *dlgFile;
    QCheckBox *cbCompatible;
    QVBoxLayout *layout;
};

#endif // DLGSAVEPROJ_H
