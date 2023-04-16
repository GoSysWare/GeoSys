#ifndef CADPANEL_H
#define CADPANEL_H
#include <QtGui>
#include <QDebug>
#include "pllink.h"
#include "plvlink.h"
#include "plfunctionblock.h"
#include "plselobject.h"
#include<QWidget>

const int DEF_WIDTH = 500;
const int DEF_HEIGHT = 500;
const int DEF_GRID_STEP = 11;
const int MIN_GRID_STEP = 5;
const int MAX_GRID_STEP = 21;
const QString DEF_FONT_FAMILY = "Monospaced";

class CadPanel : public QWidget
{
    Q_OBJECT
public:
    CadPanel();
    ~CadPanel();
    void zoom(int mode);
    void removeAllSelected();
    bool hasSelectedObj();
    bool hasSelectedFb();
    void getCopyCommands(QByteArray &cpCmds);
    void exeCopyCommands(QByteArray &cpCmds);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void dragEnterEvent(QDragEnterEvent * event);
    void dropEvent(QDropEvent * event);
    void mouseDoubleClickEvent(QMouseEvent * event);
signals:
	void setOnlineValueSignal(int idMod,int idPrg,int idFb,int idPin, value_tm val);


private:
    int step;
    QFontMetrics *fontMetrics;

    void drawColorText(QPainter &painter, QRect &rect, int flag, QString &text, QColor &fColor, QColor &bColor);
    void drawGrid(QPainter &painter);
    void drawLinkTracker(QPainter &painter, PLLink &lk);
    void drawLink(QPainter &painter, PLLink &lk);
    void drawFunctionBlockTracker(QPainter &painter, PLFunctionBlock &fb);
    void drawFunctionBlock(QPainter &painter, PLFunctionBlock &fb);
    void drawVLink(QPainter &painter, PLVLink &vlk);

    void hitTest(int x, int y);
    bool fbHitTest(PLSelObject &sel, PLFunctionBlock &fb, int x, int y);
    bool vlkHitTest(PLSelObject &sel, PLVLink &vlk, int x, int y);
    bool lkHitTest(PLSelObject &sel, PLLink &lk, int x, int y);
    int pinMatch();
    void hitTestTarget(int x, int y);
    void fbRectSelect(PLFunctionBlock &fb, QRect &rect);
    void vlkRectSelect(PLVLink & vlk, QRect &rect);
    void lkRectSelect(PLLink &lk, QRect &rect);

    PLSelObject selCurrent;
    PLSelObject selTarget;
    int xSel;
    int ySel;
    int xMov;
    int yMov;
    PLLink linkSel;
    PLLink linkTracker;
    void clearAllSelected();
    bool onTracker;
    void drawTracker(QPainter &painter, int dx, int dy);
    void moveAllSelectedFbs(int dx, int dy);
    void markLinks(int id);
    void moveMarkLinks(int dx, int dy);
    void markVLinks(int id);

    QCursor *cursorFb;
    QCursor *cursorLk;
    QCursor *cursorEv;
    QCursor *cursorPaste;
};

#endif // CADPANEL_H
