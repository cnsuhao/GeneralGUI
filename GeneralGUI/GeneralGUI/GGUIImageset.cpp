//-----------------------------------------------------------------------------
// (C) oil
// 2012-10-19
//-----------------------------------------------------------------------------
#include "GGUIStdAfx.h"
#include "GGUIImageset.h"
#include "GGUIDXTextureManager.h"
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
	const GGUITinyString* GGUIImageset::GetImageRectNameByID(ImageRectID theRectID) const
	{
		GGUITinyString* pResult = NULL;
		for (mapRectName2RectID::const_iterator it = m_mapRectName2RectID.begin();
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
	bool GGUIImageset::GetImageRectPixel(ImageRectID theRectID, GGUIRect& theRect) const
	{
		const GGUIRect* pRect = GetImageRect(theRectID);
		if (pRect)
		{
			theRect.m_fLeft = pRect->m_fLeft * m_nDXTextureWidth;
			theRect.m_fRight = pRect->m_fRight * m_nDXTextureWidth;
			theRect.m_fTop = pRect->m_fTop * m_nDXTextureHeight;
			theRect.m_fBottom = pRect->m_fBottom * m_nDXTextureHeight;
			if (theRect.m_fLeft < 0.0f)
			{
				theRect.m_fLeft = 0.0f;
			}
			if (theRect.m_fRight > (SoFloat)m_nDXTextureWidth)
			{
				theRect.m_fRight = (SoFloat)m_nDXTextureWidth;
			}
			if (theRect.m_fTop < 0.0f)
			{
				theRect.m_fTop = 0.0f;
			}
			if (theRect.m_fBottom > (SoFloat)m_nDXTextureHeight)
			{
				theRect.m_fBottom = (SoFloat)m_nDXTextureHeight;
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	//-----------------------------------------------------------------------------
	GGUIImageset::GGUIImageset()
	:m_pImageRectID2Rect(NULL)
	,m_nCapacity(0)
	,m_nIndexEnd(0)
	,m_MyImagesetID(Invalid_ImagesetID)
	,m_MyDXTextureID(Invalid_DXTextureID)
	,m_MyImagesetName()
	,m_nDXTextureWidth(0)
	,m_nDXTextureHeight(0)
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
		GGUIDXTextureManager::GetInstance()->ReleaseDXTexture(m_MyDXTextureID);
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
	void GGUIImageset::SetDXTextureID(DXTextureID theTextureID)
	{
		m_MyDXTextureID = theTextureID;
		if (theTextureID != Invalid_DXTextureID)
		{
			IDirect3DTexture9* pDXTexture = GGUIDXTextureManager::GetInstance()->GetDXTexture(theTextureID);
			if (pDXTexture)
			{
				D3DSURFACE_DESC stDesc;
				if (pDXTexture->GetLevelDesc(0, &stDesc) == D3D_OK)
				{
					m_nDXTextureWidth = (SoInt)stDesc.Width;
					m_nDXTextureHeight = (SoInt)stDesc.Height;
				}
			}
		}
	}
	//-----------------------------------------------------------------------------
} //namespace GGUI
//-----------------------------------------------------------------------------
