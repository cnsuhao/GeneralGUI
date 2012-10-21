//-----------------------------------------------------------------------------
// (C) oil
// 2012-10-19
//-----------------------------------------------------------------------------
#include "GGUIStdAfx.h"
#include "GGUIImageset.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	//-----------------------------------------------------------------------------
	bool GGUIImageset::AddImageRect(const GGUITinyString& strRectName, SoFloat fLeft, SoFloat fRight, SoFloat fTop, SoFloat fBottom, ImageRectID* pRectID)
	{
		//判断名字为strRectName的ImageRect是否已经存在。
		ImageRectID alreadyExistRectID = GetImageRectIDByName(strRectName);
		if (alreadyExistRectID != Invalid_ImageRectID)
		{
			//已经存在，添加失败。
			if (pRectID)
			{
				*pRectID = alreadyExistRectID;
			}
			return false;
		}
		//分配一个新的数组元素。
		if (m_nIndexEnd >= m_nCapacity)
		{
			//容器空间不够了，则把容器空间扩大到原来的2倍。
			SoUInt sizeOfOldArray = sizeof(GGUIRect*) * m_nCapacity;
			m_nCapacity *= 2;
			GGUIRect** pNewArray = new GGUIRect*[m_nCapacity];
			SoUInt sizeOfNewArray = sizeof(GGUIRect*) * m_nCapacity;
			memset(pNewArray, 0, sizeOfNewArray);
			memcpy_s(pNewArray, sizeOfNewArray, m_pImageRectID2Rect, sizeOfOldArray);
			SAFE_DELETE_ARRAY(m_pImageRectID2Rect);
			m_pImageRectID2Rect = pNewArray;
		}
		ImageRectID newRectID = m_nIndexEnd;
		++m_nIndexEnd;
		//
		m_pImageRectID2Rect[newRectID] = new GGUIRect(fLeft, fRight, fTop, fBottom);
		m_mapRectName2RectID.insert(std::make_pair(strRectName, newRectID));
		if (pRectID)
		{
			*pRectID = newRectID;
		}
		return true;
	}
	//-----------------------------------------------------------------------------
	void GGUIImageset::RemoveImageRect(ImageRectID theRectID)
	{
		if (theRectID >= 0 && theRectID < m_nIndexEnd)
		{
			//
			if (m_pImageRectID2Rect[theRectID])
			{
				SAFE_DELETE(m_pImageRectID2Rect[theRectID]);
			}
			//
			for (mapRectName2RectID::iterator it = m_mapRectName2RectID.begin();
				it != m_mapRectName2RectID.end();
				++it)
			{
				if (it->second == theRectID)
				{
					m_mapRectName2RectID.erase(it);
					break;
				}
			}
		}
	}
	//-----------------------------------------------------------------------------
	const GGUITinyString* GGUIImageset::GetImageRectNameByID(ImageRectID theRectID)
	{
		GGUITinyString* pResult = NULL;
		for (mapRectName2RectID::iterator it = m_mapRectName2RectID.begin();
			it != m_mapRectName2RectID.end();
			++it)
		{
			if (it->second == theRectID)
			{
				//写成pResult = &(it->first);会报错。
				pResult = (GGUITinyString*)(&(it->first));
				break;
			}
		}
		return pResult;
	}
	//-----------------------------------------------------------------------------
	GGUIImageset::GGUIImageset()
	:m_MyImagesetID(Invalid_ImagesetID)
	,m_MyImagesetName()
	,m_pDXTexture(NULL)
	,m_pImageRectID2Rect(NULL)
	,m_nCapacity(0)
	,m_nIndexEnd(0)
	{
		//初始化GGUIRect数组。
		m_nCapacity = 10;
		m_pImageRectID2Rect = new GGUIRect*[m_nCapacity];
		memset(m_pImageRectID2Rect, 0, sizeof(GGUIRect*)*m_nCapacity);
	}
	//-----------------------------------------------------------------------------
	GGUIImageset::~GGUIImageset()
	{
		//尝试删除贴图。
		SAFE_D3D_RELEASE(m_pDXTexture);
		//
		m_mapRectName2RectID.clear();
		//
		for (SoInt i=0; i<m_nIndexEnd; ++i)
		{
			if (m_pImageRectID2Rect[i])
			{
				SAFE_DELETE(m_pImageRectID2Rect[i]);
			}
		}
		SAFE_DELETE_ARRAY(m_pImageRectID2Rect);
	}
	//-----------------------------------------------------------------------------
	void GGUIImageset::SetDXTexture(IDirect3DTexture9* pTexture)
	{
		//尝试删除旧贴图。
		SAFE_D3D_RELEASE(m_pDXTexture);
		//保存新贴图。
		m_pDXTexture = pTexture;
	}
	//-----------------------------------------------------------------------------
} //namespace GGUI
//-----------------------------------------------------------------------------
