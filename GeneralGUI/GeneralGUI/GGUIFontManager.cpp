//-----------------------------------------------------------------------------
// GGUI的字体管理器
// (C) oil
// 2012-10-04
//-----------------------------------------------------------------------------
#include "GGUIStdAfx.h"
#include "GGUIFontManager.h"
#include "GGUIFreeTypeFont.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	//-----------------------------------------------------------------------------
	GGUIFontManager::GGUIFontManager()
	{
		for (SoInt i=0; i<GGUIMaxFontCount; ++i)
		{
			m_pFontList[i] = 0;
		}
	}
	//-----------------------------------------------------------------------------
	GGUIFontManager::~GGUIFontManager()
	{
		for (SoInt i=0; i<GGUIMaxFontCount; ++i)
		{
			if (m_pFontList[i])
			{
				delete m_pFontList[i];
				m_pFontList[i] = 0;
			}
		}
	}
	//-----------------------------------------------------------------------------
	bool GGUIFontManager::AddFont(SoInt nID, const char* pFontFileName, SoInt nFontFaceIndex, SoInt nFontSizeWidth, SoInt16 nEdge)
	{
		if (nID < 0 || nID >= GGUIMaxFontCount)
		{
			return false;
		}
		if (!pFontFileName)
		{
			return false;
		}
		if (m_pFontList[nID])
		{
			//该元素已经被赋值了。
			return false;
		}
		m_pFontList[nID] = new GGUIFreeTypeFont;
		if (!m_pFontList[nID]->InitFont(GGUITinyString(TEXT("oil")), pFontFileName, nFontFaceIndex, nFontSizeWidth, nEdge))
		{
			delete m_pFontList[nID];
			m_pFontList[nID] = 0;
			return false;
		}
		return true;
	}
	//-----------------------------------------------------------------------------
	void GGUIFontManager::RemoveFont(SoInt nID)
	{
		if (nID < 0 || nID >= GGUIMaxFontCount)
		{
			return;
		}
		if (m_pFontList[nID])
		{
			delete m_pFontList[nID];
			m_pFontList[nID] = 0;
		}
	}
}
//-----------------------------------------------------------------------------
