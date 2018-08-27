#include <stdio.h>
#include "k_config.h"
#include "k_util.h"
#include "k_process.h"
#include "vnet.h"
#include "vtcp.h"

#ifdef _LINUX
#include <sys/types.h>
#include <string.h>
//#include <arpa/inet.h>
//#include <unistd.h>
//#include <netdb.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <stdlib.h>
#endif

#define BASE_PORT 16666
#define TCPPORTSCOUNT 8
#define LISTENCOUNT 8
#define OUTDATE 5

typedef struct SrvPort{
    SOCKET ssc;
    int flag;
}srvport_t;

typedef struct TcpPort{
    SOCKET ssl;
    srvport_t sp[LISTENCOUNT];
    SOCKET scc;
    frecvfrom srvrev;
} tcpport_t;

static tcpport_t ports[TCPPORTSCOUNT];
static int ports_monitor;

typedef struct RecvPara{
    int port;
    int income;
    SOCKET s;
    frecvfrom rev;
}recv_para_t;

#define TCPMAGIC	0x62677772
typedef struct TcpHead{
    int magic;
    int length;
}tcp_head_t;

static int send_packet(SOCKET s, char *buffer, int len)
{
    fd_set sset;
    int bytes;
    int left;
    struct timeval tout;
    tcp_head_t tht;
    tht.magic=TCPMAGIC;
    tht.length=len;

    while(1){
        FD_ZERO(&sset);
        FD_SET(s,&sset);
        tout.tv_sec=1;
        tout.tv_usec=0;
        select((s+1),NULL,&sset,NULL,&tout);
        if(!FD_ISSET(s, &sset)){
            return 0;
        }
        bytes=send(s,(char*)&tht,sizeof(tcp_head_t),0);
        if(bytes==SOCKET_ERROR){
            return 0;
        }
        left=len;
        while(left>0){
            FD_ZERO(&sset);
            FD_SET(s,&sset);
            select((s+1),NULL,&sset,NULL,&tout);
            if(!FD_ISSET(s, &sset)){
                return 0;
            }
            bytes=send(s,buffer,left,0);
            if(bytes==SOCKET_ERROR){
                return 0;
            }
            left-=bytes;
            buffer+=bytes;
        }
        return len;
    }
    return 0;
}

static int recv_packet(SOCKET s, char *buffer)
{
    fd_set sset;
    int bytes;
    int total;
    int left;
    tcp_head_t tht;
    while(1){
        FD_ZERO(&sset);
        FD_SET(s,&sset);
        select((s+1),&sset,NULL,NULL,NULL);
        bytes = recv(s, buffer, TCPBUFSIZE, 0);
        if(bytes==0){
            return bytes;
        }
        if(bytes==SOCKET_ERROR){
            return bytes;
        }
        if(bytes>=8){
            memcpy(&tht, buffer, sizeof(tcp_head_t));
            if(tht.magic==TCPMAGIC && tht.length<=TCPBUFSIZE-sizeof(tcp_head_t)){
                total=tht.length;
                left=total+sizeof(tcp_head_t)-bytes;
                buffer+=bytes;
                while(left > 0){
                    FD_ZERO(&sset);
                    FD_SET(s,&sset);
                    select((s+1),&sset,NULL,NULL,NULL);
                    bytes = recv(s, buffer, total, 0);
                    if(bytes==0){
                        return bytes;
                    }
                    if(bytes==SOCKET_ERROR){
                        return bytes;
                    }
                    left-=bytes;
                    buffer+=bytes;
                }
                return total;
            }
        }
    }

    return 0;
}

static void recv_thread(void *p)
{
    int ret;
    char *buffer;
    recv_para_t para;

    memcpy(&para, p, sizeof(recv_para_t));
    k_free(p);

    if(para.income>=0){
        //if(para.port==1){
        //	printf("Server receive thread start, ssl=%d\n",ports[1].ssl);
        //}
    }else{
        //printf("Client receive thread start\n");
    }

    buffer=k_malloc(TCPBUFSIZE);
    while(1){
        //ret = recv(para.s, buffer, TCPBUFSIZE, 0);
        ret = recv_packet(para.s, buffer);
        if(ret == 0){        // Graceful close
            printf("Graceful close\n");
            break;
        }else if(ret == SOCKET_ERROR){
            printf("Error close\n");
            break;
        }
        //para.rev(para.income, ret, buffer);
        para.rev(para.income, ret, buffer+sizeof(tcp_head_t));
        //printf("recv %d bytes from %d, ssl=%d\n", ret, para.s, ports[1].ssl);
        if(para.port>=0 && para.port<TCPPORTSCOUNT){
            if(para.income >=0){
                ports[para.port].sp[para.income].flag=0;
            }
        }else{
            //printf("fital error!\n");
        }
    }
    //para.rev(-2,0,NULL);
    k_free(buffer);
    vnet_closesocket(para.s);
    if(para.income>=0){
        ports[para.port].sp[para.income].flag=-1;
        //if(para.port==1){
        //	printf("Server receive thread exit, ssl=%d\n",ports[1].ssl);
        //}
        //printf("Server receive thread exit, close %d\n",para.s);
        //}else{
        //printf("Client receive thread exit\n");
    }
}


static void monitor_thread(void *p)
{
    int i, j;

    while(ports_monitor)
    {
        for(i=0; i<TCPPORTSCOUNT; i++)
        {
            for(j=0; j<LISTENCOUNT; j++)
            {
                if(ports[i].sp[j].flag > OUTDATE)
                {
                    //qss:
                   // printf("monitor close port[%d].sp[%d].ssc = %d.\n", i, j, ports[i].sp[j].ssc);
                    vnet_closesocket(ports[i].sp[j].ssc);
                }
                else if(ports[i].sp[j].flag >= 0)
                {
                    ports[i].sp[j].flag++;
                }
            }
        }
        k_sleep(1000);
    }
}

static int get_srvsocket(int port)
{
    int i;

    if(port<0 || port>=TCPPORTSCOUNT){
        return -1;
    }

    for(i=0;i<LISTENCOUNT;i++){
        if(ports[port].sp[i].flag<0){
            return i;
        }
    }

    return -1;
}


static void listen_thread(void *p)
{
    SOCKET sc;
    recv_para_t *prp;
    struct sockaddr_in client;
    int iAddrSize;
    int port, issc;
    int ssl;

    port = *(int*)p;
    k_free(p);
    ssl=ports[port].ssl;

    while(1){

        iAddrSize = sizeof(client);

        sc=accept(ssl,(struct sockaddr *)&client,&iAddrSize);
        if(sc == INVALID_SOCKET){
            k_sleep(1000);
            //continue;
            break;
        }else{
            //printf("accept success: ssl=%d.\n",ports[port].ssl);
        }

        issc=get_srvsocket(port);
        if(issc>=0){
            prp=k_malloc(sizeof(recv_para_t));
            prp->s=sc;
            ports[port].sp[issc].ssc=sc;
            ports[port].sp[issc].flag=0;
            prp->rev=ports[port].srvrev;
            prp->income=issc;
            prp->port=port;
            k_thread_start(recv_thread,prp);
        }else{
            vnet_closesocket(sc);
        }
    }
}

void vtcp_init()
{
    int i,j;

    for(i=0; i<TCPPORTSCOUNT; i++){
        for(j=0; j<LISTENCOUNT; j++){
            ports[i].sp[j].flag = -1;
        }
    }

    ports_monitor = 1;

    k_thread_start(monitor_thread,NULL);

    printf("monitor_thread start.\n");

}

void vtcp_uninit()
{
    ports_monitor=0;
    k_sleep(2000);
}

int vtcp_srvcreate(int port, frecvfrom ondata)
{
    struct sockaddr_in local;
    int bind_reuse = 1;
    int *pi;

    if(port<0 || port>=TCPPORTSCOUNT){
        return 1;
    }

    ports[port].ssl = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (ports[port].ssl == SOCKET_ERROR){
        return 1;
    }

#ifdef _LINUX
    bzero(&local, sizeof(local));
#endif   
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    local.sin_family = AF_INET;
    local.sin_port = htons((unsigned short)(BASE_PORT+port));

    if(setsockopt(ports[port].ssl, SOL_SOCKET, SO_REUSEADDR, (char*)&bind_reuse,sizeof(bind_reuse)) == -1){
        printf("tcp reuse error\n");
        return 1;
    }

    if(bind(ports[port].ssl, (struct sockaddr *)&local,sizeof(struct sockaddr)) == SOCKET_ERROR){
        return 1;
    }

    ports[port].srvrev=ondata;

    listen(ports[port].ssl, LISTENCOUNT);

    pi=k_malloc(sizeof(int));
    *pi=port;

    k_thread_start(listen_thread, pi);

    return 0;
}

int vtcp_srvsend(int port, int income, int len, char *data)
{
    if(income<0 || income>=LISTENCOUNT){
        return -1;
    }
    return send_packet(ports[port].sp[income].ssc,data,len);
}

void vtcp_srvclose(int port)
{
    vnet_closesocket(ports[port].ssl);
}

int vtcp_cltcreate(int port, frecvfrom ondata, char *srvaddr)
{
    struct sockaddr_in server;
    struct hostent *host = NULL;
    recv_para_t *prp;

    //printf("before connect ssl=%d\n", ports[1].ssl);

    ports[port].scc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(ports[port].scc == INVALID_SOCKET){
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons((unsigned short)(BASE_PORT+port));
    server.sin_addr.s_addr = inet_addr(srvaddr);

    if(server.sin_addr.s_addr == INADDR_NONE){
        host = gethostbyname(srvaddr);
        printf("gethostbyname");
        if (host == NULL){
            return 1;
        }
        memcpy(&server.sin_addr,host->h_addr_list[0],host->h_length);
    }

    if (connect(ports[port].scc, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR){
        return 1;
    }

    //printf("after clt create scc:%d ssl:%d\n",ports[1].scc, ports[1].ssl);
    prp=k_malloc(sizeof(recv_para_t));
    prp->income=-1;
    prp->port=port;
    prp->s=ports[port].scc;
    prp->rev=ondata;
    k_thread_start(recv_thread, prp);

    printf("after connect ssl=%d\n", ports[1].ssl);

    return 0;
}

int vtcp_cltsend(int port, int len, char *data)
{
    int ret;
    //printf("before send ssl=%d\n", ports[1].ssl);
    ret = send_packet(ports[port].scc,data,len);
    //printf("after send ssl=%d\n", ports[1].ssl);
    return ret;
}

void vtcp_cltclose(int port)
{
    vnet_closesocket(ports[port].scc);
}
