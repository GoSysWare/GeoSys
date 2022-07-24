/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.                      *
*                                                                            *
*  @file     geoStringMap.h                                                     *
*  @brief    ����  char * ��hashmap                                                     *
*																			 *
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

#ifndef  GEOSYS_UTILS_STRINGMAP_H__
#define  GEOSYS_UTILS_STRINGMAP_H__

#include <string>
#include<unordered_map>
#include"geoUtils.h"


#define DEFAULT_NAMEHASH_SIZE	4096

///"Hash PJW"�㷨�����Ը�������㷨 
struct hash_func  //hash ����  
{
	size_t operator()(const char* str) const
	{
		unsigned long hash = 0;
		size_t  len = strlen(str);
		for (size_t i = 0; i < len; i++)
		{
			const wchar_t temp = str[i];
			hash = (hash << 4) + (temp * 13);
			unsigned long g = hash & 0xf0000000;

			if (g)
			{
				hash ^= (g >> 24);
				hash ^= g;
			}
		}
		return hash;
	}
};
struct cmp_fun //�ȽϺ��� ==  
{
	bool operator()(const geoChar* str1, const geoChar* str2) const
	{
		return strcmp(str1, str2) == 0 ? true : false;
	}
};


typedef  std::unordered_map<geoChar*, int, hash_func, cmp_fun>   NameHash;
typedef  NameHash::value_type   NameHash_ValueType;
typedef  NameHash::iterator		NameHash_Iter;
typedef  std::pair<NameHash_Iter, bool>		NameHash_Pair;

//std:unordered_mapĬ��char*�ǱȽ�ָ���С����д�ȽϺ�����hashֵ
//�õ�(string,int)��ֵ��
class GEO_UITLS_API GeoStringMap
{
private:
	NameHash  hash_;
public:
	GeoStringMap(geoVoid);
	GeoStringMap(geoUInt32 size);
	~GeoStringMap(geoVoid);
	//���ư�	
	geoAPIStatus bind(geoChar *name, geoUInt32 &id); 
	//����	
	geoAPIStatus find(geoChar *name, geoUInt32 &id);
	//�ж��Ƿ���ڶ���
	geoAPIStatus find(geoChar *name) 
	{
		geoUInt32 nTempId;
		return find(name, nTempId);
	}
	//�����
	geoAPIStatus unbind(geoChar *name, geoUInt32 id = 0); 
	//��ʼ��
	virtual geoAPIStatus init(); 
	geoAPIStatus delete_all_ext_id();
};
#endif
