#include <memory.h>

#include "k_datatype.h"
#include "k_evdata.h"
#include "k_io.h"

int cmps_zvar(const var_t *p_var, Int type, char *buf)
{
	*buf=type;
	switch(type){
	case T_BOOL:
		*buf=T_BOOL;
		if(p_var->b){
			*buf|=0x01;
		}
		return 1;
	case T_INT:
		*buf=T_INT;
		buf++;
		memcpy(buf,&p_var->i,sizeof(Int));
		return 1+sizeof(Int);
	case T_REAL:
		*buf=T_REAL;
		buf++;
		memcpy(buf,&p_var->f,sizeof(Real));
		return 1+sizeof(Real);
	case T_LREAL:
		*buf=T_LREAL;
		buf++;
		memcpy(buf,&p_var->fl,sizeof(LReal));
		return 1+sizeof(LReal);
	case T_TIME:
		*buf=T_TIME;
		buf++;
		memcpy(buf,&p_var->tm,sizeof(Time));
		return 1+sizeof(Time);
	default:
		*buf=T_NONE;
		buf++;
		memcpy(buf,&p_var,sizeof(var_t));
		return 1+sizeof(var_t);
	}
}

int cmps_uzvar(const char *buf, var_t *p_var, Int *p_tp)
{
	*p_tp=*buf&T_MASK;

	switch(*p_tp){
	case T_BOOL:
		if(*buf&0x01){
			p_var->b=1;
		}else{
			p_var->b=0;
		}
		return 1;
	case T_INT:
		buf++;
		memcpy(&p_var->i,buf,sizeof(Int));
		return 1+sizeof(Int);
	case T_REAL:
		buf++;
		memcpy(&p_var->f,buf,sizeof(Real));
		return 1+sizeof(Real);
	case T_LREAL:
		buf++;
		memcpy(&p_var->fl,buf,sizeof(LReal));
		return 1+sizeof(LReal);
	case T_TIME:
		buf++;
		memcpy(&p_var->tm,buf,sizeof(Time));
		return 1+sizeof(Time);
	default:
		buf++;
		memcpy(&p_var,buf,sizeof(var_t));
		return 1+sizeof(var_t);
	}
}

int cmps_zcell(const iocell_t *p_cell, char *buf)
{
	int i,s;
	if(p_cell->id[0]==0){
		*buf=0;
		return 1;
	}
	s=sizeof(p_cell->data);
	for(i=s-1;i>=0;i--){
		if(p_cell->data[i]==0){
			s--;
		}else{
			break;
		}
	}

	s+=sizeof(p_cell->id);
	*buf=s;
	buf++;
	memcpy(buf,p_cell,s);
	
	return s+1;
}

int cmps_uzcell(const char *buf, iocell_t *p_cell)
{
	int s;
	s=*buf;
	if(s==0){
		memset(p_cell,0,sizeof(iocell_t));
		return 1;
	}
	buf++;
	memcpy(p_cell,buf,s);
	return s+1;
}
