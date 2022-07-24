

#ifndef k_process_h
#define k_process_h

#include "k_config.h"

typedef void (*run_proc)(void *);

#ifdef _LINUX
#include <pthread.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

void k_sleep(int ms);
void k_thread_start(run_proc proc, void *cookie);

#ifdef _WIN32
#define LOCK            void*
#define LockCreate()    CreateMutex(NULL, FALSE, NULL)
#define Lock(x)         (void)WaitForSingleObject((x), INFINITE)
#define Unlock(x)       (void)ReleaseMutex(x)
#define LockClose(x)    (void)CloseHandle(x)
#endif

#ifdef _LINUX
#define LOCK            pthread_mutex_t
#define LockCreate(x)   pthread_mutex_init(&x,NULL)
#define Lock(x)         pthread_mutex_lock(&x)
#define Unlock(x)       pthread_mutex_unlock(&x)
#define LockClose(x)    pthread_mutex_destroy(&x)
#endif

typedef struct RWLock{
    LOCK read;
    int rcount;
}rwlock_t;
rwlock_t *k_rwlock_create();

void k_rwlock_destory(rwlock_t *plock);
void k_rlock(rwlock_t *plock);
void k_runlock(rwlock_t *plock);
void k_wlock(rwlock_t *plock);
void k_wunlock(rwlock_t *plock);

#ifdef __cplusplus
}
#endif
#endif
