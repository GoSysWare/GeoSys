

#include "geoTagTree.h"
#include"geoError.hh"


geoAPIStatus DeleteFunction(CTagTree* pTagTree, geoUInt32 unTagId)
{

	assert(pTagTree->IsExist(unTagId));
	return   0;
	
//	return (reinterpret_cast<CTagVector*>(pTagTree))->DelTag(unTagId);
}

geoAPIStatus IsExist(CTagTree* pTagTree, geoUInt32 unTagId)
{

	return pTagTree->IsExist(unTagId) ? geoRET_SUCC : geoERR_TAG_NOT_EXIST;
}


//CTagTree 测点的树结构
CTagTree::CTagTree() {

}

CTagTree::~CTagTree() {

}

geoAPIStatus CTagTree::PreOrder(geoQueryArea* pQueryArea, ListFunction pFunction)
{

	assert(pQueryArea != geoNULL);
	assert(pFunction != geoNULL);
	geoAPIStatus nRet;
	if (pQueryArea->QuerySelf)
	{
		RET_ERR(pFunction(this, pQueryArea->RootTagId));
	}
	if (pQueryArea->QueryLevel>0)
	{
		if (m_pData[pQueryArea->RootTagId].FirstChildId != geoTagId_Unused)
		{
			RET_ERR(PrevOrderBinTree(
				m_pData[pQueryArea->RootTagId].FirstChildId,
				pQueryArea->QueryLevel,
				1,
				pFunction));
		}
	}
	return geoRET_SUCC;
}

geoAPIStatus CTagTree::PrevOrderBinTree(
	geoUInt32 nCurrentTagId,
	geoUInt16 nLevel,
	geoUInt16 nCurrentLevel,
	ListFunction pFunction)
{

	assert(IsExist(nCurrentTagId));

	geoUInt32 nTempId = nCurrentTagId;
	geoAPIStatus nRet = geoRET_SUCC;
	do
	{

		RET_ERR(pFunction(this, nTempId));
		nTempId = m_pData[nTempId].NextId;
	} while (nTempId != nCurrentTagId);

	if (nCurrentLevel >= nLevel)
	{
		return geoRET_SUCC;
	}

	nTempId = nCurrentTagId;
	do
	{
		if (m_pData[nTempId].FirstChildId != geoTagId_Unused)
		{
			RET_ERR(PrevOrderBinTree(
				m_pData[nTempId].FirstChildId,
				nLevel,
				nCurrentLevel + 1,
				pFunction));
		}
		nTempId = m_pData[nTempId].NextId;
	} while (nTempId != nCurrentTagId);


	return geoRET_SUCC;
}

geoAPIStatus CTagTree::PostOrder(geoQueryArea* pQueryArea, ListFunction pFunction)
{

	assert(pQueryArea != geoNULL);
	assert(pFunction != geoNULL);
	geoAPIStatus nRet;
	if (pQueryArea->QueryLevel>0)
	{
		if (m_pData[pQueryArea->RootTagId].FirstChildId != geoTagId_Unused)
		{
			RET_ERR(PostOrderBinTree(m_pData[pQueryArea->RootTagId].FirstChildId, pQueryArea->QueryLevel, 1, pFunction));
		}
	}
	if (pQueryArea->QuerySelf)
	{
		RET_ERR(pFunction(this, pQueryArea->RootTagId));
	}
	return geoRET_SUCC;
}

geoAPIStatus CTagTree::PostOrderBinTree(
	geoUInt32 nCurrentTagId,
	geoUInt16 nLevel,
	geoUInt16 nCurrentLevel,
	ListFunction pFunction)
{

	assert(IsExist(nCurrentTagId));
	geoAPIStatus nRet = geoRET_SUCC;
	geoUInt32 nTempId = nCurrentTagId;
	if (nCurrentLevel<nLevel)
	{
		do
		{
			if (m_pData[nTempId].FirstChildId != geoTagId_Unused)
			{
				RET_ERR(PostOrderBinTree(
					m_pData[nTempId].FirstChildId,
					nLevel,
					nCurrentLevel + 1,
					pFunction));
			}
			nTempId = m_pData[nTempId].NextId;
		} while (nTempId != nCurrentTagId);
	}

	nTempId = nCurrentTagId;
	do
	{
		RET_ERR(pFunction(this, nTempId));
		nTempId = m_pData[nTempId].NextId;
	} while (nTempId != nCurrentTagId);

	return geoRET_SUCC;
}

//************************************
// Method:    删除节点
// FullName:  CTagTree::DelTag
// Access:    public
// Returns:   geoAPIStatus
// Qualifier:
// Parameter: geoUInt32 nDelTagId
//************************************
// 1、可以同时遍历同时删除子结点，不需要先找出所有的子结点
// 2、加入一个字段，可以使删除链表中最后一个结点的效率更高
// LCB 2008-2-2
geoAPIStatus CTagTree::DelTag(geoUInt32 nDelTagId)
{

	if (!IsExist(nDelTagId))
	{
		return geoERR_TAG_NOT_EXIST;
	}
	CTagTree_Reverse_Iterator iter(*this, nDelTagId);
	geoAPIStatus nRet = geoRET_SUCC;
	if (!iter.done())
	{
		RET_ERR(Del_i(iter.Curr()));
	}
	//出错处理
	return Del_i(nDelTagId);
}

geoAPIStatus CTagTree::Del_i(geoUInt32 nDelTagId)
{

	if (!IsExist(nDelTagId))
	{
		return geoERR_TAG_NOT_EXIST;
	}
	geoAPIStatus nRet;
	RET_ERR(DelTagRelation(nDelTagId));
//	return CTagVector::DelTag(nDelTagId);
	return 0;
}
//-------------------------------------------------------------------------
geoAPIStatus CTagTree::DelTagRelation(geoUInt32 nDelTagId)
{

	assert(IsExist(nDelTagId));
	geoUInt32 nTempId = m_pData[nDelTagId].ParentId;
	if (m_pData[nTempId].FirstChildId == nDelTagId)
	{
		SetDirtyFlag(nTempId);
		if (m_pData[nDelTagId].NextId == nDelTagId)
		{
			m_pData[nTempId].FirstChildId = geoTagId_Unused;
		}
		else
		{
			m_pData[nTempId].FirstChildId = m_pData[nDelTagId].NextId;
		}
	}
	nTempId = m_pData[nDelTagId].PrevId;
	if (nTempId != nDelTagId)
	{
		SetDirtyFlag(nTempId);
		m_pData[nTempId].NextId = m_pData[nDelTagId].NextId;
	}
	nTempId = m_pData[nDelTagId].NextId;
	if (nTempId != nDelTagId)
	{
		SetDirtyFlag(nTempId);
		m_pData[nTempId].PrevId = m_pData[nDelTagId].PrevId;
	}
	SetDirtyFlag(nDelTagId);
	m_pData[nDelTagId].ParentId = geoTagId_Unused;
	m_pData[nDelTagId].PrevId = geoTagId_Unused;
	m_pData[nDelTagId].NextId = geoTagId_Unused;
	return geoRET_SUCC;
}

//-------------------------------------------------------------------------
geoAPIStatus CTagTree::ClearTagRelation(geoUInt32 nClearTagId)
{

	assert(IsExist(nClearTagId));
	m_pData[nClearTagId].ParentId = geoTagId_Unused;
	m_pData[nClearTagId].PrevId = geoTagId_Unused;
	m_pData[nClearTagId].NextId = geoTagId_Unused;
	m_pData[nClearTagId].FirstChildId = geoTagId_Unused;
	return geoRET_SUCC;
}

geoAPIStatus CTagTree::AddTagRelation(geoUInt32 AddTagId, geoUInt32 nParentTagId)
{

	assert(IsExist(AddTagId));
	assert(m_pData[AddTagId].ParentId == geoTagId_Unused);
	assert(m_pData[AddTagId].NextId == geoTagId_Unused);
	assert(m_pData[AddTagId].PrevId == geoTagId_Unused);
	assert(nParentTagId == geoTagId_Root || IsExist(nParentTagId));

	if (m_pData[nParentTagId].FirstChildId == geoTagId_Unused)
	{
		SetDirtyFlag(nParentTagId);
		m_pData[nParentTagId].FirstChildId = AddTagId;
		m_pData[AddTagId].PrevId = AddTagId;
		m_pData[AddTagId].NextId = AddTagId;
	}
	else
	{
		geoUInt32 nFirstId = m_pData[nParentTagId].FirstChildId;
		geoUInt32 nLastId = m_pData[nFirstId].PrevId;

		SetDirtyFlag(nFirstId);
		m_pData[nFirstId].PrevId = AddTagId;

		SetDirtyFlag(nLastId);
		m_pData[nLastId].NextId = AddTagId;

		m_pData[AddTagId].NextId = nFirstId;
		m_pData[AddTagId].PrevId = nLastId;
	}
	//设置新增点相关值
	//SetDirtyFlag(AddTagId);
	m_pData[AddTagId].ParentId = nParentTagId;
	return geoRET_SUCC;
}


//-------------------------------------------------------------------------
geoAPIStatus CTagTree::AddTag(geoUInt32 nParentTagId, geoUInt32* pnNewTagId)
{
	assert(nParentTagId == geoTagId_Root || IsExist(nParentTagId));
	assert(pnNewTagId != geoNULL);

	//添加进动态数组当中。返回在数组中的位置；
	geoAPIStatus nRet = geoRET_SUCC;
//	geoAPIStatus nRet = CTagVector::AddTag(pnNewTagId);
	if (geoFail(nRet))
	{
		return nRet;
	}

	//将nTagId加入到测点树的正确位置
	return AddTagRelation(*pnNewTagId, nParentTagId);
}

//************************************
// Method:    判断节点是否存在
// FullName:  CTagTree::IsExist
// Access:    public
// Returns:   geoBool
// Qualifier:
// Parameter: geoUInt32 unTagId
//************************************

//-------------------------------------------------------------------------
geoAPIStatus CTagTree::IsParent(geoUInt32 nParentTagId, geoUInt32 nChildTagId,
	geoBool* pbRet)
{


	if (nParentTagId != geoTagId_Root && !IsExist(nParentTagId))
	{
		return geoERR_TAG_NOT_EXIST;
	}
	if (!IsExist(nChildTagId))
	{
		return geoERR_TAG_NOT_EXIST;
	}
	assert(m_pData[nChildTagId].ParentId != geoTagId_Unused);
	*pbRet = (m_pData[nChildTagId].ParentId == nParentTagId) ? geoTRUE : geoFALSE;
	return geoRET_SUCC;
}

//-------------------------------------------------------------------------
geoAPIStatus CTagTree::IsAncestor(geoUInt32 nAncestorTagId, geoUInt32
	nDescendantTagId, geoBool* pbRet)
{

	if (nAncestorTagId != geoTagId_Root && !IsExist(nAncestorTagId))
	{
		return geoERR_TAG_NOT_EXIST;
	}
	if (!IsExist(nDescendantTagId))
	{
		return geoERR_TAG_NOT_EXIST;
	}
	geoUInt32 tempId = nDescendantTagId;
	do
	{
		if (m_pData[tempId].ParentId == geoTagId_Unused)
		{
			*pbRet = geoFALSE;
			return geoRET_SUCC;
		}
		tempId = m_pData[tempId].ParentId;
		assert(tempId == geoTagId_Root || IsExist(tempId));
		if (tempId == nAncestorTagId)
		{
			*pbRet = geoTRUE;
			return geoRET_SUCC;
		}
	} while (tempId != geoTagId_Root);
	*pbRet = geoFALSE;
	return geoRET_SUCC;
}

//-------------------------------------------------------------------------
geoAPIStatus CTagTree::Move(geoUInt32 nSourceTagId, geoUInt32 nParentTagId)
{

	if (m_pData[nSourceTagId].ParentId == nParentTagId)
	{
		return geoRET_SUCC;
	}

	//两点之间的关联关系在CTagBaseInfo::Move函数验证，此处不再验证

	//删除nSourceTagId与原来相关点的关联。
	geoAPIStatus nRet = geoRET_SUCC;
	nRet = DelTagRelation(nSourceTagId);
	if (geoFail(nRet))
	{
		return nRet;
	}
	//增加到nParentTagId下
	return AddTagRelation(nSourceTagId, nParentTagId);
}

//-------------------------------------------------------------------------

geoAPIStatus CTagTree::Copy_i(geoUInt32 nSourceTagId, geoUInt32 nParentTagId, geoUInt32* pnNewTagId)
{

	//CTagVector::AddTag(pnNewTagId);
	this->m_pData[*pnNewTagId] = this->m_pData[nSourceTagId];
	this->ClearTagRelation(*pnNewTagId);
	this->AddTagRelation(*pnNewTagId, nParentTagId);
	return geoRET_SUCC;
}



geoUInt32 CTagTree::SubTagCount(geoUInt32 unTagId)
{

	CTagTree::iterator iter(*reinterpret_cast<CTagTree*>(this), unTagId);
	geoUInt32 temp = 0;
	if (!iter.done())
	{
		temp++;
		iter.advance();
	}
	return temp;
}


