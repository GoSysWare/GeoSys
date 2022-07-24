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


/**	通用类型数据比较函数
	@param	void *pData1 -要比较的第1个参数	
	@param	void *pData2 -要比较的第2个参数	
        @return	INT - 小于0表示pData1小于pData2, 等于0表示pData1等于pData2,
                  大于0表示pData1大于pData2
*/
typedef INT (*COMPAREFUNC) ( void *pData1, void *pData2 );

/**	通用类型数据释放函数
	@param	void *pData -要释放的数据	
	@return	 -无	
*/
typedef void (*DESTROYFUNC) ( void *pData );

/**	通用类型数据的遍历执行函数
	@param	void *pData - 要操作的数据指针	
	@return	void - 无	
*/
typedef void (*TRAVERSEFUNC)( void *pData );


/**	通用类型数据的遍历执行函数
	@param	void *pData - 要操作的数据指针	
	@return	void - 无	
*/
typedef INT (*VISITFUNC)(void *pData);

/**	通用数据拷贝函数
	@param	void *pData - 要拷贝的数据	
	@return	void * - 成功返回拷贝的数据，失败返回NULL	
*/
typedef void *(*COPYFUNC)(void *pData);

/**	基数排序的获取关键字转换成序号的函数
	@param	void *pData - 关键字指针	
    @param	UINT *uKeyIndex - 关键字的位数	
	@return	UINT - 关键字转换后的序号	
*/
typedef UINT (*GETKEYFUNC)( void *pData, UINT uKeyIndex );

/**	计算哈希值的回调函数
        @param  void *pKey - 要计算哈希值的关键词	
        @param  UINT uBucketNum - 哈希表中的BUCKET数组大小	
	@return UINT - 返回计算出的哈希值，一般用作哈希表BUCKET数组下标。	
*/
typedef UINT (*HASHFUNC)(void *pKey, UINT uBucketNum);

#ifdef __cplusplus
}
#endif

#endif /* __CAPIGLOBAL_H__ */