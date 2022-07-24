/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.							                      *
*                                                                            *
*  @file     geoSingletion.h                                                     *
*  @brief    单例模式模板                            *
*																			 *
*
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
*  2016/09/24 | 1.0.0.1   | George.Kuo      | Create file                    *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/
#ifndef  GEOSYS_UTILS_SINGLETON_H__
#define  GEOSYS_UTILS_SINGLETON_H__
#include "geoBasicType.h"
#include <mutex>
#include "geoUtils.h"
using namespace std;


template <class T>
class  SingletonGrabber
{
private:
	 T* m_pInstance;
	 unsigned int m_nRefernce;
	 mutex m_Mutex;
public:
	SingletonGrabber();
	~SingletonGrabber();

	T* GetInstance();
};

//template <class T>
//T* SingletonGrabber<T>::m_pInstance = nullptr;

//template <class T>
//unsigned int SingletonGrabber<T>::m_nRefernce = 0;

template <class T>T* SingletonGrabber<T>::GetInstance() { return m_pInstance; }

//template <class T> mutex SingletonGrabber<T>::m_Mutex;

template <class T>
SingletonGrabber<T>::SingletonGrabber()
{
	if (m_pInstance == nullptr)
	{
		std::lock_guard<std::mutex> lock(m_Mutex);

		if (m_pInstance == nullptr)
		{

			GEO_NEW_NORETURN(m_pInstance, T);
		}
	}
	m_nRefernce++;
}

template <class T>
SingletonGrabber<T>::~SingletonGrabber()
{
	m_nRefernce--;
	if (m_nRefernce == 0)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}


#endif


