#ifndef k_config_h
#define k_config_h
#ifdef __cplusplus
extern "C" {
#endif

#define UUIDSIZE 40
#define LIBNAMESIZE 16	/* lib name length */
#define FBNAMESIZE 32
#define FCNAMESIZE 16	/* function name length */
#define PINNAMESIZE 8	/* pin name length */
#define EVNAMESIZE 32
#define PRGNAMESIZE 32
#define PRJNAMESIZE 32

#define IOSTATIONCOUNT 32
#define IOCELLCOUNT 16
#define IOIDSIZE 8
#define IODATASIZE 24
#ifndef JPMCLOGICINT_EXPORTS
//#define IONETUDP
#endif
//#define IPIOA1 "200.200.10.1"
//#define IPIOA2 "200.200.10.2"
//#define IPIOB1 "200.200.11.1"
//#define IPIOB2 "200.200.11.2"

#define TCPBUFSIZE (2*1024*1024)
#define IPA "200.200.200.10"
#define IPB "200.200.200.11"
#define STBPOLLTIME 1000
#define MAGICBASE 0x52577772

#define DEFCTRLFILE "a.cl"

#define SIMULATOR
#define INPUTCYCLE 100
#define EMPTYCYClE 50
#define OUTPUTCYCLE 100
#define MAXPEERLIFE 5
#define PEERPOLLTIME 20

#define IORETRYTIME 3
#define IOTIMEOUT 10

#ifndef _WIN32
#define _LINUX
#define _REENTERNT
#else
#endif

#ifdef __cplusplus
}
#endif
#endif
