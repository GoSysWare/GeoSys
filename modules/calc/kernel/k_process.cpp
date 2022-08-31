#include <stdio.h>
#include "modules/calc/include/k_util.h"
#include "modules/calc/include/k_process.h"

#ifdef _WIN32
	#include <windows.h>
	#include <process.h>
#elif defined(_LINUX)
	#include <pthread.h>
#endif

void k_sleep(int ms){
#ifdef _WIN32
	Sleep(ms);
#elif defined(_LINUX)
	int s, ns;	
	struct timespec tm,tm1;
	s = ms/1000;
	ns = (ms%1000)*1000*1000;
	
	tm.tv_sec = s;
	tm.tv_nsec = ns;
	nanosleep(&tm,&tm1);
#endif
}

#ifdef _LINUX
void *runproc(run_proc proc, void *cookie)
{
        //printf("ttt\n");
	proc(cookie);
        //printf("tttt\n");
}
#endif

void k_thread_start(run_proc proc, void *cookie)
{
#ifdef _WIN32
	_beginthread(proc,0,cookie);
#elif defined(_LINUX)
	static pthread_t idThread;
	pthread_create(&idThread,NULL, proc, cookie);
	pthread_detach(idThread);

#endif
}


rwlock_t *k_rwlock_create()
{
	rwlock_t  *plock;
#ifdef _LINUX
	int res;
#endif
	plock = (rwlock_t*)k_malloc(sizeof(rwlock_t));
	if(plock != NULL){
#ifdef _WIN32
        plock->read = LockCreate();
        if(plock->read != NULL){
            plock->rcount = 0;
        }else{
            k_free(plock);
           plock = NULL;
        }
#elif defined(_LINUX)
        res=LockCreate(plock->read);
        if(res==0){
            plock->rcount = 0;
        }else{
            k_free(plock);
            plock = NULL;
        }
#endif
    }
	return plock;
}

void k_rwlock_destory(rwlock_t *plock)
{
    if(plock != NULL){
        LockClose(plock->read);
        k_free(plock);
    }
}

void k_rlock(rwlock_t *plock)
{
    Lock(plock->read);    
    plock->rcount += 1;
    //printf("read lock %d\n", plock->rcount);
    Unlock(plock->read);
}

void k_runlock(rwlock_t *plock)
{
    Lock(plock->read);    
    plock->rcount -= 1;    
    //printf("read unlock %d\n", plock->rcount);
    Unlock(plock->read);
}

void k_wlock(rwlock_t *plock)
{
    Lock(plock->read);
    while(plock->rcount>0){
        Unlock(plock->read);
        k_sleep(1);
        Lock(plock->read);
    }
    //printf("write lock\n");
}

void k_wunlock(rwlock_t *plock)
{
    Unlock(plock->read);
    //printf("write unlock\n");
}
