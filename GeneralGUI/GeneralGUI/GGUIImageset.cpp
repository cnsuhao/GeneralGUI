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
	void GGUIImageset::SetImagesetName(const char* pszName)
	{
		m_MyImagesetName.SetValue(pszName);
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
		m_nCapacity = 30;
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
				delete m_pImageRectID2Rect[i];
				m_pImageRectID2Rect[i] = 0;
			}
		}
		delete [] m_pImageRectID2Rect;
		m_pImageRectID2Rect = 0;
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
