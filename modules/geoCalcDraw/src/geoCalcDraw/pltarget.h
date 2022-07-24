#ifndef PLTARGET_H
#define PLTARGET_H

#include <QTimer>
#include "pliomodel.h"

class PLTarget : public QTimer
{
public:
    PLTarget(QObject *parent = 0);
    ~PLTarget();
    bool online(bool mode, char *ip);
    void monitor(bool mode);
    bool sync();
    bool download();
    bool upload(QString &cmds);
    bool isOnline();
    bool isMonitor();
    bool isMatch();
    bool isSync();

    void timerEvent(QTimerEvent *e);

    PLIOModel modelIO;

private:
    bool bOnline;
    bool bMonitor;
    QString uuidTarget;
    int idCmdTarget;
};

#endif // PLTARGET_H
