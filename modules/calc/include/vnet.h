#ifndef vnet_h
#define vnet_h

#include "k_config.h"

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <process.h>
#endif

#ifdef _LINUX
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _LINUX
typedef int SOCKET;
#define SOCKET_ERROR -1
#define INVALID_SOCKET (SOCKET)(~0)
#define vnet_closesocket(x)  close(x)
#endif

typedef void (*frecv)(int, char *);
typedef void (*frecvfrom)(int, int, char *);

#define MAX_IF_COUNT 8

//#ifdef _WIN32
typedef struct{
	struct in_addr ip;
} local_intf_t;
local_intf_t local_intfs[MAX_IF_COUNT];
local_intf_t intfs[MAX_IF_COUNT];
//#endif

extern int intfCount;
extern int intfLoopbackCount;

#define VNET_MTU 1500

int vnet_init();
void vnet_uninit();
void vnet_dump_ifs();
unsigned char vnet_iomask();

int vnet_closesocket(SOCKET);

#ifdef __cplusplus
}
#endif
#endif


