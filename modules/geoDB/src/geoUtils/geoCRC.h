/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.  using C++ std::thread                       *
*                                                                            *
*  @file     geoCRC.h                                                     *
*  @brief    CRC校验处理函数                                                      *
*																			 *
*  其中封装了通用的CRC校验方法
*
*  @author   George.Kuo                                                      *
*  @email    guooujie@163.com												 *
*  @version  1.0.0.1(版本号)                                                 *
*  @date     2016.8															 *
*  @license																	 *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         :									                         *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  2016/08/24 | 1.0.0.1   | George.Kuo      | Create file                    *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

//
//名称       生成多项式								简记式*		标准引用
//CRC - 4       x4 + x + 1							3			ITU G.704
//CRC - 8       x8 + x5 + x4 + 1					0x31
//CRC - 8       x8 + x2 + x1 + 1					0x07
//CRC - 8       x8 + x6 + x4 + x3 + x2 + x1			0x5E
//CRC - 12      x12 + x11 + x3 + x + 1				80F
//CRC - 16      x16 + x15 + x2 + 1					8005		IBM SDLC
//CRC16 - CCITT x16 + x12 + x5 + 1					1021		ISO HDLC, ITU X.25, V.34 / V.41 / V.42, PPP - FCS
//CRC - 32      x32 + x26 + x23 + ... + x2 + x + 1	04C11DB7	ZIP, RAR, IEEE 802 LAN / FDDI, IEEE 1394, PPP - FCS
//CRC - 32c     x32 + x28 + x27 + ... + x8 + x6 + 1	1EDC6F41	SCTP

#ifndef  GEOSYS_UTILS_CRC_H__
#define  GEOSYS_UTILS_CRC_H__

#include"geoBasicType.h"
#include"geoUtils.h"

/// Computes CRC-CCITT for the string.
extern GEO_UITLS_API geoUInt16 crc_ccitt(const char *str);

/// Computes CRC-CCITT for the buffer.
extern GEO_UITLS_API geoUInt16 crc_ccitt(const void *buf, size_t len,
	geoUInt16 crc = 0);

/// Computes CRC-CCITT for the @ len iovec buffers.
extern GEO_UITLS_API geoUInt16 crc_ccitt(const geoBlob *iov, int len,
	geoUInt16 crc = 0);

/// Computes the ISO 8802-3 standard 32 bits CRC for the string.
extern GEO_UITLS_API geoUInt32 crc32(const char *str);

/// Computes the ISO 8802-3 standard 32 bits CRC for the buffer.
extern GEO_UITLS_API geoUInt32 crc32(const void *buf, size_t len,
	geoUInt32 crc = 0);

/// Computes the ISO 8802-3 standard 32 bits CRC for the
/// @ len iovec buffers.
extern GEO_UITLS_API geoUInt32 crc32(const geoBlob *iov, int len,
	geoUInt32 crc = 0);



#endif