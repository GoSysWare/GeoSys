/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.						                         *
*                                                                            *
*  @file     geoTagTree.h                                            *
*  @brief    实时库内核数据结构                                             *
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
*  Remark         : 必须在支持C++11环境下编译通过                            *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  2016/10/24 | 1.0.0.1   | George.Kuo      | Create file                    *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/
#ifndef  GEOSYS_RTDB_TAG_TREE_H__
#define  GEOSYS_RTDB_TAG_TREE_H__




#include"geoBasicType.h"
#include "geoRTDBMacro.h"
#include <assert.h>
#include <vector>

/// <summary> 
///	遍历过程中的处理函数
/// </summary> 
class CTagTree;

typedef geoAPIStatus(*ListFunction) (CTagTree*, geoUInt32 unTagId);

class TestCase_Iterator;
class CTagTree_Iterator_Base;
class CTagTree_Iterator;
class CTagTree_Reverse_Iterator;
class CTagTree
{

	friend TestCase_Iterator;

	friend geoAPIStatus IsNotUnique(CTagTree* pTagTree, geoUInt32 unTagId);

	friend CTagTree_Iterator_Base;
	friend CTagTree_Iterator;
	friend CTagTree_Reverse_Iterator;
	typedef CTagTree_Iterator  iterator;
	typedef CTagTree_Reverse_Iterator Reverse_iterator;

public:
	geoTagRecordBase* m_pData;
	std::vector<geoInt8>  m_Data_Dirty;

	size_t m_nSize;
	geoBool IsExist(geoUInt32 unTagId)const
	{
		assert(m_pData != geoNULL);
		// 不处理根结点
		return (unTagId >= 0 && unTagId<m_nSize && !IsDeleted(unTagId));
	}
	geoBool IsDeleted(geoUInt32 unTagId)const
	{
		assert(m_pData != geoNULL);
		assert(unTagId<m_nSize);
		return (m_pData[unTagId].Flag.Deleted == 1);
	}
	geoVoid SetDirtyFlag(geoUInt32 unTagId)
	{
		assert(m_pData != geoNULL);
		assert(unTagId<m_nSize);
		m_Data_Dirty[unTagId] = 1;
	}
	CTagTree();
	~CTagTree(void);
protected:

protected:

	geoAPIStatus PreOrder(geoQueryArea* pQueryArea, ListFunction pFunction);

	geoAPIStatus PrevOrderBinTree(
		geoUInt32 nCurrentTagId,
		geoUInt16 nLevel,
		geoUInt16 nCurrentLevel,
		ListFunction pFunction);

	geoAPIStatus PostOrder(geoQueryArea* pQueryArea, ListFunction pFunction);

	geoAPIStatus PostOrderBinTree(
		geoUInt32 nCurrentTagId,
		geoUInt16 nLevel,
		geoUInt16 nCurrentLevel,
		ListFunction pFunction);

	geoAPIStatus DelTagRelation(geoUInt32 nDelTagId);

	geoAPIStatus ClearTagRelation(geoUInt32 nClearTagId);

	geoAPIStatus AddTagRelation(geoUInt32 AddTagId, geoUInt32 nParentTagId);

	//删除节点
	geoAPIStatus DelTag(geoUInt32 nDelTagId);

	//增加节点
	geoAPIStatus AddTag(geoUInt32 nParentTagId, geoUInt32* pnNewTagId);

	geoAPIStatus Move(geoUInt32 nSourceTagId, geoUInt32 nParentTagId);

	geoAPIStatus Copy_i(geoUInt32 nSourceTagId, geoUInt32 nParentTagId, geoUInt32* pnNewTagI);
public:
	geoUInt32 SubTagCount(geoUInt32 unTagId);
	//判断是否为父节点
	geoAPIStatus IsParent(geoUInt32 ParentId, geoUInt32 ChildId, geoBool* pbRet);

	//判断是否为祖先节点
	geoAPIStatus IsAncestor(geoUInt32 AncestorId, geoUInt32 DescendantId, geoBool* pbRet);

	geoBool IsNode(geoUInt32 unTagId)
	{
		assert(IsExist(unTagId));
		return m_pData[unTagId].Flag.IsNode == geoTRUE;
	}

	geoVoid SetIsNodeFlag(geoUInt32 unTagId)
	{
		assert(IsExist(unTagId));
		m_pData[unTagId].Flag.IsNode = geoTRUE;
	}
	geoAPIStatus Del_i(geoUInt32 nDelTagId);
};


class CTagTree_Iterator_Base :public iter_info
{
public:
	const CTagTree & TagTree_;
	const geoUInt32 Iter_root() const { return iter_root; }
	const geoUInt32 Curr() const { return curr_tag; }
	CTagTree_Iterator_Base(const CTagTree &tagtree, geoUInt32 unTagId)
		:TagTree_(tagtree)
	{
		iter_root = unTagId;
		curr_level = 0;
		iter_last = BTree_GetLast(iter_root);
	}
	CTagTree_Iterator_Base(const CTagTree &tagtree, geoUInt32 unTagId, geoUInt16 uslevel)
		:TagTree_(tagtree)
	{
		iter_root = unTagId;
		curr_level = 0;
		level = uslevel;
		iter_last = BTree_GetLast(iter_root);
	}
	virtual ~CTagTree_Iterator_Base()
	{

	}
	geoTagRecordBase & operator* (void) const;
	virtual int  advance() = 0;
	virtual int  advance_dyna() = 0;

	virtual geoUInt32 next(geoTagRecordBase *&next_item) = 0;
	virtual int done(void) = 0;

	geoVoid Up()
	{
		curr_tag = TagTree_.m_pData[curr_tag].ParentId;
		curr_level--;
	}

	geoUInt32 BTree_GetLast(geoUInt32 tag)
	{
		assert(TagTree_.IsExist(tag));
		if (TagTree_.m_pData[tag].FirstChildId != geoTagId_Unused)
		{
			return BTree_GetLast(TagTree_.m_pData[TagTree_.m_pData[tag].FirstChildId].PrevId);
		}
		else
		{
			return tag;
		}
	}
	geoUInt32 BTree_GetNext(geoUInt32 tag)
	{

		if (TagTree_.m_pData[tag].NextId != geoTagId_Unused&&TagTree_.m_pData[tag].NextId != TagTree_.m_pData[TagTree_.m_pData[tag].ParentId].FirstChildId)
		{
			return TagTree_.m_pData[tag].NextId;
		}
		else
		{
			curr_level--;
			return BTree_GetNext(TagTree_.m_pData[tag].ParentId);
		}
	}
	geoVoid forward()
	{
		if (TagTree_.m_pData[curr_tag].FirstChildId != geoTagId_Unused)
		{
			curr_tag = TagTree_.m_pData[curr_tag].FirstChildId;
			curr_level++;
		}
		else if (TagTree_.m_pData[curr_tag].NextId != TagTree_.m_pData[TagTree_.m_pData[curr_tag].ParentId].FirstChildId)
		{
			curr_tag = TagTree_.m_pData[curr_tag].NextId;
		}
		else
		{
			curr_tag = BTree_GetNext(TagTree_.m_pData[curr_tag].ParentId);
			curr_level--;
		}
	}

	geoVoid backward(geoVoid)
	{
		if (TagTree_.m_pData[curr_tag].PrevId != curr_tag)
		{
			curr_tag = BTree_GetLast(TagTree_.m_pData[curr_tag].PrevId);
		}
		else
		{
			curr_tag = TagTree_.m_pData[curr_tag].ParentId;
		}
	}
	geoUInt32 getbackward(geoVoid)
	{
		if (TagTree_.m_pData[curr_tag].PrevId != geoTagId_Unused)
		{
			return BTree_GetLast(TagTree_.m_pData[curr_tag].PrevId);
		}
		else
		{
			return TagTree_.m_pData[curr_tag].ParentId;
		}
	}


	geoInt32 isroot(void)
	{
		if (iter_root == curr_tag)
		{
			return 1;
		}
		return 0;
	};

	geoInt32 islast(void)
	{
		if (curr_tag == BTree_GetLast(iter_root))
		{
			return 1;
		}
		return 0;
	}

	geoInt32 isoriglast(void)
	{
		if (curr_tag == iter_last)
		{
			return 1;
		}
		return 0;
	}



	geoUInt32 getforward(geoVoid)
	{

		if (TagTree_.m_pData[curr_tag].FirstChildId != geoTagId_Unused)
		{
			return TagTree_.m_pData[curr_tag].FirstChildId;
		}
		else if (TagTree_.m_pData[curr_tag].NextId != geoTagId_Unused)
		{
			return TagTree_.m_pData[curr_tag].NextId;
		}
		else
		{
			return BTree_GetNext(TagTree_.m_pData[curr_tag].ParentId);
		}
	};


};

class CTagTree_Iterator :public CTagTree_Iterator_Base
{
public:
	CTagTree_Iterator(const CTagTree &tagtree, geoUInt32 unTagId)
		:CTagTree_Iterator_Base(tagtree, unTagId)
	{
		curr_tag = unTagId;
	}
	CTagTree_Iterator(const CTagTree &tagtree, geoUInt32 unTagId, geoUInt16 usLevel)
		:CTagTree_Iterator_Base(tagtree, unTagId, usLevel)
	{
		curr_tag = unTagId;
	}


	geoUInt32 next(geoTagRecordBase *&next_item)
	{
		if (!done())
		{
			next_item = &TagTree_.m_pData[getforward()];
			return geoRET_SUCC;
		}
		else
		{
			return 1;
		}

	};
	/// <summary>
	/// 移动到下一个，如果已经遍历到同层次的点，返回0，如果继续遍历本结点的子结点，返回1，如果访问比自己层次高的结点，返回目的层次和本层次的差，取负数
	/// <summary>
	virtual int advance(void)
	{
		if (done())
		{
			return Iter_Done;
		}
		forward();
		return 0;
	}
	virtual int advance_dyna(void)
	{
		if (islast())
		{
			return Iter_Done;
		}
		forward();
		return 0;
	}


	/// <summary>
	/// 如果已经遍历了所有点，返回1，否则返回0
	/// <summary>
	inline int done(void)
	{
		return isoriglast();
	};
};


class CTagTree_Reverse_Iterator :public CTagTree_Iterator_Base
{
public:
	CTagTree_Reverse_Iterator(const CTagTree &tagtree, geoUInt32 unTagId)
		:CTagTree_Iterator_Base(tagtree, unTagId)
	{
		if (TagTree_.m_pData[unTagId].FirstChildId == geoTagId_Unused)
		{
			curr_tag = unTagId;
		}
		else
		{
			curr_tag = BTree_GetLast(unTagId);
		}
	}
	CTagTree_Reverse_Iterator(const CTagTree &tagtree, geoUInt32 unTagId, geoUInt16 usLevel)
		:CTagTree_Iterator_Base(tagtree, unTagId, usLevel)
	{
		if (TagTree_.m_pData[unTagId].FirstChildId == geoTagId_Unused)
		{
			curr_tag = unTagId;
		}
		else
		{
			curr_tag = BTree_GetLast(unTagId);
		}
	}
	geoUInt32 next(geoTagRecordBase *&next_item)
	{
		if (!done())
		{
			next_item = &TagTree_.m_pData[getbackward()];
			return geoRET_SUCC;
		}
		else
		{
			return 1;
		}

	};
	/// <summary>
	/// 移动到下一个，如果已经遍历到此次查询的根结点，返回0，否则返回1
	/// <summary>
	virtual int advance(void)
	{
		if (!done())
		{
			backward();
			return 1;
		}
		else
			return 0;
	}

	/// <summary>
	/// 移动到下一个，如果已经遍历到此次查询的根结点，返回0，否则返回1
	/// <summary>
	virtual int advance_dyna(void)
	{
		if (!done())
		{
			backward();
			return 1;
		}
		else
			return 0;
	}


	/// <summary>
	/// 如果已经遍历了所有点，返回1，否则返回0
	/// <summary>
	int done(void)
	{
		return isroot();
	};
};


#endif

