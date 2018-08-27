/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.  using C++ std::thread                       *
*                                                                            *
*  @file     GeoAsioMcast.h                                            *
*  @brief    �ಥ������                                                      *
*																			 *
*  ����asio�⣬����codeǶ���ڱ�ϵͳ�У������첽IO��ʵ�֣���֤Ч��
*  �����http://think-async.com/
*  ����no-boostģʽ,���������ص�boost��
*  
*
*  @author   George.Kuo                                                      *
*  @email    guooujie@163.com												 *
*  @version  1.0.0.1(�汾��)                                                 *
*  @date     2016.8															 *
*  @license																	 *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : ������֧��C++11�����±���ͨ��                            *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  2016/08/24 | 1.0.0.1   | George.Kuo      | Create file                    *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/


#ifndef  GEOSYS_NET_MULTICAST_H__
#define  GEOSYS_NET_MULTICAST_H__

#include<string>
#include"asio.hpp"


#include"geoNet.h"

#define MAX_PACKET_SIZE  8096
/**
* @class GeoAsioMcast
* @brief �첽�������Ķಥ��
*    
*  ����ASIO������ಥ��������Ϊ�����Ҳ������Ϊ�ͻ���
*/
class  GEO_NET_API GeoAsioMcast
{
public:
	GeoAsioMcast(asio::io_service& io_service);
	~GeoAsioMcast();
	int joinGroup(string  ip, unsigned short port, int nTTL = 255, bool isLoopback = true);
	int leaveGroup();
	int close();
	int sendTo(void * buff, int len);
	int initRecvFrom();
	int onRecieveFrom(int recvlen);
	virtual int onData(void * buff, int len);
	int open(unsigned short port);
	int bind(unsigned short port, string ip = "");
private:

	udp::socket mSocket;
	udp::endpoint mSenderEndpoint;
	unique_ptr<asio::io_service> mService;

	bool mIsMulticast;

	// cached string address
	string mGroupIP;

	unsigned short  mGroupPort;
	bool  mIsGroupLoopback;
	unsigned short  mGroupTTL;

	bool mIsReuseAddr;
	char mDataBuff[MAX_PACKET_SIZE + 1];


};


#endif