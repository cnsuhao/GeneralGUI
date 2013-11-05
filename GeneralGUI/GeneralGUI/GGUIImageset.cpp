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
		GGUIRect* pNewRect = new GGUIRect(fLeft, fRight, fTop, fBottom);
		m_arrayRect.AddElement(pNewRect);
		ImageRectID newRectID = m_arrayRect.GetWriteIndex() - 1;
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
		GGUIRect* pRect = m_arrayRect.GetElement(theRectID);
		if (pRect)
		{
			SAFE_DELETE(pRect);
			m_arrayRect.RemoveElement(theRectID);
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
	:m_arrayRect(NULL, 10)
	,m_MyImagesetID(Invalid_ImagesetID)
	,m_MyDXTextureID(Invalid_DXTextureID)
	,m_MyImagesetName()
	,m_nDXTextureWidth(0)
	,m_nDXTextureHeight(0)
	{

	}
	//-----------------------------------------------------------------------------
	GGUIImageset::~GGUIImageset()
	{
		//尝试删除贴图。
		GGUIDXTextureManager::GetInstance()->ReleaseDXTexture(m_MyDXTextureID);
		//先清零m_mapRectName2RectID，再清除m_arrayRect，
		//把m_mapRectName2RectID清零后，在RemoveImageRect()中遍历一个空map会快很多。
		m_mapRectName2RectID.clear();
		//
		SoInt nValidCount = m_arrayRect.GetWriteIndex();
		for (SoInt i=0; i<nValidCount; ++i)
		{
			RemoveImageRect(i);
		}
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
