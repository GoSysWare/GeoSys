#include <stdio.h>
#include <k_util.h>
#include <k_process.h>
#include <vnet.h>
#include <vudp.h>

#define INADDR_VBUS "230.10.10.10"
#define BASE_PORT 15555
#define UDPPORTSCOUNT 8
typedef struct{
	SOCKET s;		//SOCKET st cancelled
	SOCKET sm;
	frecv rev;
	int bind;
	unsigned char mask;
	int ttl;
	int loop;
} udpport_t;
static udpport_t uports[UDPPORTSCOUNT];

static int initialized=0;

int vudp_init()
{
	int i;
	int trueval = 1;
	int falseval = 0;

	if(initialized){
		return 0;
	}

	for(i = 0; i < UDPPORTSCOUNT; i++){
		uports[i].bind = 0;
		uports[i].mask = 0xff;
		uports[i].ttl = 3;
		uports[i].loop = 0; 

		uports[i].s = socket(AF_INET,SOCK_DGRAM,0);
		if(uports[i].s == INVALID_SOCKET){
			printf("Create udp socket ERROR!\n");
			return -1;
		}							
		
		if(SOCKET_ERROR == setsockopt(uports[i].s, SOL_SOCKET, SO_BROADCAST, (char*)&trueval,sizeof(trueval))){
			printf("Set udp socket broadcast ERROR!\n");
			return -1;
		}
		if(SOCKET_ERROR == setsockopt(uports[i].s,IPPROTO_IP,IP_MULTICAST_TTL,
			(const char*)&uports[i].ttl,sizeof(uports[i].ttl))){
			printf("Set udp socket ttl ERROR!\n");
			return -1;
		}
	}
	
	initialized=1;
	return 0;
}

void vudp_uninit()
{
	int i;

	for(i=0; i<UDPPORTSCOUNT; i++){
		if(uports[i].bind){
			vudp_unhook(i);
		}
	}
	initialized=0;
}

void vudp_set_mask(int port, unsigned char mask)
{
	if(port < 0 || port >= UDPPORTSCOUNT){
		return;
	}
	
	uports[port].mask = mask;
}

int vudp_set_loop(int port, int loop)
{
	if(port < 0 || port >= UDPPORTSCOUNT){
		return -1;
	}
	
	uports[port].loop = loop;

	if(SOCKET_ERROR == setsockopt(uports[port].s, IPPROTO_IP, IP_MULTICAST_LOOP,
		(const char*)&uports[port].loop,sizeof(uports[port].loop))){
		printf("Set udp sock loop ERROR!\n");
		return -1;
	}
	return 0;
}

int vudp_set_ttl(int port, int ttl)
{
	if(port < 0 || port >= UDPPORTSCOUNT){
		return -1;
	}
	
	uports[port].ttl = ttl;

	if(SOCKET_ERROR == setsockopt(uports[port].s, IPPROTO_IP, IP_MULTICAST_TTL,
		(const char*)&uports[port].ttl, sizeof(uports[port].ttl))){
		printf("Set udp sock ttl ERROR!\n");
		return -1;
	}
	
	return 0;
}

unsigned char vudp_get_mask(int port)
{
	if(port < 0 || port >= UDPPORTSCOUNT){
		return 0;
	}

	return uports[port].mask;
}

int vudp_get_loop(int port)
{
	if(port < 0 || port >= UDPPORTSCOUNT){
		return 0;
	}

	return uports[port].loop;
}

int vudp_get_ttl(int port)
{
	if(port < 0 || port >= UDPPORTSCOUNT){
		return 0;
	}
	return uports[port].ttl;
}

static void vudp_recv_thread(void *p)
{
	int ret, len, port;
	int i;
	char recvbuf[VNET_MTU];
	struct sockaddr_in from;

	port = *(int*)p;
	k_free(p);

	uports[port].bind=1;

#ifdef _LINUX
	from.sin_family = AF_INET;
	for(i = 0; i < intfCount; i++){	
		if(uports[port].mask & (1 << i)){
			from.sin_addr.s_addr = intfs[i].ip.s_addr;	//Notice.....Modified
			printf("i is %d, s_addr is %d\n", i, intfs[i].ip.s_addr);
		}
	}
	//from.sin_addr.s_addr = htonl(INADDR_ANY);
	from.sin_port = htons(port);
#endif

	while(uports[port].bind){
		len = sizeof(struct sockaddr_in);
		if((ret = recvfrom(uports[port].s, recvbuf, VNET_MTU, 0,(struct sockaddr *)&from, &len)) != SOCKET_ERROR){
			//printf("ret == %d, from %d\n", ret, from.sin_addr.s_addr);			
			uports[port].rev(ret, recvbuf);
		}else{
			printf("Udp sock recv ERROR!\n");
		}
	}

	closesocket(uports[port].sm);
	//closesocket(uports[port].sr);

	uports[port].bind = 0;
}

int vudp_hook(int port, frecv hook)
{
	struct sockaddr_in  local, remote;
	int bind_reuse = 1;
	int *pi;
	int i;

#ifdef _LINUX
	struct ip_mreq  mul_addr;
#endif

	if(port < 0 || port >= UDPPORTSCOUNT){
		return -1;
	}
	
	uports[port].rev = hook;

#ifdef _WIN32		
	uports[port].s = WSASocket(AF_INET, SOCK_DGRAM, 0, NULL, 0,
                  WSA_FLAG_MULTIPOINT_C_LEAF
				  | WSA_FLAG_MULTIPOINT_D_LEAF 
				  | WSA_FLAG_OVERLAPPED);

	local.sin_family = AF_INET;
	local.sin_port   = htons((unsigned short)(BASE_PORT+port));
	for(i = 0; i < intfCount; i++){
		if(uports[port].mask & (1 << i)){
			local.sin_addr = intfs[i].ip;	//Notice.....Modified
		}
	}
#endif

	if(SOCKET_ERROR == setsockopt(uports[port].s, SOL_SOCKET, SO_REUSEADDR, (char*)&bind_reuse,sizeof(bind_reuse))){
		printf("Set udp sock reuse ERROR!\n");			
		return -1;
	}

	if(bind(uports[port].s, (struct sockaddr *)&local, sizeof(local)) == SOCKET_ERROR){
   		printf("Bind udp sock ERROR!\n");
		return -1;
   	}

#ifdef _WIN32	
   remote.sin_family = AF_INET;
   remote.sin_port = htons((unsigned short)(BASE_PORT + port));
   remote.sin_addr.s_addr = inet_addr(INADDR_VBUS);

   if((uports[port].sm = WSAJoinLeaf(uports[port].s, (SOCKADDR *)&remote, 
        		sizeof(remote),NULL,NULL,NULL,NULL,JL_BOTH)) == INVALID_SOCKET){		
       printf("JoinLeaf udp sockm Invalid!\n"); 
	   return -1;
	}
#endif

#ifdef _LINUX
	mul_addr.imr_multiaddr.s_addr = inet_addr(INADDR_VBUS);
	for(i = 0; i < intfCount; i++){
		if(uports[port].mask & (1 << i)){
			mul_addr.imr_interface.s_addr = intfs[i].ip.s_addr;	//Notice.....Modified
			printf("i is %d, s_addr is %d\n", i, intfs[i].ip.s_addr);
		}
	}
	//mul_addr.imr_interface.s_addr = inet_addr("200.200.10.2");
	
	if(mul_addr.imr_multiaddr.s_addr == -1){
		printf("mul_addr is not a legal multicast address!\n");
	}
	
	if(SOCKET_ERROR == setsockopt(uports[port].s, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mul_addr, sizeof(mul_addr))){		
		printf("Set udpsock multicast ERROR!\n");        
		return -1;
	}
#endif

	uports[port].bind = 1;
	pi = k_malloc(sizeof(int));
	*pi = port;
	k_thread_start(vudp_recv_thread,pi);

	return 0;
}

void vudp_unhook(int port)
{
	if(port < 0 || port >= UDPPORTSCOUNT){
		return;
	}
	
	uports[port].bind = 0;
}

int vudp_send(int port, char *p, int len)
{
	int i;
	struct sockaddr_in recipient;

	recipient.sin_family = AF_INET;
	recipient.sin_port = htons((unsigned short)(BASE_PORT + port));
	recipient.sin_addr.s_addr = inet_addr(INADDR_VBUS);

	if(port < 0 || port >= UDPPORTSCOUNT){
		return -1;
	}
	
	//printf("intfCount is %d\n", intfCount);

	for(i = 0; i < intfCount; i++){
		if(uports[port].mask & (1 << i)){
			if(SOCKET_ERROR == setsockopt(uports[port].s, IPPROTO_IP, IP_MULTICAST_IF, (char*)&intfs[i].ip, sizeof(intfs[i].ip))){
				printf("Set udpsock send interface ERROR!\n");
				return -1;
			}
			//test
			//printf("udpsend IP is 'NO.%d'\n", i);

			if(SOCKET_ERROR == sendto(uports[port].s, p, len, 0, (struct sockaddr *)&recipient, sizeof(recipient))){
				printf("Udp sock sendto ERROR!\n");
				return -1;
			}
		}
	}
	return 0;
}
