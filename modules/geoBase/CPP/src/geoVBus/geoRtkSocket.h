/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.						                         *
*                                                                            *
*  @file     geoRtkSocket.h                                            *
*  @brief    socket通信处理类                                                      *
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
#ifndef GEOSYS_NET_RTKUDPSOCKT_H_ 
#define GEOSYS_NET_RTKUDPSOCKT_H_



#include "geoBasicType.h"
#include "geoAsioMcast.hh"

/**
* @class GeoRtkSocket
* @brief 网络通信处理类，这个跟数据的业务有关系了，
*    后续把网络模块与Vbus模块分拆,Net模块只有各种标准的TCP UDP 串口等通信底层，跟业务无关
*
*/
class  GeoRtkSocket : public GeoAsioMcast
{
public:
	GeoRtkSocket();
	GeoRtkSocket(geoUInt16 port, const geoChar * mcast_addr);
	virtual ~GeoRtkSocket();
	//同步接收数据处理
	virtual geoInt32 OnReceive(geoInt32 nErrorCode);
	//异步接收的处理
	geoInt32 OnReceive();
	inline virtual void OnPacket(geoRtkPacket_ptr packet, geoInt32 /* len */){};
	geoUInt16 RemotePort();

protected:
	virtual geoBool WillingToAccept(geoRtkPacket_ptr p){
		return geoTRUE;
	}
	enum {
		cached_packets=16,
	};
	/* a ring buffer */
	geoPacketID		cached_packet_ids[cached_packets];
	geoInt32			head;
	ACE_INET_Addr	peerAddress;
	//同步接收的缓冲
	geoChar buffer[VBUS_MAX_PACKET_SIZE];
	//异步IO的接收缓冲区
	ACE_Message_Block *recv_msg_buff;
public:	
	geoRtkTime  cached_packet_times [cached_packets];
	geoUInt32	in_packets; 
	geoUInt32	out_packets;
	geoUInt32   duplicated_packets;
	geoInt64	in_bytes; 
	geoInt64 	out_bytes;
	double	    total_delay;
};
#endif

