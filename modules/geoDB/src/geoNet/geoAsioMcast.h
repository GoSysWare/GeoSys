/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.  using C++ std::thread                       *
*                                                                            *
*  @file     GeoAsioMcast.h                                            *
*  @brief    多播处理类                                                      *
*																			 *
*  运用asio库，采用code嵌入在本系统中，采用异步IO来实现，保证效率
*  详见：http://think-async.com/
*  采用no-boost模式,不依赖繁重的boost库
*  
*
*  @author   George.Kuo                                                      *
*  @email    guooujie@163.com												 *
*  @version  1.0.0.1(版本号)                                                 *
*  @date     2016.8															 *
*  @license																	 *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : 必须在支持C++11环境下编译通过                            *
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
* @brief 异步非阻塞的多播类
*    
*  采用ASIO来处理多播，可以作为服务端也可以作为客户端
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