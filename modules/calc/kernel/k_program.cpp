#include <stddef.h>
#include <stdio.h>

#include "modules/calc/include/k_util.h"
#include "modules/calc/include/k_lib.h"
#include "modules/calc/include/k_evdata.h"
#include "modules/calc/include/k_program.h"
#include "modules/calc/include/k_project.h"

static enode_t *en_new()
{
	return new enode_t ;
}

static void en_delete(enode_t *p_en)
{

	delete p_en;

}

static void en_addbefore(enode_t *p_en, enode_t *p_ref)
{
	p_en->p_prev = p_ref->p_prev;
	p_en->p_next = p_ref;
	p_ref->p_prev->p_next = p_en;
	p_ref->p_prev = p_en;
}

static void en_addafter(enode_t *p_en, enode_t *p_ref)
{
	p_en->p_prev = p_ref;
	p_en->p_next = p_ref->p_next;
	p_ref->p_next->p_prev = p_en;
	p_ref->p_next = p_en;
}

static void en_remove(enode_t *p_en)
{
	p_en->p_prev->p_next = p_en->p_next;
	p_en->p_next->p_prev = p_en->p_prev;
}

static void en_movebefore(enode_t *p_en, enode_t *p_ref)
{
	en_remove(p_en);
	en_addbefore(p_en, p_ref);
}

static void en_moveafter(enode_t *p_en, enode_t *p_ref)
{
	en_remove(p_en);
	en_addafter(p_en, p_ref);
}

void prg_exec(prog_t *p_prg)
{
	enode_t *p_en;
	
	/* fb to fb */
	p_en = p_prg->en_head.p_next;
	while(p_en != &p_prg->en_head){
		if(p_en->p_fb != 0){
			p_en->p_fb->h.run(p_en->p_fb); 
		}else{
			p_en->p_vtgt->v = p_en->p_vsrc->v;
		}
		p_en = p_en->p_next;
	}

 }

prog_t *prg_new()
{
	prog_t *p_new;

	p_new = new prog_t ;
	if(p_new != 0){
		p_new->en_head.p_prev = &p_new->en_head;
		p_new->en_head.p_next = &p_new->en_head;
		p_new->p_en_select = &p_new->en_head;

	}

	return p_new;
}

void prg_delete(prog_t *p_prg)
{
	enode_t *p_en, *p_erm;

	/* clear enode list */
	p_en = p_prg->en_head.p_next;
	while(p_en != &p_prg->en_head){
		p_erm = p_en;
		p_en = p_en->p_next;
		if(p_erm->p_fb != 0){
			fb_delete(p_erm->p_fb);
		}
		en_remove(p_erm);
		en_delete(p_erm);
	}	
	delete p_prg;
}

static void prg_setrank(prog_t *p_prg)
{
	int i;
	enode_t *p_en;

	i = 0;
	p_en = p_prg->en_head.p_next;
	while(p_en != &p_prg->en_head){
		p_en->rank = i;
		i++;
		p_en = p_en->p_next;
	}
}

static void prg_clearmark(prog_t *p_prg)
{
	enode_t *p_en;

	p_en = p_prg->en_head.p_next;
	while(p_en != &p_prg->en_head){
		p_en->mark = 0;
		p_en = p_en->p_next;
	}
}

static void prg_markfbchild(prog_t *p_prg, enode_t *p_en)
{
	p_en->mark = 1;
	while(p_en != &p_prg->en_head){
		if(p_en->p_fb == 0){
			p_en->mark = p_en->p_prev->mark;
			if(p_en->mark){
				p_en->p_entgt->mark = 1;
			}
		}
		p_en = p_en->p_next;
	}
}

static void prg_markfblink(prog_t *p_prg, enode_t *p_enfb)
{
	enode_t *p_en;

	p_enfb->mark = 1;

	p_en=p_prg->en_head.p_next;
	while(p_en !=&p_prg->en_head){
		if(p_en->p_fb == 0){
			if(p_en->idsrc == p_enfb->id || p_en->idtgt == p_enfb->id){
				p_en->mark = 1;
			}
		}
		p_en=p_en->p_next;
	}
}

int prg_fbadd(prog_t *p_prg, int id, const std::string & libname, const std::string & fcname, const std::string & fbname)
{
	fb_t *p_fb;
	enode_t *p_en;
	//根据库名和功能块名找到功能块
	p_fb = lib_find(libname, fcname);
	if(0 == p_fb){
		return -1;
	}
	//根据功能块的预定义的生成一个新的功能块
	p_fb = fb_new(p_fb);
	if(0 == p_fb){
		return -1;
	}
	// p_fb->h.prj = p_prg->prj;
	
	p_en = en_new();
	if(0 == p_en){
		fb_delete(p_fb);
		return -1;
	}
	p_en->id = id;
	p_en->p_fb = p_fb;
	p_en->fbname = fbname;

	en_addbefore(p_en, &p_prg->en_head);

	return 0;
}

static int prg_enselect(prog_t *p_prg, int id)
{
	enode_t *p_en;

	if(id == 0){
		p_prg->p_en_select = &p_prg->en_head;
		return -1;
	}

	if(p_prg->p_en_select->id == id){
		return 0;
	}
	
	p_en = p_prg->en_head.p_next;
	while(p_en != &p_prg->en_head){
		if(p_en->id == id){
			p_prg->p_en_select = p_en;
			return 0;
		}
		p_en = p_en->p_next;
	}

	return -1;
}

fb_t *prg_fbfind(prog_t *p_prg, int id)
{
	enode_t *p_en;

	prg_enselect(p_prg, id);
	p_en = p_prg->p_en_select;

	if(p_en == &p_prg->en_head){
		return 0;
	}
	
	return p_en->p_fb;
}

int prg_fbremove(prog_t *p_prg, int id)
{
	enode_t *p_en, *p_rm;

	prg_enselect(p_prg, id);
	p_en = p_prg->p_en_select;
	p_prg->p_en_select = &p_prg->en_head;
	if(p_en == &p_prg->en_head){
		return -1;
	}
	
	prg_clearmark(p_prg);
	prg_markfblink(p_prg, p_en);

	
	p_en = p_prg->en_head.p_next;
	while(p_en != &p_prg->en_head){
		p_rm = p_en;
		p_en = p_en->p_next;
		if(p_rm->mark){
			if(p_rm->p_fb != 0){
				fb_delete(p_rm->p_fb);
			}
			en_remove(p_rm);
			en_delete(p_rm);
		}
	}
	return 0;
}

int prg_viadd(prog_t *p_prg,int idev, int idfb, int pin)
{
	fb_t *p_fb;
	pin_t * p_pin;
	vam_t * p_var;

	p_var= ev_find_v(idev);
	if(p_var == nullptr){
		return -1;
	}
	p_fb = prg_fbfind(p_prg, idfb);
	if(p_fb == 0){
		return -1;
	}
	p_pin = fb_getpin(p_fb, PININPUT, pin);
	if(p_pin == 0){
		return -1;
	}
	p_pin->v = *p_var;

	return 0;
}

int prg_voadd(prog_t *p_prg, int idev, int idfb, int pin)
{
	fb_t *p_fb;
	pin_t * p_pin;
	vam_t * p_var;

	p_var= ev_find_v(idev);
	if(p_var == nullptr){
		return -1;
	}
	p_fb = prg_fbfind(p_prg, idfb);
	if(p_fb == 0){
		return -1;
	}
	p_pin = fb_getpin(p_fb, PINOUTPUT, pin);
	if(p_pin == 0){
		return -1;
	}

	p_pin->v = *p_var;
	
	return 0;
}
int prg_lkadd(prog_t *p_prg, int id, int fbsrc, int pinsrc, int fbtgt, int pintgt)
{
	enode_t en, *p_en, *p_mv;
	enode_t *p_src, *p_tgt;
	
	/* get link map */
	prg_enselect(p_prg, fbsrc);
	p_src = p_prg->p_en_select;
	if(p_src == &p_prg->en_head){
		return -1;
	}
	if(p_src->p_fb == 0){
		return -1;
	}
	en.p_vsrc = fb_getpin(p_src->p_fb, PINOUTPUT, pinsrc);
	if(en.p_vsrc == 0){
		return -1;
	}

	prg_enselect(p_prg, fbtgt);
	p_tgt = p_prg->p_en_select;
	if(p_tgt == &p_prg->en_head){
		return -1;
	}
	if(p_tgt->p_fb == 0){
		return -1;
	}
	en.p_vtgt = fb_getpin(p_tgt->p_fb, PININPUT, pintgt);
	if(en.p_vtgt == 0){
		return -1;
	}

	if(en.p_vsrc->t != en.p_vtgt->t){		
		return -1;
	}

	en.id = id;
	en.idsrc = fbsrc;
	en.p_ensrc = p_src;
	en.idtgt = fbtgt;
	en.p_entgt = p_tgt;
	en.p_fb = 0;

	p_en = en_new();
	if(p_en == 0){
		return -1;
	}
	*p_en = en;
	en_addafter(p_en, p_src);

	prg_setrank(p_prg);
	//
	if(p_src->rank > p_tgt->rank){
		p_en = p_src->p_next;
		en_movebefore(p_src, p_tgt);
		while(p_en->p_fb == 0 && p_en != &p_prg->en_head){
			p_mv = p_en;
			p_en = p_en->p_next;
			en_moveafter(p_mv, p_src);
		}
	}

	return 0;
}

int prg_lkremove(prog_t *p_prg, int id)
{
	enode_t *p_rm;

	prg_enselect(p_prg, id);
	p_rm = p_prg->p_en_select;
	p_prg->p_en_select = &p_prg->en_head;
	if(p_rm == &p_prg->en_head){ 
		return -1;
	}	

	if(p_rm->p_fb != 0){
		fb_delete(p_rm->p_fb);
	}
	en_remove(p_rm);
	en_delete(p_rm);

	return 0;
}

void prg_dump(prog_t *p_prg)
{
	// vnode_t *p_vn;
	enode_t *p_en;
	std::cout << "program:" << std::endl;

	std::cout << "en:" << std::endl;
	p_en = p_prg->en_head.p_next;
	while(p_en != &p_prg->en_head){
		if(p_en->p_fb != 0){
				std::cout << "  fb: " << p_en->id 
				<< " - " << p_en->fbname
              	<< ", fc: " << p_en->p_fb->h.fcname
			  	<< std::endl;
		}else{
				std::cout << "  lk: " << p_en->id
				<< ", From.pin: " << p_en->idsrc
              	<< "." << p_en->p_vsrc->pinname
				<< " --> " 
				<< " To.pin: " << p_en->idtgt
              	<< "." << p_en->p_vtgt->pinname			
			  	<< std::endl;
		}
		p_en = p_en->p_next;
	}
}

int prg_checkloop(prog_t *p_prg, int idSrc, int idTgt)
{
	enode_t *p_src, *p_tgt;

	if(idSrc==idTgt){
		return -1;
	}

	prg_enselect(p_prg, idSrc);
	p_src = p_prg->p_en_select;
	prg_enselect(p_prg, idTgt);
	p_tgt = p_prg->p_en_select;
	if(p_src == &p_prg->en_head || p_tgt == &p_prg->en_head){
		return -1;
	}

	prg_setrank(p_prg);
	if(p_src->rank > p_tgt->rank){
		prg_clearmark(p_prg);
		prg_markfbchild(p_prg, p_tgt);
		if(p_src->mark){
			/* have loop */
			return -1;
		}
	}
	
	/* no loop */
	return 0;
}
