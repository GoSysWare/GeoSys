/*
 * Copyright (c) 2000-2008
 * Author: Weiming Zhou
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  
 *
 * modified by chenjun @2008
 * - remove unused code
 *
 */


#ifndef __CAPIGLOBAL_H__
#define __CAPIGLOBAL_H__

#include <memory.h>
#ifdef __cplusplus
extern "C" {
#endif

#define CAPI_SUCCESS        0
#define CAPI_FAILED         1

typedef unsigned int    UINT;
typedef int             INT;
typedef void * HANDLE;


/**	ͨ���������ݱȽϺ���

	@param	void *pData1 -Ҫ�Ƚϵĵ�1������	
	@param	void *pData2 -Ҫ�Ƚϵĵ�2������	
        @return	INT - С��0��ʾpData1С��pData2, ����0��ʾpData1����pData2,
                  ����0��ʾpData1����pData2
*/
typedef INT (*COMPAREFUNC) ( void *pData1, void *pData2 );

/**	ͨ�����������ͷź���

	@param	void *pData -Ҫ�ͷŵ�����	
	@return	 -��	
*/
typedef void (*DESTROYFUNC) ( void *pData );

/**	ͨ���������ݵı���ִ�к���

	@param	void *pData - Ҫ����������ָ��	
	@return	void - ��	
*/
typedef void (*TRAVERSEFUNC)( void *pData );


/**	ͨ���������ݵı���ִ�к���

	@param	void *pData - Ҫ����������ָ��	
	@return	void - ��	
*/
typedef INT (*VISITFUNC)(void *pData);

/**	ͨ�����ݿ�������

	@param	void *pData - Ҫ����������	
	@return	void * - �ɹ����ؿ��������ݣ�ʧ�ܷ���NULL	
*/
typedef void *(*COPYFUNC)(void *pData);

/**	��������Ļ�ȡ�ؼ���ת������ŵĺ���

	@param	void *pData - �ؼ���ָ��	
    @param	UINT *uKeyIndex - �ؼ��ֵ�λ��	
	@return	UINT - �ؼ���ת��������	
*/
typedef UINT (*GETKEYFUNC)( void *pData, UINT uKeyIndex );

/**	�����ϣֵ�Ļص�����

        @param  void *pKey - Ҫ�����ϣֵ�Ĺؼ���	
        @param  UINT uBucketNum - ��ϣ���е�BUCKET�����С	
	@return UINT - ���ؼ�����Ĺ�ϣֵ��һ��������ϣ��BUCKET�����±ꡣ	
*/
typedef UINT (*HASHFUNC)(void *pKey, UINT uBucketNum);

#ifdef __cplusplus
}
#endif

#endif /* __CAPIGLOBAL_H__ */
