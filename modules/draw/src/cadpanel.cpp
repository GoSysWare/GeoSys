#include "cadpanel.h"
#include "gdefine.h"
#include "pllink.h"
#include "plfunctionblock.h"
#include "plevdata.h"
#include "plprogram.h"
#include "dlgpinset.h"
#include "dlgobjname.h"
#include "modules/calc/include/k_project.h"
#include <QMessageBox>

CadPanel::CadPanel()
{
    fontMetrics = NULL;
    zoom(0);

    cursorFb = new QCursor(QPixmap(":/images/cursorfb.png"));
    cursorLk = new QCursor(QPixmap(":/images/cursorlk.png"), 0, 0);
    cursorEv = new QCursor(QPixmap(":/images/cursorev.png"), 0, 0);
    cursorPaste = new QCursor(QPixmap(":/images/cursorcp.png"));

    setMouseTracking(true);
    onTracker = false;

    setAcceptDrops(true);
}

CadPanel::~CadPanel()
{
    delete fontMetrics;
}

void CadPanel::zoom(int mode)
{
    if(mode < 0){
        step -= 2;
        if(step < MIN_GRID_STEP){
            step = MIN_GRID_STEP;
        }
    }else if(mode == 0){
        step = DEF_GRID_STEP;
    }else{
        step += 2;
        if(step > MAX_GRID_STEP){
            step = MAX_GRID_STEP;
        }
    }

    int w, h;
    w = (DEF_WIDTH + 2) * step;
    h = (DEF_HEIGHT + 2) * step;
    setMinimumSize(w, h);

    int ch = step * 0.8;
    if(ch < 1){
        ch = 1;
    }
    QFont ft(DEF_FONT_FAMILY, ch);
    setFont(ft);

    if(fontMetrics != NULL){
        delete fontMetrics;
    }
    fontMetrics = new QFontMetrics(ft);
}

void CadPanel::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.translate(step, step);

    drawGrid(painter);

    if(gMainModel->prgCurrent == NULL){
        return;
    }

    int i;
    // draw links
    for(i=0; i<gMainModel->prgCurrent->lks.size(); i++){
        drawLink(painter, gMainModel->prgCurrent->lks[i]);
    }

    // draw functionblocks
    for(i=0; i<gMainModel->prgCurrent->fbs.size(); i++){
        drawFunctionBlock(painter, gMainModel->prgCurrent->fbs[i]);
    }

    // draw vis & vos
    for(i=0; i<gMainModel->prgCurrent->vis.size(); i++){
        drawVLink(painter, gMainModel->prgCurrent->vis[i]);
    }
    for(i=0; i<gMainModel->prgCurrent->vos.size(); i++){
        drawVLink(painter, gMainModel->prgCurrent->vos[i]);
    }

    if(onTracker){
        drawTracker(painter, xMov - xSel, yMov - ySel);
        onTracker = false;
    }
}

void CadPanel::drawGrid(QPainter &painter)
{
    if(gTarget->isMonitor()){
        QRect rect(0, 0, DEF_WIDTH*step-1, DEF_HEIGHT*step-1);
        painter.fillRect(rect, Qt::lightGray);
        return;
    }

    int i;

    QColor gridColor(225, 225, 225);
    painter.setPen(gridColor);
    for(i = 0; i <= DEF_HEIGHT; i++){
        painter.drawLine(0, i*step, DEF_WIDTH*step, i*step);
    }
    for(i = 0; i <= DEF_WIDTH; i++){
        painter.drawLine(i*step, 0, i*step, DEF_HEIGHT*step);
    }
}

void CadPanel::drawLinkTracker(QPainter &painter, PLLink &lk)
{
    int i, x1, y1, x2, y2;
    x2 = lk.pts.at(0).x;
    y2 = lk.pts.at(0).y;
    for(i=1; i<lk.pts.size(); i++){
        x1 = x2;
        y1 = y2;
        x2 = lk.pts.at(i).x;
        y2 = lk.pts.at(i).y;
        painter.drawLine(x1*step, y1*step, x2*step, y2*step);
    }
}

void CadPanel::drawLink(QPainter &painter, PLLink &lk)
{
    if(lk.isSelected){
        painter.setPen(Qt::blue);
    }else{
        painter.setPen(Qt::black);
        if(gTarget->isMonitor()){
            if(lk.pin->value.v().t()  == T_BOOL){
                if(lk.pin->value.v().b()){
                    painter.setPen(Qt::green);
                }else{
                    painter.setPen(Qt::red);
                }
            }
        }
    }

    drawLinkTracker(painter, lk);
}

void CadPanel::drawColorText(QPainter &painter, QRect &rect, int flag, QString &text, QColor &fColor, QColor &bColor)
{
    painter.fillRect(rect, bColor);
    painter.setPen(fColor);
    painter.drawText(rect, flag, text);
}

void CadPanel::drawFunctionBlockTracker(QPainter &painter, PLFunctionBlock &fb)
{
    int x1, x2, y1, y2;
    QRect rt;

    x1 = (fb.x + 2) * step;
    x2 = x1 + fb.w * step;
    y1 = (fb.y + 2) * step;
    y2 = y1 + fb.h * 2 * step;
    rt.setCoords(x1, y1, x2-1, y2-1);

    painter.drawRect(rt);
}

void CadPanel::drawFunctionBlock(QPainter &painter, PLFunctionBlock &fb)
{
    int i;
    int x1, x2, y1, y2;
    QRect rt;

    QColor fColor = Qt::black;
    QColor bColor = Qt::white;
    if(gTarget->isMonitor()){
        bColor = Qt::lightGray;
    }

    // fb name
    x1 = (fb.x + 2) * step + 1;
    x2 = x1 + fontMetrics->width(fb.blkName);
    y1 = fb.y * step + 1;
    y2 = y1 + 2 * step - 2;
    rt.setCoords(x1, y1, x2, y2);
    drawColorText(painter, rt, Qt::AlignLeft | Qt::AlignVCenter, fb.blkName, fColor, bColor);


    // body
    x1 = (fb.x + 2) * step;
    x2 = x1 + fb.w * step;
    y1 = (fb.y + 2) * step;
    y2 = y1 + fb.h * 2 * step;
    rt.setCoords(x1, y1, x2-1, y2-1);
    QColor fbColor(250, 200, 150);
    painter.fillRect(rt, fbColor);
    if(fb.isSelected){
        QBrush brush(Qt::blue);
        QPen pen(brush, 2.0);
        painter.setPen(pen);
    }else{
        painter.setPen(Qt::black);
    }
    painter.drawRect(rt);

    // fc name
    painter.setPen(Qt::black);
    y1 = (fb.y + 2) * step;
    y2 = y1 + 2 * step;
    rt.setCoords(x1+1, y1, x2-1, y2);
    painter.drawText(rt, Qt::AlignHCenter | Qt::AlignVCenter, fb.funName);

    int xa, xb, y;
    QString sv;
    // input pins
    for(i=0; i<fb.input.size(); i++){
        xa = x1 - 2 * step;
        xb = x1;
        y1 = (fb.y + 4 + 2 * i) * step;
        y2 = y1 + 2 * step;
        y = y1 + step;
        if(gTarget->isMonitor()){
            if(fb.input.at(i).value.v().t()== T_BOOL){
                if(fb.input.at(i).value.v().b()){
                    painter.setPen(Qt::green);
                }else{
                    painter.setPen(Qt::red);
                }
            }
        }
        painter.drawLine(xa, y, xb, y);
        painter.setPen(Qt::black);
        rt.setCoords(x1+3, y1, x2-3, y2);
        painter.drawText(rt, Qt::AlignLeft | Qt::AlignVCenter, fb.input.at(i).name);
        if(!fb.input[i].hasInputLink && !fb.input[i].hasVariable){
            sv = fb.input[i].getStrValue();
            xb = xa;
            xa = xb - fontMetrics->width(sv);
            rt.setCoords(xa, y1, xb, y2);
            drawColorText(painter, rt, Qt::AlignRight | Qt::AlignVCenter, sv, fColor, bColor);
        }
    }

    // output pins
    for(i=0; i<fb.output.size(); i++){
        xa = x2;
        xb = x2 + 2 * step;
        y1 = (fb.y + 4 + 2 * i) * step;
        y2 = y1 + 2 * step;
        y = y1 + step;
        if(gTarget->isMonitor()){
            if(fb.output.at(i).value.v().t() == T_BOOL){
                if(fb.output.at(i).value.v().b()){
                    painter.setPen(Qt::green);
                }else{
                    painter.setPen(Qt::red);
                }
            }
        }
        painter.drawLine(xa, y, xb, y);
        painter.setPen(Qt::black);
        rt.setCoords(x1+3, y1, x2-3, y2);
        painter.drawText(rt, Qt::AlignRight | Qt::AlignVCenter, fb.output.at(i).name);
        if(!fb.output[i].hasVariable && gTarget->isMonitor()){
            sv = fb.output[i].getStrValue();
            xa = xb;
            xb = xa + fontMetrics->width(sv);
            rt.setCoords(xa, y1, xb, y2);
            drawColorText(painter, rt, Qt::AlignLeft | Qt::AlignVCenter, sv, fColor, bColor);
        }
    }
}

void CadPanel::drawVLink(QPainter &painter, PLVLink &vlk)
{
    QColor fColor = Qt::black;
    QColor bColor = Qt::white;
    if(gTarget->isMonitor()){
        bColor = Qt::lightGray;
    }

    QString sv;
    int x1, y1, x2, y2;
    if(vlk.isInput){
        sv = vlk.ev->name + "(" + vlk.ev->getStrValue() + ")";
        x2 = vlk.fb->x * step;
        x1 = x2 - fontMetrics->width(sv);
    }else{
        sv = vlk.ev->name + "(" + vlk.pin->getStrValue() + ")";
        x1 = (vlk.fb->x + vlk.fb->w + 4) * step;
        x2 = x1 + fontMetrics->width(sv);
    }
    y1 = (vlk.fb->y + (vlk.idPin + 2) * 2) * step;
    y2 = y1 + 2 * step;
    QRect rt, rt1;
    rt1.setCoords(x1, y1+1, x2, y2-2);
    rt.setCoords(x1, y1, x2, y2-1);

    drawColorText(painter, rt1, Qt::AlignHCenter | Qt::AlignVCenter, sv, fColor, bColor);
    if(vlk.isSelected){
        painter.setPen(Qt::blue);
        painter.drawRect(rt);
    }
}

void CadPanel::mousePressEvent(QMouseEvent * event)
{
    if(gMainModel->prgCurrent == NULL){
        return;
    }

    if(event->button() != Qt::LeftButton){
        return;
    }

    bool bShift = false;
    if(event->modifiers() & Qt::ShiftModifier){
        bShift = true;
    }

    int x, y;
    x = event->x() - step;
    y = event->y() - step;
    /*
        if(PLUtil.paste){
            if((evt.getModifiers()&MouseEvent.BUTTON1_MASK)!=0){
                doPaste((int)xx, (int)yy);
                if(!evt.isShiftDown()){
                    PLUtil.paste=false;
                }
            }else{
                setCursor(PLMainFrame.cursorDefault);
                PLUtil.paste=false;
            }
            return;
        }
    */

    hitTest(x, y);

    if(selCurrent.type == PT_FB){
        if(!selCurrent.fb->isSelected && !bShift){
            clearAllSelected();
        }
        selCurrent.fb->isSelected = true;
    }else{
        if(!bShift){
            clearAllSelected();
        }
    }

    PLPoint pt;
    switch(selCurrent.type){
    case PT_LKH:
        linkSel.clear();
        selCurrent.lk->isSelected = true;
        linkSel = *selCurrent.lk;
        break;
    case PT_LKV:
        linkSel.clear();
        selCurrent.lk->isSelected = true;
        linkSel = *selCurrent.lk;
        break;
    case PT_INPUT:
        linkSel.clear();
        //linkTracker.clear();
        linkSel.idPrg = selCurrent.fb->idPrg;
        linkSel.idFbTgt = selCurrent.fb->id;
        linkSel.pinTgt = selCurrent.value;
        linkSel.typeTgt = selCurrent.fb->input.at(selCurrent.value).value.v().t();
        pt.x = selCurrent.fb->x;
        pt.y = selCurrent.fb->y + 5 + selCurrent.value * 2;
        linkSel.pts.append(pt);
        linkSel.pts.append(pt);
        linkSel.pts.append(pt);
        linkSel.pts.append(pt);
        break;
    case PT_OUTPUT:
        linkSel.clear();
        //linkTracker.clear();
        linkSel.idPrg = selCurrent.fb->idPrg;
        linkSel.idFbSrc = selCurrent.fb->id;
        linkSel.pinSrc = selCurrent.value;
        linkSel.typeSrc = selCurrent.fb->output.at(selCurrent.value).value.v().t();
        pt.x = selCurrent.fb->x + selCurrent.fb->w + 4;
        pt.y = selCurrent.fb->y + 5 + selCurrent.value * 2;
        linkSel.pts.append(pt);
        linkSel.pts.append(pt);
        linkSel.pts.append(pt);
        linkSel.pts.append(pt);
        break;
    case PT_VI:
    case PT_VO:
        selCurrent.vlk->isSelected = true;
        break;
    default:
        ;
    }

    update();

    xSel = x;
    ySel = y;
    xMov = xSel;
    yMov = ySel;
}

void CadPanel::mouseMoveEvent(QMouseEvent * event)
{
    if(gTarget->isMonitor()){
        return;
    }

    if(gMainModel->prgCurrent == NULL){
        return;
    }

    /*
         if(PLUtil.paste){
            setCursor(PLMainFrame.mainFrame.cursorPaste);
            return;
        }
    */

    xMov = event->x() - step;
    yMov = event->y() - step;

    if(event->buttons() & Qt::LeftButton){
        if(selCurrent.type == PT_INPUT || selCurrent.type == PT_OUTPUT){
            hitTestTarget(xMov, yMov);
        }
        onTracker = true;
        update();
    }else{
        hitTest(xMov, yMov);
        switch(selCurrent.type){
        case PT_FB:
            setCursor(Qt::SizeAllCursor);
            break;
        case PT_INPUT:
        case PT_OUTPUT:
            setCursor(Qt::CrossCursor);
            break;
        case PT_LKH:
            setCursor(Qt::SplitVCursor);
            break;
        case PT_LKV:
            setCursor(Qt::SplitHCursor);
            break;
        case PT_VI:
        case PT_VO:
            setCursor(*cursorEv);
            break;
        default:
            setCursor(Qt::ArrowCursor);
        }
    }
}

void CadPanel::mouseReleaseEvent(QMouseEvent * event)
{
    if(gTarget->isMonitor()){
        return;
    }

    if(gMainModel->prgCurrent == NULL){
        return;
    }

    if(event->button() != Qt::LeftButton){
        return;
    }

    QRect rt;
    int i;
    PLCommand cmd;
    int dx = xMov - xSel;
    int dy = yMov - ySel;
    int ddx, ddy;
    int m;

    switch(selCurrent.type){
    case PT_NONE:
        rt.setCoords(xSel, ySel, xMov, yMov);
        for(i=0; i<gMainModel->prgCurrent->fbs.size(); i++){
            fbRectSelect(gMainModel->prgCurrent->fbs[i], rt);
        }
        for(i=0; i<gMainModel->prgCurrent->lks.size(); i++){
            lkRectSelect(gMainModel->prgCurrent->lks[i], rt);
        }
        for(i=0; i<gMainModel->prgCurrent->vis.size(); i++){
            vlkRectSelect(gMainModel->prgCurrent->vis[i], rt);
        }
        for(i=0; i<gMainModel->prgCurrent->vos.size(); i++){
            vlkRectSelect(gMainModel->prgCurrent->vos[i], rt);
        }
        break;
    case PT_LKH:
    case PT_LKV:
        if(linkTracker.id != 0){
            gMainModel->makeLkMoveCmd(cmd, linkTracker);
            if(!gMainModel->exeCommand(cmd)){
                 QMessageBox::critical(this, "Error", QString::fromStdString(cmd.editInfo.ShortDebugString()));
            }
        }
        break;
    case PT_INPUT:
        m = pinMatch();
        if(m > 0){
            linkSel.idFbSrc = selTarget.fb->id;
            linkSel.pinSrc = selTarget.value;
            linkSel.pts[0].x = selTarget.fb->x + selTarget.fb->w + 4;
            linkSel.pts[0].y = selTarget.fb->y + 5 + selTarget.value * 2;
            linkSel.pts[3].x = selCurrent.fb->x;
            linkSel.pts[3].y = selCurrent.fb->y + 5 + selCurrent.value *2;
            linkSel.pts[1].x = (linkSel.pts[0].x + linkSel.pts[3].x) / 2;
            linkSel.pts[1].y = linkSel.pts[0].y;
            linkSel.pts[2].x = (linkSel.pts[0].x + linkSel.pts[3].x) / 2;
            linkSel.pts[2].y = linkSel.pts[3].y;
            if(prj_checkloop(gMainModel->prgCurrent->idMod,gMainModel->prgCurrent->id, linkSel.idFbSrc, linkSel.idFbTgt)){
                QMessageBox::warning(this, "warning", "Signal loop - can't add link");
            }else{
                gMainModel->makeLkNewCmd(cmd, linkSel);
                if(!gMainModel->exeCommand(cmd)){
                     QMessageBox::critical(this, "Error", QString::fromStdString(cmd.editInfo.ShortDebugString()));
                }
            }
        }
        selTarget.reset();
        break;
    case PT_OUTPUT:
        m = pinMatch();
        if(m > 0){
            linkSel.idFbTgt = selTarget.fb->id;
            linkSel.pinTgt = selTarget.value;
            linkSel.pts[0].x = selCurrent.fb->x + selCurrent.fb->w + 4;
            linkSel.pts[0].y = selCurrent.fb->y + 5 + selCurrent.value * 2;
            linkSel.pts[3].x = selTarget.fb->x;
            linkSel.pts[3].y = selTarget.fb->y + 5 + selTarget.value * 2;
            linkSel.pts[1].x = (linkSel.pts[0].x + linkSel.pts[3].x) / 2;
            linkSel.pts[1].y = linkSel.pts[0].y;
            linkSel.pts[2].x = (linkSel.pts[0].x + linkSel.pts[3].x) / 2;
            linkSel.pts[2].y = linkSel.pts[3].y;
            if(prj_checkloop(gMainModel->prgCurrent->idMod,gMainModel->prgCurrent->id, linkSel.idFbSrc, linkSel.idFbTgt)){
                QMessageBox::warning(this, "warning", "Signal loop - can't add link");
            }else{
                gMainModel->makeLkNewCmd(cmd, linkSel);
                if(!gMainModel->exeCommand(cmd)){
                     QMessageBox::critical(this, "Error", QString::fromStdString(cmd.editInfo.ShortDebugString()));
                }
            }
        }
        selTarget.reset();
        break;
    case PT_FB:
        if(dx < 0){
            ddx = (dx - 0.5 * step) / step;
        }else{
            ddx = (dx + 0.5 * step) / step;
        }
        if(dy < 0){
            ddy = (dy - 0.5 * step) / step;
        }else{
            ddy = (dy + 0.5 * step) / step;
        }
        if(ddx!=0 || ddy !=0){
            moveAllSelectedFbs(ddx, ddy);
        }
        break;
    default:
        ;
    }

    onTracker = false;
    update();
}

void CadPanel::mouseDoubleClickEvent(QMouseEvent * event)
{
    if(gTarget->isMonitor()){
        return;
    }

    if(gMainModel->prgCurrent == NULL){
        return;
    }

    int x, y;
    x = event->x() - step;
    y = event->y() - step;
    hitTest(x, y);

    if(selCurrent.type == PT_FB){
        DlgObjName dlgObjName(this);
        dlgObjName.setTitle(tr("Rename function block"));
        dlgObjName.setName(selCurrent.fb->blkName);
        if(dlgObjName.exec() == QDialog::Accepted){
            PLFunctionBlock fbMove = *selCurrent.fb;
            fbMove.blkName = dlgObjName.getName();
            PLCommand cmd;
            gMainModel->makeFbMoveCmd(cmd, fbMove);
            if(!gMainModel->exeCommand(cmd)){
                 QMessageBox::critical(this, "Error", QString::fromStdString(cmd.editInfo.ShortDebugString()));
                return;
            }
            update();
            gMainModel->isModified = true;
        }
        return;
    }

    if(selCurrent.type != PT_INPUT && selCurrent.type != PT_OUTPUT){
        return;
    }

    PLEVData ev;
    bool isInput;
    if(selCurrent.type == PT_INPUT){
        if(selCurrent.fb->input.at(selCurrent.value).hasVariable){
            return;
        }
        if(selCurrent.fb->input.at(selCurrent.value).hasInputLink){
            return;
        }
        ev.initValue.mutable_v()->set_t(selCurrent.fb->input.at(selCurrent.value).value.v().t());
        isInput = true;
    }else if(selCurrent.type == PT_OUTPUT){
        if(selCurrent.fb->output.at(selCurrent.value).hasVariable){
            return;
        }
        ev.initValue.mutable_v()->set_t(selCurrent.fb->output.at(selCurrent.value).value.v().t());
        isInput = false;
    }

    QString constValue = "0";
    bool isConst = true;
    DlgPinSet dlgPinSet(this);
    dlgPinSet.exchangeValue(constValue, ev, isConst, isInput, true);
    if(dlgPinSet.exec() != QDialog::Accepted){
        return;
    }
    dlgPinSet.exchangeValue(constValue, ev, isConst, isInput, false);

    PLCommand cmd;
    PLVLink vlk;
    vlk.idPrg = gMainModel->prgCurrent->id;
    vlk.idFb = selCurrent.fb->id;
    vlk.idPin = selCurrent.value;
    vlk.idEv = ev.id;
    if(isConst){
        value_tm val;
        val =setvar(selCurrent.fb->input[selCurrent.value].type,constValue.toStdString());
        gMainModel->makePinSetCmd(cmd, gMainModel->prgCurrent->idMod,gMainModel->prgCurrent->id, selCurrent.fb->id, selCurrent.value, val);
        if(!gMainModel->exeCommand(cmd)){
            QMessageBox::critical(this, "Error", QString::fromStdString(cmd.editInfo.ShortDebugString()));
            return;
        }
        update();
    }else{
        if(isInput){
            gMainModel->modelEVData.beginReset();
            gMainModel->makeViNewCmd(cmd, vlk);
            if(!gMainModel->exeCommand(cmd)){
                QMessageBox::critical(this, "Error", QString::fromStdString(cmd.editInfo.ShortDebugString()));
                gMainModel->modelEVData.endReset();
                return;
            }
            gMainModel->modelEVData.endReset();
            update();
        }else{
            gMainModel->modelEVData.beginReset();
            gMainModel->makeVoNewCmd(cmd, vlk);
            if(!gMainModel->exeCommand(cmd)){
                QMessageBox::critical(this, "Error", QString::fromStdString(cmd.editInfo.ShortDebugString()));
                gMainModel->modelEVData.endReset();
                return;
            }
            gMainModel->modelEVData.endReset();
            update();
        }

    }
}

void CadPanel::dragEnterEvent(QDragEnterEvent * event)
{    
    if(event->mimeData()->hasFormat("PL-addfb")){
        event->acceptProposedAction();
    }
}

void CadPanel::dropEvent(QDropEvent * event)
{
    QStringList list = event->mimeData()->text().split(";");
    PLFunctionBlock fb;
    fb.libName = list.at(1);
    fb.funName = list.at(2);
    fb.x = (event->pos().x() + 0.5 * step) / step;
    fb.y = (event->pos().y() + 0.5 * step) / step;
    fb.idMod = gMainModel->modCurrent->id;
    fb.idPrg = gMainModel->prgCurrent->id;
    PLCommand cmd;
    gMainModel->makeFbNewCmd(cmd, fb);
    if(!gMainModel->exeCommand(cmd)){
        QMessageBox::critical(this, "Error", QString::fromStdString(cmd.editInfo.ShortDebugString()));
        return;
    }

    update();
}

void CadPanel::hitTest(int x, int y)
{
    selCurrent.reset();

    int i;

    // vlinks
    for(i=gMainModel->prgCurrent->vis.size()-1; i>=0; i--){
        if(vlkHitTest(selCurrent, gMainModel->prgCurrent->vis[i], x, y)){
            return;
        }
    }
    for(i=gMainModel->prgCurrent->vos.size()-1; i>=0; i--){
        if(vlkHitTest(selCurrent, gMainModel->prgCurrent->vos[i], x, y)){
            return;
        }
    }

    // function blocks
    for(i=gMainModel->prgCurrent->fbs.size()-1; i>=0; i--){
        if(fbHitTest(selCurrent, gMainModel->prgCurrent->fbs[i], x, y)){
            return;
        }
    }

    // links
    for(i=gMainModel->prgCurrent->lks.size()-1; i>=0; i--){
        if(lkHitTest(selCurrent, gMainModel->prgCurrent->lks[i], x, y)){
            return;
        }
    }
}

bool CadPanel::fbHitTest(PLSelObject &sel, PLFunctionBlock &fb, int x, int y)
{
    int i, x1, y1, x2, y2;
    QRect rt;

    // input
    for(i=0; i<fb.input.size(); i++){
        x1 = fb.x * step;
        x2 = x1 + 2 * step;
        y1 = (fb.y + 5 + i * 2) * step - 0.5 * step;
        y2 = y1 + step;
        rt.setCoords(x1, y1, x2, y2);
        if(rt.contains(x, y)){
            sel.type = PT_INPUT;
            sel.value = i;
            sel.fb = &fb;
            return true;
        }
    }

    // output
    for(i=0; i<fb.output.size(); i++){
        x1 = (fb.x + fb.w + 2) * step;
        x2 = x1 + 2 * step;
        y1 = (fb.y + 5 + i * 2) * step - 0.5 * step;
        y2 = y1 + step;
        rt.setCoords(x1, y1, x2, y2);
        if(rt.contains(x, y)){
            sel.type = PT_OUTPUT;
            sel.value = i;
            sel.fb = &fb;
            return true;
        }
    }

    // body
    x1 = fb.x * step;
    x2 = (fb.x + fb.w + 4) * step;
    y1 = fb.y *step;
    y2 = (fb.y + 2 + fb.h * 2) * step;
    rt.setCoords(x1, y1, x2, y2);
    if(rt.contains(x, y)){
        sel.type = PT_FB;
        sel.fb = &fb;
        return true;
    }else{
        return false;
    }
}

bool CadPanel::vlkHitTest(PLSelObject &sel, PLVLink &vlk, int x, int y)
{
    int x1, y1, x2, y2;
    QRect rt;

    QString sv;
    if(vlk.isInput){
        sv = vlk.ev->name + "(" + vlk.ev->getStrValue() + ")";
        x2 = vlk.fb->x * step;
        x1 = x2 - fontMetrics->width(sv);
    }else{
        sv = vlk.ev->name + "(" + vlk.pin->getStrValue() + ")";
        x1 = (vlk.fb->x + vlk.fb->w + 4) * step;
        x2 = x1 + fontMetrics->width(sv);
    }
    y1 = (vlk.fb->y + (vlk.idPin + 2) * 2) * step;
    y2 = y1 + 2 * step;

    rt.setCoords(x1, y1, x2, y2);
    if(rt.contains(x, y)){
        if(vlk.isInput){
            sel.type = PT_VI;
        }else{
            sel.type = PT_VO;
        }
        sel.vlk = &vlk;
        return true;
    }else{
        return false;
    }
}

bool CadPanel::lkHitTest(PLSelObject &sel, PLLink &lk, int x, int y)
{
    int i, x1, y1, x2, y2;
    QRect rt;

    x2 = lk.pts.at(0).x;
    y2 = lk.pts.at(0).y;
    for(i=1; i<lk.pts.size(); i++){
        x1 = x2;
        y1 = y2;
        x2 = lk.pts.at(i).x;
        y2 = lk.pts.at(i).y;
        if(x1 == x2){
            rt.setCoords(x1*step-0.5*step, y1 * step, x2*step+0.5*step, y2 * step);
            if(rt.contains(x, y)){
                sel.type = PT_LKV;
                sel.value = i;
                sel.lk = &lk;
                return true;
            }
        }else{
            rt.setCoords(x1 * step, y1*step-0.5*step, x2 * step, y2*step+0.5*step);
            if(rt.contains(x, y)){
                sel.type = PT_LKH;
                sel.value = i;
                sel.lk = &lk;
                return true;
            }
        }
    }
    return false;
}

void CadPanel::clearAllSelected()
{
    int i;

    // vlinks
    for(i=0; i<gMainModel->prgCurrent->vis.size(); i++){
        gMainModel->prgCurrent->vis[i].isSelected = false;
    }
    for(i=0; i<gMainModel->prgCurrent->vos.size(); i++){
        gMainModel->prgCurrent->vos[i].isSelected = false;
    }

    // function blocks
    for(i=0; i<gMainModel->prgCurrent->fbs.size(); i++){
        gMainModel->prgCurrent->fbs[i].isSelected = false;
    }

    // links
    for(i=0; i<gMainModel->prgCurrent->lks.size(); i++){
        gMainModel->prgCurrent->lks[i].isSelected = false;
    }
}

void CadPanel::drawTracker(QPainter &painter, int dx, int dy)
{
    int ddx;
    int ddy;
    if(dx < 0){
        ddx = (dx - 0.5 * step) / step;
    }else{
        ddx = (dx + 0.5 * step) / step;
    }
    if(dy < 0){
        ddy = (dy - 0.5 * step) / step;
    }else{
        ddy = (dy + 0.5 * step) / step;
    }

    QPen penDash(Qt::black);
    penDash.setStyle(Qt::DashLine);
    painter.setPen(penDash);
    QRect rt;    
    PLPoint *pt0, *pt1, *pt2, *pt3;
    PLFunctionBlock fb;

    switch(selCurrent.type){
    case PT_NONE:
        rt.setCoords(xSel, ySel, xSel + dx, ySel + dy);
        painter.drawRect(rt);
        break;
    case PT_INPUT:
        linkTracker = linkSel;
        pt0 = &linkTracker.pts[0];
        pt1 = &linkTracker.pts[1];
        pt2 = &linkTracker.pts[2];
        pt3 = &linkTracker.pts[3];
        pt0->x = pt3->x + ddx;
        pt0->y = pt3->y + ddy;
        pt1->x = (pt0->x + pt3->x) / 2;
        pt1->y = pt0->y;
        pt2->x = (pt0->x + pt3->x) /2;
        pt2->y = pt3->y;
        drawLinkTracker(painter, linkTracker);
        break;
    case PT_OUTPUT:
        linkTracker = linkSel;
        pt0 = &linkTracker.pts[0];
        pt1 = &linkTracker.pts[1];
        pt2 = &linkTracker.pts[2];
        pt3 = &linkTracker.pts[3];
        pt3->x = pt0->x + ddx;
        pt3->y = pt0->y + ddy;
        pt1->x = (pt0->x + pt3->x) / 2;
        pt1->y = pt0->y;
        pt2->x = (pt0->x + pt3->x) /2;
        pt2->y = pt3->y;
        drawLinkTracker(painter, linkTracker);
        break;
    case PT_LKV:
        linkTracker = linkSel;
        pt0 = &linkTracker.pts[selCurrent.value - 1];
        pt1 = &linkTracker.pts[selCurrent.value];
        if(linkTracker.pts.size() < 3){
            linkTracker.pts.insert(0, *pt0);
        }else{
            if(selCurrent.value == 1){
                linkTracker.pts.insert(0, *pt0);
            }
            if(selCurrent.value == linkTracker.pts.size() - 1){
                linkTracker.pts.append(*pt1);
            }
        }
        pt0->x += ddx;
        if(pt0->x < 0){
            pt0->x = 0;
        }
        if(pt0->x >= DEF_WIDTH){
            pt0->x = DEF_WIDTH;
        }
        pt1->x = pt0->x;
        drawLinkTracker(painter, linkTracker);
        break;
    case PT_LKH:
        linkTracker = linkSel;
        pt0 = &linkTracker.pts[selCurrent.value - 1];
        pt1 = &linkTracker.pts[selCurrent.value];
        if(linkTracker.pts.size() < 3){
            linkTracker.pts.insert(0, *pt0);
        }else{
            if(selCurrent.value == 1){
                linkTracker.pts.insert(0, *pt0);
            }
            if(selCurrent.value == linkTracker.pts.size() - 1){
                linkTracker.pts.append(*pt1);
            }
        }
        pt0->y += ddy;
        if(pt0->y < 0){
            pt0->y = 0;
        }
        if(pt0->y >= DEF_HEIGHT){
            pt0->y = DEF_HEIGHT;
        }
        pt1->y = pt0->y;
        drawLinkTracker(painter, linkTracker);
        break;
    default:
        for(int i=0; i<gMainModel->prgCurrent->fbs.size(); i++){
            if(gMainModel->prgCurrent->fbs.at(i).isSelected){
                fb = gMainModel->prgCurrent->fbs.at(i);
                fb.x += ddx;
                fb.y += ddy;
                drawFunctionBlockTracker(painter,fb);
            }
        }
    }
}

int CadPanel::pinMatch()
{
    int t1, t2;
    PLPin *pin;

    if(selTarget.type == PT_OUTPUT){
        if(selCurrent.type == PT_INPUT){
            t1 = selCurrent.fb->input.at(selCurrent.value).value.v().t();
            t2 = selTarget.fb->output.at(selTarget.value).value.v().t();
            pin = &selCurrent.fb->input[selCurrent.value];
        }else{
            return -1;
        }
    }else if(selTarget.type == PT_INPUT){
        if(selCurrent.type == PT_OUTPUT){
            t1 = selCurrent.fb->output.at(selCurrent.value).value.v().t();
            t2 = selTarget.fb->input.at(selTarget.value).value.v().t();
            pin = &selTarget.fb->input[selTarget.value];
        }else{
            return -1;
        }
    }else{
       return 0;
    }

    if(t1 == t2){
        if(pin->hasInputLink || pin->hasVariable){
            return -1;
        }else{
            return 1;
        }
    }else{
        return -1;
    }
}

void CadPanel::hitTestTarget(int x, int y)
{
    selTarget.reset();
    for(int i=0; i<gMainModel->prgCurrent->fbs.size(); i++){
        if(fbHitTest(selTarget, gMainModel->prgCurrent->fbs[i], x, y)){
            break;
        }
    }

    int m = pinMatch();

    if(m < 0){
        setCursor(Qt::ForbiddenCursor);
    }else if( m > 0){
        setCursor(*cursorLk);
    }else{
        setCursor(Qt::CrossCursor);
    }
}

void CadPanel::fbRectSelect(PLFunctionBlock &fb, QRect &rect)
{
    int x1 = fb.x;
    int x2 = fb.x + fb.w + 4;
    int y1 = fb.y;
    int y2 = fb.y + 2 + fb.h * 2;
    QRect rt;
    rt.setCoords(x1*step, y1*step, x2*step, y2*step);

    if(rect.contains(rt)){
        fb.isSelected = true;
    }
}

void CadPanel::vlkRectSelect(PLVLink & vlk, QRect &rect)
{
    QString sv;
    int x1, y1, x2, y2;
    if(vlk.isInput){
        sv = vlk.ev->name + "(" + vlk.ev->getStrValue() + ")";
        x2 = vlk.fb->x * step;
        x1 = x2 - fontMetrics->width(sv);
    }else{
        sv = vlk.ev->name + "(" + vlk.pin->getStrValue() + ")";
        x1 = (vlk.fb->x + vlk.fb->w + 4) * step;
        x2 = x1 + fontMetrics->width(sv);
    }
    y1 = (vlk.fb->y + (vlk.idPin + 2) * 2) * step;
    y2 = y1 + 2 * step;
    QRect rt;
    rt.setCoords(x1, y1, x2, y2);

    if(rect.contains((rt))){
        vlk.isSelected = true;
    }
}

void CadPanel::lkRectSelect(PLLink &lk, QRect &rect)
{
    int x1 = DEF_WIDTH;
    int x2 = 0;
    int y1 = DEF_HEIGHT;
    int y2 = 0;

    for(int i=0; i<lk.pts.size(); i++){
        if(x1 > lk.pts.at(i).x){
            x1 = lk.pts.at(i).x;
        }
        if(x2 < lk.pts.at(i).x){
            x2 = lk.pts.at(i).x;
        }
        if(y1 > lk.pts.at(i).y){
            y1 = lk.pts.at(i).y;
        }
        if(y2 < lk.pts.at(i).y){
            y2 = lk.pts.at(i).y;
        }
    }

    QRect rt;
    rt.setCoords(x1*step, y1*step, x2*step, y2*step);
    if(rect.contains(rt)){
        lk.isSelected = true;
    }
}

void CadPanel::moveAllSelectedFbs(int dx, int dy)
{
    int i;
    for(i=0; i<gMainModel->prgCurrent->lks.size(); i++){
        gMainModel->prgCurrent->lks[i].markSrc = false;
        gMainModel->prgCurrent->lks[i].markTgt = false;
    }

    PLFunctionBlock *fb;
    for(i=0; i<gMainModel->prgCurrent->fbs.size(); i++){
        fb = &gMainModel->prgCurrent->fbs[i];
        if(fb->isSelected){
            if(fb->x + dx < 0){
                dx = -fb->x;
            }
            if(fb->x + fb->w + 4 + dx > DEF_WIDTH){
                dx = DEF_WIDTH - fb->x -fb->w - 4;
            }
            if(fb->y + dy < 0){
                dy = -fb->y;
            }
            if(fb->y + fb->h * 2 + 2 + dy > DEF_HEIGHT){
                dy = DEF_HEIGHT - fb->y - fb->h * 2 - 2;
            }
        }
    }

    PLFunctionBlock fbMove;
    PLCommand cmd;
    for(i=0; i<gMainModel->prgCurrent->fbs.size(); i++){
        fb = &gMainModel->prgCurrent->fbs[i];
        if(fb->isSelected){
            fbMove = *fb;
            fbMove.x += dx;
            fbMove.y += dy;
            markLinks(fbMove.id);
            gMainModel->makeFbMoveCmd(cmd, fbMove);
            if(!gMainModel->exeCommand(cmd)){
                QMessageBox::critical(this, "Error", QString::fromStdString(cmd.editInfo.ShortDebugString()));
                return;
            }
        }
    }

    moveMarkLinks(dx, dy);
}

void CadPanel::markLinks(int id)
{
    PLLink *lk;
    for(int i=0; i<gMainModel->prgCurrent->lks.size(); i++){
        lk = &gMainModel->prgCurrent->lks[i];
        if(lk->idFbSrc == id){
            lk->markSrc = true;
        }
        if(lk->idFbTgt == id){
            lk->markTgt = true;
        }
    }
}

void CadPanel::markVLinks(int id)
{
    PLVLink *vlk;
    int i;
    for(i=0; i<gMainModel->prgCurrent->vis.size(); i++){
        vlk = &gMainModel->prgCurrent->vis[i];
        if(vlk->idFb == id){
            vlk->mark = true;
        }
    }
    for(i=0; i<gMainModel->prgCurrent->vos.size(); i++){
        vlk = &gMainModel->prgCurrent->vos[i];
        if(vlk->idFb == id){
            vlk->mark = true;
        }
    }
}

void CadPanel::moveMarkLinks(int dx, int dy)
{
    PLLink lkm, *lk;
    PLPoint *pt0, *pt1;
    PLCommand cmd;

    for(int i=0; i<gMainModel->prgCurrent->lks.size(); i++){
        lk = &gMainModel->prgCurrent->lks[i];
        if(lk->markSrc && lk->markTgt){
            lkm = *lk;
            for(int j=0; j<lkm.pts.size(); j++){
                lkm.pts[j].x += dx;
                lkm.pts[j].y += dy;
            }
        }else if(lk->markSrc){
            lkm = *lk;
            pt0 = &lkm.pts[0];
            pt1 = &lkm.pts[1];
            if(lkm.pts.size() < 3){
                lkm.pts.append(*pt1);
            }
            if(pt0->x == pt1->x){
                pt0->x += dx;
                pt0->y += dy;
                pt1->x = pt0->x;
            }else{
                pt0->x += dx;
                pt0->y += dy;
                pt1->y = pt0->y;
            }
        }else if(lk->markTgt){
            lkm = *lk;
            pt0 = &lkm.pts[lkm.pts.size()-1];
            pt1 = &lkm.pts[lkm.pts.size()-2];
            if(lkm.pts.size() < 3){
                lkm.pts.insert(0, *pt1);
            }
            if(pt0->x == pt1->x){
                pt0->x += dx;
                pt0->y += dy;
                pt1->x = pt0->x;
            }else{
                pt0->x += dx;
                pt0->y += dy;
                pt1->y = pt0->y;
            }
        }else{
            continue;
        }

        gMainModel->makeLkMoveCmd(cmd, lkm);
        if(!gMainModel->exeCommand(cmd)){
            QMessageBox::critical(this, "Error", QString::fromStdString(cmd.editInfo.ShortDebugString()));
            return;
        }
    }
}

void CadPanel::removeAllSelected()
{
    if(gMainModel->prgCurrent == NULL){
        return;
    }

    int i;
    PLCommand cmd;
    PLVLink vlk;
    PLLink lk;
    PLFunctionBlock fb;

    for(i=0; i<gMainModel->prgCurrent->lks.size(); i++){
        gMainModel->prgCurrent->lks[i].markSrc = false;
        gMainModel->prgCurrent->lks[i].markTgt = false;
    }
    for(i=0; i<gMainModel->prgCurrent->vis.size(); i++){
        gMainModel->prgCurrent->vis[i].mark = false;
    }
    for(i=0; i<gMainModel->prgCurrent->vos.size(); i++){
        gMainModel->prgCurrent->vos[i].mark = false;
    }
    for(i=gMainModel->prgCurrent->fbs.size()-1; i>=0; i--){
        fb = gMainModel->prgCurrent->fbs.at(i);
        if(fb.isSelected){
            markVLinks(fb.id);
            markLinks(fb.id);
        }
    }
    for(i=gMainModel->prgCurrent->vis.size()-1; i>=0; i--){
        vlk = gMainModel->prgCurrent->vis.at(i);
        if(vlk.isSelected || vlk.mark){
            gMainModel->makeViRemoveCmd(cmd, vlk);
            if(!gMainModel->exeCommand(cmd)){
                QMessageBox::critical(this, "Error", QString::fromStdString(cmd.editInfo.ShortDebugString()));
                return;
            }
        }
    }
    for(i=gMainModel->prgCurrent->vos.size()-1; i>=0; i--){
        vlk = gMainModel->prgCurrent->vos.at(i);
        if(vlk.isSelected || vlk.mark){
            gMainModel->makeVoRemoveCmd(cmd, vlk);
            if(!gMainModel->exeCommand(cmd)){
                QMessageBox::critical(this, "Error", QString::fromStdString(cmd.editInfo.ShortDebugString()));
                return;
            }
        }
    }
    for(i=gMainModel->prgCurrent->lks.size()-1; i>=0; i--){
        lk = gMainModel->prgCurrent->lks.at(i);
        if(lk.isSelected || lk.markSrc || lk.markTgt){
            gMainModel->makeLkRemoveCmd(cmd, lk);
            if(!gMainModel->exeCommand(cmd)){
                QMessageBox::critical(this, "Error", QString::fromStdString(cmd.editInfo.ShortDebugString()));
                return;
            }
        }
    }
    for(i=gMainModel->prgCurrent->fbs.size()-1; i>=0; i--){
        fb = gMainModel->prgCurrent->fbs.at(i);
        if(fb.isSelected){
            gMainModel->makeFbRemoveCmd(cmd, fb);
            if(!gMainModel->exeCommand(cmd)){
                QMessageBox::critical(this, "Error", QString::fromStdString(cmd.editInfo.ShortDebugString()));
                return;
            }
        }
    }

    selCurrent.reset();
    update();
}

bool CadPanel::hasSelectedObj()
{
    if(gMainModel->prgCurrent == NULL){
        return false;
    }

    int i;

    for(i=gMainModel->prgCurrent->vis.size()-1; i>=0; i--){
        if(gMainModel->prgCurrent->vis.at(i).isSelected){
            return true;
        }
    }
    for(i=gMainModel->prgCurrent->vos.size()-1; i>=0; i--){
        if(gMainModel->prgCurrent->vos.at(i).isSelected){
            return true;
        }
    }
    for(i=gMainModel->prgCurrent->lks.size()-1; i>=0; i--){
        if(gMainModel->prgCurrent->lks.at(i).isSelected){
            return true;
        }
    }
    for(i=gMainModel->prgCurrent->fbs.size()-1; i>=0; i--){
        if(gMainModel->prgCurrent->fbs.at(i).isSelected){
            return true;
        }
    }

    return false;
}

bool CadPanel::hasSelectedFb()
{
    if(gMainModel->prgCurrent == NULL){
        return false;
    }

    int i;
    for(i=0; i<gMainModel->prgCurrent->fbs.size(); i++){
        if(gMainModel->prgCurrent->fbs[i].isSelected){
            return true;
        }
    }

    return false;
}

void CadPanel::getCopyCommands(QByteArray &cpCmds)
{
    if(gMainModel->prgCurrent == NULL){
        return;
    }

    QList<PLFunctionBlock> fbs;
    QList<PLLink> lks;
    int i;
    PLFunctionBlock *fb;
    PLLink *lk;

    for(i=0; i<gMainModel->prgCurrent->fbs.size(); i++){
        fb = &gMainModel->prgCurrent->fbs[i];
        if(fb->isSelected){
            markLinks(fb->id);
            fbs.append(*fb);
        }
    }

    for(i=0; i<gMainModel->prgCurrent->lks.size(); i++){
        lk = &gMainModel->prgCurrent->lks[i];
        if(lk->markSrc && lk->markTgt && lk->isSelected){
            lks.append(*lk);
        }
    }

    int idObj = 1;
    PLMainModel::extractObjsId(idObj, fbs, lks);

    PLCommand cmd;
    QBuffer buff_io;
    buff_io.open(QFile::WriteOnly| QFile::Truncate);
    QDataStream in(&buff_io);
    for(i=0; i<fbs.size(); i++){
        gMainModel->makeFbCopyCmd(cmd, fbs[i]);
        in << QString::fromStdString(cmd.editInfo.ShortDebugString()).toLatin1();
    }

    for(i=0; i<lks.size(); i++){
        gMainModel->makeLkCopyCmd(cmd, lks[i]);
        in << QString::fromStdString(cmd.editInfo.ShortDebugString()).toLatin1();
    }
    cpCmds = buff_io.buffer();
    buff_io.close();
}


static int getObjFromCpCmd(QString &cmdLine, PLFunctionBlock &fb, PLLink &lk)
{
    QStringList list = cmdLine.split(";");
    QStringList paraList = list[2].split(",");
    QStringList resList = list[3].split(",");

    if(list.at(1) == "cpfb"){
        //fb->idPrg = paraList.at(0).toInt();
        fb.id = paraList.at(1).toInt();
        fb.libName = paraList.at(2);
        fb.funName = paraList.at(3);
        //fb->blkName = paraList.at(4);
        fb.x = resList.at(0).toInt();
        fb.y = resList.at(1).toInt();
        return 1;
    }else if(list.at(1) == "cplk"){
        //lk.idPrg = paraList.at(0).toInt();
        lk.id = paraList.at(1).toInt();
        lk.idFbSrc = paraList.at(2).toInt();
        lk.pinSrc = paraList.at(3).toInt();
        lk.idFbTgt = paraList.at(4).toInt();
        lk.pinTgt = paraList.at(5).toInt();

        lk.pts.clear();
        int x, y;
        QStringList vlist;
        for(int i=0; i<resList.size()-1; i++){
            vlist = resList.at(i).split("/");
            x = vlist.at(0).toInt();
            y = vlist.at(1).toInt();
            PLPoint pt(x,y);
            lk.pts.append(pt);
        }
        return 2;
    }

    return 0;
}

void CadPanel::exeCopyCommands(QByteArray &cpCmds)
{
    if(cpCmds.isEmpty()){
        return;
    }

    QList<PLFunctionBlock> fbList;
    QList<PLLink> lkList;
    PLFunctionBlock fb;
    PLLink lk;
    int i, t;
    int idBase = gMainModel->objID;
    QBuffer buff_io(&cpCmds);
    buff_io.open(QFile::ReadOnly);
    QDataStream in(&buff_io);
    while(!in.atEnd()){
        QByteArray meta_cmd;
        in >>meta_cmd;
        QString cmd = QString::fromLatin1(meta_cmd);
        t = getObjFromCpCmd(cmd, fb, lk);
        if(t == 1){
            fb.idPrg = gMainModel->prgCurrent->id;
            fb.id += idBase;
            fbList.append(fb);
        }else if(t ==2){
            lk.idPrg = gMainModel->prgCurrent->id;
            lk.id += idBase;
            lk.idFbSrc += idBase;
            lk.idFbTgt += idBase;
            lkList.append(lk);
        }
    }

    buff_io.close();
    clearAllSelected();
    PLCommand cmd;
    for(i=0; i<fbList.size(); i++){
        gMainModel->makeFbNewCmd(cmd, fbList[i], false);
        if(!gMainModel->exeCommand(cmd)){
           QMessageBox::critical(this, "Error", QString::fromStdString(cmd.editInfo.ShortDebugString()));
            return;
        }
    }
    for(i=0; i<lkList.size(); i++){
        gMainModel->makeLkNewCmd(cmd, lkList[i], false);
        qDebug()<<"cmd:"<<QString::fromStdString(cmd.editInfo.ShortDebugString());
        if(!gMainModel->exeCommand(cmd)){
            QMessageBox::critical(this, "Error", QString::fromStdString(cmd.editInfo.ShortDebugString()));
            return;
        }
    }
    update();
}
