#include "pllink.h"

PLLink::PLLink()
{
    isSelected = false;
    pin = NULL;
}

PLLink::PLLink(const PLLink &lk)
{
    idPrg = lk.idPrg;
    id = lk.id;
    idLog = lk.idLog;
    idFbSrc = lk.idFbSrc;
    idFbTgt = lk.idFbTgt;
    pinSrc = lk.pinSrc;
    pinTgt = lk.pinTgt;
    isSelected = lk.isSelected;
    markSrc = lk.markSrc;
    markTgt = lk.markTgt;
    typeSrc = lk.typeSrc;
    typeTgt = lk.typeTgt;
    pts = lk.pts;
    pin = lk.pin;
}

void PLLink::clear()
{
    idPrg = 0;
    id = 0;
    idLog = 0;
    idFbSrc = 0;
    idFbTgt = 0;
    pinSrc = 0;
    pinTgt = 0;
    isSelected = false;
    typeSrc = T_NONE;
    typeTgt = T_NONE;
    pts.clear();
    pin = NULL;
}

void PLLink::removeDualPoints()
{
    if(pts.size() < 3){
        return;
    }

    int i;
    for(i=0; i<pts.size(); i++){
        pts[i].mark = false;
    }

    PLPoint *pt0, *pt1, *pt2;
    pt1 = &pts[0];
    pt2 = &pts[1];
    for(i=2; i<pts.size(); i++){
        pt0 = pt1;
        pt1 = pt2;
        pt2 = &pts[i];
        if(pt0->x == pt1->x && pt1->x == pt2->x){
            pt1->mark = true;
        }
        if(pt0->y == pt1->y && pt1->y == pt2->y){
            pt1->mark = true;
        }
    }

    for(i = pts.size()-1; i>=0; i--){
        if(pts.at(i).mark){
            pts.removeAt(i);
        }
    }
}
