#include <stdio.h>
#include "modules/calc/include/k_util.h"
#include "modules/calc/include/vnet.h"

#ifdef _LINUX
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//char **addrs;
#endif

//for vc++ only
#ifdef _WIN32
#pragma comment(lib,  "ws2_32.lib")
#endif

static int initialized = 0;
int intfCount = 0;
int intfLoopbackCount = 0;
local_intf_t local_intfs[MAX_IF_COUNT];
local_intf_t intfs[MAX_IF_COUNT];

int vnet_init()
{
	if(initialized){
		return 0;
	}

#ifdef _WIN32
	WSADATA wsd;
	int wsError;
	SOCKET inet_s;
	DWORD bytesReturned;
	INTERFACE_INFO interfaceList[MAX_IF_COUNT];
	int i, j;

	if(WSAStartup(MAKEWORD(2,2),&wsd)!=0){
		printf("WSAStartup Error!\n");
		return -1;
	}

	inet_s = socket(AF_INET,SOCK_DGRAM,0);
	wsError = WSAIoctl(inet_s,SIO_GET_INTERFACE_LIST,0,0,&interfaceList,sizeof(interfaceList), 
			&bytesReturned,NULL,NULL);
	vnet_closesocket(inet_s);
	if (wsError == SOCKET_ERROR){
		printf("Make interface list Error!\n");
		return -1;
	}

	intfCount = bytesReturned/sizeof(INTERFACE_INFO);
	for(i=0,j=0;i<intfCount;i++){
		if(interfaceList[i].iiFlags & IFF_LOOPBACK){
            local_intfs[j].ip = interfaceList[i].iiAddress.AddressIn.sin_addr;
			intfLoopbackCount++;
			j++;
		}
	}
	for(i=0;i<intfCount;i++){
		if(!(interfaceList[i].iiFlags & IFF_LOOPBACK)){
            local_intfs[j].ip = interfaceList[i].iiAddress.AddressIn.sin_addr;
			j++;
		}
	}

	initialized = 1;
	printf("init net ok\n");
	return 0;
#endif

#ifdef _LINUX	
	int inet_sock;
	struct ifreq ifr;
	FILE *net_devs;
	char *ifs_temp[MAX_IF_COUNT], *ifs[MAX_IF_COUNT];	
	int i, j;
	
	char interface[32];
	char newifs[32];
	char buf[1024];

	memset(newifs, 0, 32);
	
	net_devs = fopen("/proc/net/dev", "r");
	if(net_devs == NULL){
		perror("Can't open /proc/net/dev for reading");
		return -1;
        }

	inet_sock = socket(AF_INET, SOCK_DGRAM, 0);

	while(1){
		if(fscanf(net_devs, "%32s %1024[^\n]", interface, buf) < 0){
			//printf("scan over!\n");			
			vnet_closesocket(inet_sock);
			initialized = 1;			
			return 0;
		}	
		
		printf("interface is '%s'\n", interface);
		for(i = 0; i < strlen(interface); i++){
			if(interface[i] != ':'){
				continue;
			}else{
				ifs_temp[intfCount] = strncpy(newifs, interface, i);
				strcpy(ifr.ifr_name, newifs);			
				printf("ifs_temp[%d] is %s\n", intfCount, ifs_temp[intfCount]);			
				
				if(intfCount == 0){
						if(ioctl(inet_sock, SIOCGIFADDR, &ifr) < 0){
						perror("Not setup interface\n");
					}else{
                        local_intfs[intfCount].ip.s_addr= ((struct sockaddr_in*)&(ifr.ifr_addr))->sin_addr.s_addr;
					}
				}				
								
				for(j=0; j<MAX_IF_COUNT; j++){
					if(atoi(ifs_temp[intfCount]+3) == j){
						//printf("number is '%d', j is %d\n", atoi(ifs_temp[intfCount]+3), j);
						if(ioctl(inet_sock, SIOCGIFADDR, &ifr) < 0){
							perror("Not setup interface\n");
						}else{
                            local_intfs[j+1].ip.s_addr= ((struct sockaddr_in*)&(ifr.ifr_addr))->sin_addr.s_addr;
						}
					}	
				}
				intfCount++;
			}
		}
	}
#endif
}

void vnet_dump_ifs()
{
#ifdef _WIN32
	int i;
	for(i=0;i<intfCount;i++){
		printf("%d.%d.%d.%d\n", 
            local_intfs[i].ip.S_un.S_un_b.s_b1,
            local_intfs[i].ip.S_un.S_un_b.s_b2,
            local_intfs[i].ip.S_un.S_un_b.s_b3,
            local_intfs[i].ip.S_un.S_un_b.s_b4);
		}
#endif

#ifdef _LINUX
	int i;
	for(i=0;i<intfCount;i++){
		printf("%d.%d.%d.%d\n",		
            local_intfs[i].ip.s_addr & 0x000000ff,
            (local_intfs[i].ip.s_addr & 0x0000ff00)>>8,
            (local_intfs[i].ip.s_addr & 0x00ff0000)>>16,
            (local_intfs[i].ip.s_addr & 0xff000000)>>24);
	}
#endif
}

void vnet_uninit()
{
	initialized = 0;
}

int vnet_closesocket(SOCKET s)
{
#ifdef _WIN32
	return closesocket(s);
#endif
#ifdef _LINUX
	return close(s);
#endif
}
