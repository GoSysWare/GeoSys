#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "k_command.h"
#include "k_lib.h"
#include "k_evdata.h"
#include "k_project.h"
#define NWORD 1024
#define NLINE 1024
static int get_word(char *line, char *word, int *cursor)
{
	char * pl, * pw;
	int i;

	pw = word;
	pl = line + *cursor;
	while((*pl == ' ' || *pl == '\t' || *pl == ';' || *pl == ',') && *pl != 0){
		pl++;
		*cursor += 1;
	}

	i = 0;
	while((*pl != '\0' && *pl != ' ' && *pl != '\t' && *pl != ';' && *pl != ',') && *pl != 0 && i < NWORD - 1){
		*pw = *pl;
		pw++;
		pl++;
		*cursor += 1;
		i++;
	}

	*pw = 0;
	return i;
}
static int get_line(char *buf, char *line, int *cursor)
{
	char *pb, *pl;
	int i;

	pl=line;
	pb=buf+*cursor;
	while(*pb=='\n' && *pb!=0){
		pb++;
		*cursor+=1;
	}

	i=0;
	while(*pb!='\n' && *pb!=0 && i<NLINE-1){
		*pl=*pb;
		pl++;
		pb++;
		*cursor+=1;
		i++;
	}

	*pl=0;
	return i;
}

static int addprg(char *line, int *cursor)
{
	char word[NWORD];
	int idprg;
	char name[PRGNAMESIZE];

	get_word(line, word, cursor);
	idprg = atoi(word);
	get_word(line, word, cursor);
	strncpy(name, word, PRGNAMESIZE);
	return prj_progadd(idprg, name);
}

static int rmprg(char *line, int *cursor)
{
	char word[NWORD];
	int idprg;

	get_word(line, word, cursor);
	idprg = atoi(word);
	return prj_progremove(idprg);
}

static int addfb(char *line, int *cursor)
{
	char word[NWORD];
	int idprg;
	int idfb;
	char libname[LIBNAMESIZE];
	char fcname[FCNAMESIZE];
	char fbname[FBNAMESIZE];
	
	get_word(line, word, cursor);
	idprg = atoi(word);
	get_word(line, word, cursor);
	idfb = atoi(word);
	get_word(line, word, cursor);
	strncpy(libname, word, LIBNAMESIZE);
	get_word(line, word, cursor);
	strncpy(fcname, word, FCNAMESIZE);
	get_word(line, word, cursor);
	strncpy(fbname, word, FBNAMESIZE);

	return prj_fbadd(idprg, idfb, libname, fcname, fbname);
}

static int rmfb(char *line, int *cursor)
{
	char word[NWORD];
	int idprg;
	int idfb;

	get_word(line, word, cursor);
	idprg = atoi(word);
	get_word(line, word, cursor);
	idfb = atoi(word);

	return prj_fbremove(idprg, idfb);
}

static int addlk(char *line, int *cursor)
{
	char word[NWORD];
	int idprg;
	int idlk, fbsrc, pinsrc, fbtgt, pintgt;
	
	get_word(line, word, cursor);
	idprg = atoi(word);
	get_word(line, word, cursor);
	idlk = atoi(word);
	get_word(line, word, cursor);
	fbsrc = atoi(word);
	get_word(line, word, cursor);
	pinsrc = atoi(word);
	get_word(line, word, cursor);
	fbtgt = atoi(word);
	get_word(line, word, cursor);
	pintgt = atoi(word);

	return prj_lkadd(idprg, idlk, fbsrc, pinsrc, fbtgt, pintgt);
}

static int rmlk(char *line, int *cursor)
{
	char word[NWORD];
	int idprg;
	int idlk;

	get_word(line, word, cursor);
	idprg = atoi(word);
	get_word(line, word, cursor);
	idlk = atoi(word);
	
	return prj_lkremove(idprg, idlk);
}

static int addvi(char *line, int *cursor)
{
	char word[NWORD];
	int idprg;
	int idvi, ev, fb, pin;

	get_word(line, word, cursor);
	idprg = atoi(word);
	get_word(line, word, cursor);
	idvi = atoi(word);
	get_word(line, word, cursor);
	ev = atoi(word);
	get_word(line, word, cursor);
	fb = atoi(word);
	get_word(line, word, cursor);
	pin = atoi(word);

	return prj_viadd(idprg, idvi, ev, fb, pin);
}

static int rmvi(char *line, int *cursor)
{
	char word[NWORD];
	int idprg;
	int idvi;

	get_word(line, word, cursor);
	idprg = atoi(word);
	get_word(line, word, cursor);
	idvi = atoi(word);

	return prj_viremove(idprg, idvi);
}

static int addvo(char *line, int *cursor)
{
	char word[NWORD];
	int idprg;
	int idvo, ev, fb, pin;

	get_word(line, word, cursor);
	idprg = atoi(word);
	get_word(line, word, cursor);
	idvo = atoi(word);
	get_word(line, word, cursor);
	ev = atoi(word);
	get_word(line, word, cursor);
	fb = atoi(word);
	get_word(line, word, cursor);
	pin = atoi(word);

	return prj_voadd(idprg, idvo, ev, fb, pin);
}

static int rmvo(char *line, int *cursor)
{
	char word[NWORD];
	int idprg;
	int idvo;

	get_word(line, word, cursor);
	idprg = atoi(word);
	get_word(line, word, cursor);
	idvo = atoi(word);

	return prj_voremove(idprg, idvo);
}

static int addev(char *line, int *cursor)
{
	char word[NWORD];
	int id;
	char type[32];
	char value[32];
	char name[EVNAMESIZE];

	get_word(line, word, cursor);
	id = atoi(word);
	get_word(line, word, cursor);
	strncpy(type, word, sizeof(type));
	get_word(line, word, cursor);
	strncpy(value, word, sizeof(value));
	get_word(line, word, cursor);
	strncpy(name, word, EVNAMESIZE);

	return ev_add(id, type, value, name);
}

static int rmev(char *line, int *cursor)
{
	char word[NWORD];
	int id;

	get_word(line, word, cursor);
	id = atoi(word);

	return ev_remove(id);
}

static int showlib()
{
	lib_t *p_lib;
	fb_t *p_fb;
	
	p_lib = lib_first();
	do{
		printf("lib - %s\n", p_lib->libname);
		p_fb = p_lib->first();
		do{
			printf("  %s\n", p_fb->h.fcname);
			p_fb = p_lib->next();
		}while(p_fb !=  ((void*) 0));

		p_lib = lib_next();
	}while(p_lib !=  ((void*) 0));
	
	return 0;
}

static int showprj()
{
	prj_dump();

	return 0;
}

static int showevlist()
{
	ev_dump();

	return 0;
}

static int showprg(char *line, int *cursor)
{
	char word[NWORD];
	int idprg;

	get_word(line, word, cursor);
	idprg = atoi(word);

	return prj_prgdump(idprg);
}

static int showfb(char *line, int *cursor)
{
	char word[NWORD];
	int idprg;
	int idfb;

	get_word(line, word, cursor);
	idprg = atoi(word);
	get_word(line, word, cursor);
	idfb = atoi(word);

	return prj_fbdump(idprg, idfb);
}

static int showev(char *line, int *cursor)
{
	char word[NWORD];
	int idev;
	val_t *p_ev;

	get_word(line, word, cursor);
	idev = atoi(word);
	p_ev = ev_find(idev);
	if(p_ev ==  ((void*) 0)){
		return -1;
	}

	var2str(word,p_ev->v,p_ev->t);
	printf("%s\n", word);

	return 0;
}


static int setev(char *line, int *cursor)
{
	char word[NWORD];
	int idev;
	val_t *p_val;

	get_word(line, word, cursor);
	idev = atoi(word);
	p_val = ev_find(idev);
	if(p_val ==  ((void*) 0)){
		return -1;
	}
	get_word(line, word, cursor);
	str2var(word,&p_val->v,p_val->t);

	return 0;
}

static int setpin(char *line, int *cursor)
{
	char word[NWORD];
	int idprg;
	int idfb, pin;
	var_t v;
	fb_t *p_fb;

	get_word(line, word, cursor);
	idprg = atoi(word);
	get_word(line, word, cursor);
	idfb = atoi(word);

	p_fb = prj_fbfind(idprg, idfb);
	if(p_fb ==  ((void*) 0)){
		return -1;
	}

	get_word(line, word, cursor);
	pin = atoi(word);	
	get_word(line, word, cursor);
	str2var(word,&v,fb_getpin(p_fb, PININPUT, pin)->t);

	return fb_setpin(p_fb, PININPUT, pin, v);
}

static int help()
{
	printf("Usage:\n");
	/* config command */
	printf("addprg	idprg name\n");
	printf("rmprg	idprg\n");
	printf("addfb	idprg idfb libname fcname fbname\n");
	printf("rmfb	idprg idfb\n");
	printf("addlk	idprg idlk fbsrc pinsrc fbtgt pintgt\n");
	printf("rmlk	idprg idlk\n");
	printf("addvi	idprg idvi idev idfb pin\n");
	printf("rmvi	idprg idvi\n");
	printf("addvo	idprg idvo idev idfb pi\n");
	printf("rmvo	idprg idvo\n");
	printf("addev	idev type value name\n");
	printf("rmev	idev\n");
	/* set data command */
	printf("setpin	idprg idfb pin val\n");
	printf("setev	idev val\n");
	/* dump command */
	printf("showprj\n");
	printf("showlib\n");
	printf("showev\n");
	printf("showprg	idprg\n");
	printf("showfb	idprg idfb\n");
	/* run command */
	printf("run\n");
	printf("stop\n");

	return 0;
}

static int run()
{
	prj_exec();

	return 0;
}

static int stop()
{
	return 0;
}

static int setprj(char *line, int *cursor)
{
	char word[NWORD];

	prjinfo_t *info;
	info=prj_info();
	
	get_word(line, word, cursor);
	strncpy(info->uuid, word, sizeof(info->uuid));

    printf("-------------------------load prj-----------------\n");
    //qss for clac:清空tag_list
   // tag_ev_reset();
   // tag_in_reset();
   // tag_out_reset();
	return 0;
}

static char imgbuf[TCPBUFSIZE];
static int dumpimg()
{
	FILE *f;
	f=fopen("img.dat","wb");
	if(f== NULL){
		return -1;
	}

	prj_to_img((prjimg_t *)imgbuf);
	fwrite(imgbuf,1,TCPBUFSIZE,f);

	fclose(f);

	return 0;
}

int cmd_dispatch(char *line)
{
	int cursor;
	char word[NWORD];
	int idcmd;
	prjinfo_t *info;
	
	cursor = 0;
	get_word(line, word, &cursor);
	idcmd=atoi(word);
	info=prj_info();
	if(info->id_cmd<idcmd){
		info->id_cmd=idcmd;
	}

	get_word(line, word, &cursor);

#ifdef _WIN32
	if(stricmp(word, "addprg") == 0){
		return addprg(line, &cursor);
	}else if(stricmp(word, "rmprg") == 0){
		return rmprg(line, &cursor);
	}else if(stricmp(word, "addev") == 0){
		return addev(line, &cursor);
	}else if(stricmp(word, "rmev") == 0){
		return rmev(line, &cursor);
	}else if(stricmp(word, "addfb") == 0){
		return addfb(line, &cursor);
	}else if(stricmp(word, "rmfb") == 0){
		return rmfb(line, &cursor);
	}else if(stricmp(word, "addlk") == 0){
		return addlk(line, &cursor);
	}else if(stricmp(word, "rmlk") == 0){
		return rmlk(line, &cursor);
	}else if(stricmp(word, "addvi") == 0){
		return addvi(line, &cursor);
	}else if(stricmp(word, "rmvi") == 0){
		return rmvi(line, &cursor);
	}else if(stricmp(word, "addvo") == 0){
		return addvo(line, &cursor);
	}else if(stricmp(word, "rmvo") == 0){
		return rmvo(line, &cursor);
	}else if(stricmp(word, "setpin") == 0){
		return setpin(line, &cursor);
	}else if(stricmp(word, "setev") == 0){
		return setev(line, &cursor);
	}else if(stricmp(word, "showprj") == 0){
		return showprj();
	}else if(stricmp(word, "showlib") == 0){
		return showlib();
	}else if(stricmp(word, "showev") == 0){
		return showevlist();
	}else if(stricmp(word, "showprg") == 0){
		return showprg(line, &cursor);
	}else if(stricmp(word, "showfb") == 0){
		return showfb(line, &cursor);
	}else if(stricmp(word, "run") == 0){
		return run();
	}else if(stricmp(word, "stop") == 0){
		return stop();
	}else if(stricmp(word, "help") == 0){
		return help();
	}else if(stricmp(word, "setprj") == 0){
		return setprj(line, &cursor);
	}else if(stricmp(word, "dumpimg") == 0){
		return dumpimg();
	}
#elif defined(_LINUX)
	if(strcasecmp(word, "addprg") == 0){
		return addprg(line, &cursor);
	}else if(strcasecmp(word, "rmprg") == 0){
		return rmprg(line, &cursor);
	}else if(strcasecmp(word, "addev") == 0){
		return addev(line, &cursor);
	}else if(strcasecmp(word, "rmev") == 0){
		return rmev(line, &cursor);
	}else if(strcasecmp(word, "addfb") == 0){
		return addfb(line, &cursor);
	}else if(strcasecmp(word, "rmfb") == 0){
		return rmfb(line, &cursor);
	}else if(strcasecmp(word, "addlk") == 0){
		return addlk(line, &cursor);
	}else if(strcasecmp(word, "rmlk") == 0){
		return rmlk(line, &cursor);
	}else if(strcasecmp(word, "addvi") == 0){
		return addvi(line, &cursor);
	}else if(strcasecmp(word, "rmvi") == 0){
		return rmvi(line, &cursor);
	}else if(strcasecmp(word, "addvo") == 0){
		return addvo(line, &cursor);
	}else if(strcasecmp(word, "rmvo") == 0){
		return rmvo(line, &cursor);
	}else if(strcasecmp(word, "setpin") == 0){
		return setpin(line, &cursor);
	}else if(strcasecmp(word, "setev") == 0){
		return setev(line, &cursor);
	}else if(strcasecmp(word, "showprj") == 0){
		return showprj();
	}else if(strcasecmp(word, "showlib") == 0){
		return showlib();
	}else if(strcasecmp(word, "showev") == 0){
		return showevlist();
	}else if(strcasecmp(word, "showprg") == 0){
		return showprg(line, &cursor);
	}else if(strcasecmp(word, "showfb") == 0){
		return showfb(line, &cursor);
	}else if(strcasecmp(word, "run") == 0){
		return run();
	}else if(strcasecmp(word, "stop") == 0){
		return stop();
	}else if(strcasecmp(word, "help") == 0){
		return help();
	}else if(strcasecmp(word, "setprj") == 0){
		return setprj(line, &cursor);
	}else if(strcasecmp(word, "dumpimg") == 0){
		return dumpimg();
	}
#endif

	return 0;
}

int cmds_dispatch(char *buf)
{
	int cursor;
	char line[NLINE];
	int len;

	cursor=0;
	while((len=get_line(buf, line, &cursor))!=0){
		if(cmd_dispatch(line)!=0){
			return -1;
		}
	}

	return 0;
}

int cmds_load(char *buf, int len)
{
	FILE *f;
	int l;
	f=fopen(DEFCTRLFILE,"rb");
	if(f== NULL){
		return -1;
	}

	l=fread(buf,1,len,f);
	buf+=l;
	*buf=0;

	fclose(f);
	return l+1;
}

int cmds_reset()
{
	FILE *f;
	f=fopen(DEFCTRLFILE,"wb");
	if(f==((void*) 0)){
		return -1;
	}

	fclose(f);

	return 0;
}

int cmds_append(char *buf, int len)
{
	FILE *f;
	f=fopen(DEFCTRLFILE,"ab");
	if(f==((void*) 0)){
		return -1;
	}

	fwrite(buf,1,len,f);
	fclose(f);

	return 0;
}
