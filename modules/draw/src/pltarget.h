#ifndef PLTARGET_H
#define PLTARGET_H

#include <QTimer>
#include "modules/calc/proto/cmd.pb.h"
class PLTarget : public QTimer
{
    Q_OBJECT
public:
    PLTarget(QObject *parent = 0);
    ~PLTarget();
    bool online(bool mode, char *ip);
    void monitor(bool mode);
    bool sync();
    bool download();
    bool upload(Bus::EditInfos &edit);
    bool isOnline();
    bool isMonitor();
    bool isMatch();
    bool isSync();

    void timerEvent(QTimerEvent *e);

public slots:
   void setOnlineValueSlot(int idMod,int idPrg,int idFb,int idPin, value_tm val);
private:
    bool bOnline;
    bool bMonitor;
    QString uuidTarget;
    int idCmdTarget;
};

#endif // PLTARGET_H
