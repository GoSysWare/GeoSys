//=============================================================================
/**
* COPYRIGHT NOTICE
* Copyright(c) 2012, CNCS All rights reserved. 
* @file MulticastSocket.h
* @date 2014-03-03
* @author CNCS-0136
* @version 2.0.1
* @brief 多播类
*
* @warning  
*/
//=============================================================================

#ifndef __NICSYS_MULTICASTSOCKET_H_
#define __NICSYS_MULTICASTSOCKET_H_


#include "ace/SOCK_Dgram_Mcast.h"

#include "nicDefines.h"

#define MAX_INTERFACE_NUM 4

/**
* @class CMulticastSocket
* @brief 多播类
*
* 多播类，兼容单播方式
* 多播时利用JoinGroup，recv，sendto
* 单播时利用create，recv，sendto
* 注意：此处还可以补充当操作系统在线修改IP时，对多播组的处理
*/
class   CMulticastSocket: public ACE_SOCK_Dgram_Mcast
{
public:
	CMulticastSocket();
	virtual ~CMulticastSocket();
	nicInt32 Create(nicInt32 port);
	nicInt32 Close();
	nicInt32 JoinGroup(nicStr strMultiGroupIP,nicInt32 nPort, nicInt32 nTTL= 255,bool bLooBack= true);
	nicInt32 LeaveGroup();
	nicVoid  RejoinGroup();
	nicInt32 ReceiveFrom(nicVoid * buf, nicInt32 len, ACE_INET_Addr& addr);
	nicInt32 ReceiveFrom(nicVoid * buf,nicInt32 len,nicChar * addr,nicInt32 & port);
	nicInt32 SendTo(nicVoid *buf,nicInt32 len,nicChar * addr,nicInt32 port);
	nicInt32 SendTo(nicVoid *buf, nicInt32 len, ACE_INET_Addr &addr);
	nicInt32 SendTo(nicVoid *buf, nicInt32 len);
	virtual nicInt32 OnReceive(nicInt32 nErrorCode);
	virtual nicInt32 OnData(nicVoid * buf,nicInt32 len,nicInt32 port,nicChar * src_addr);
private:
	nicChar m_group_ip[16];
	nicInt32  m_group_port;
	nicInt32  m_group_loopback;
	nicInt32  m_group_ttl;	

protected:

	//记录加入多播组的网卡地址
	ACE_INET_Addr  m_joined_addr[MAX_INTERFACE_NUM];
	//地址的字符串形式
	char m_strIPAddr[128];
	//实际加入的有效的网卡IP地址数量
	int m_joined_addr_num;
};


#endif