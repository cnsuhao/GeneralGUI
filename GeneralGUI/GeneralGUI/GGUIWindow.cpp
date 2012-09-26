//-----------------------------------------------------------------------------
// GGUI窗口基类
// (C) oil
// 2012-09-16
//-----------------------------------------------------------------------------
#include "GGUIStdAfx.h"
#include "GGUIWindow.h"
#include "GGUIWindowContainer.h"
#include "GGUITexture.h"
#include "GGUITextureContainer.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	GGUIWindow::GGUIWindow()
	:m_fPositionX(0.0f)
	,m_fPositionY(0.0f)
	,m_fPositionZ(0.0f)
	,m_fWidth(0.0f)
	,m_fHeight(0.0f)
	,m_fColorR(0.0f)
	,m_fColorG(0.0f)
	,m_fColorB(0.0f)
	,m_fColorA(0.0f)
	,m_nMyWindowID(Invalid_WindowID)
	,m_nMyTextureID(Invalid_TextureID)
	,m_bShouldUpdateUITexture(SoFalse)
	{
		if (!GGUIWindowContainer::GetInstance()->IsOperationByWindowContainer())
		{
			::MessageBox(NULL, TEXT("一定要使用GGUIWindowContainer来创建GGUIWindow！"), TEXT("GGUI Error"), MB_OK);
		}
	}
	//-----------------------------------------------------------------------------
	GGUIWindow::~GGUIWindow()
	{
		ReleaseUITexture();
		if (!GGUIWindowContainer::GetInstance()->IsOperationByWindowContainer())
		{
			::MessageBox(NULL, TEXT("一定要使用GGUIWindowContainer来释放GGUIWindow！"), TEXT("GGUI Error"), MB_OK);
		}
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::UpdateWindow(SoFloat fFrameTime)
	{
		if (m_bShouldUpdateUITexture)
		{
			m_bShouldUpdateUITexture = SoFalse;
			UpdateUITexture();
		}
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::RenderWindow()
	{
		GGUITexture* pUITexture = GGUITextureContainer::GetInstance()->GetUITexture(m_nMyTextureID);
		if (pUITexture)
		{
			pUITexture->RenderTexture();
		}
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetPositionX(SoFloat fPosX)
	{
		m_fPositionX = fPosX;
		m_bShouldUpdateUITexture = SoTrue;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetPositionY(SoFloat fPosY)
	{
		m_fPositionY = fPosY;
		m_bShouldUpdateUITexture = SoTrue;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetPositionZ(SoFloat fPosZ)
	{
		m_fPositionZ = fPosZ;
		m_bShouldUpdateUITexture = SoTrue;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetWidth(SoFloat fWidth)
	{
		m_fWidth = fWidth;
		m_bShouldUpdateUITexture = SoTrue;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetHeight(SoFloat fHeight)
	{
		m_fHeight = fHeight;
		m_bShouldUpdateUITexture = SoTrue;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetColor(SoFloat fR, SoFloat fG, SoFloat fB)
	{
		m_fColorR = fR;
		m_fColorG = fG;
		m_fColorB = fB;
		m_bShouldUpdateUITexture = SoTrue;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetAlpha(SoFloat fAlpha)
	{
		m_fColorA = fAlpha;
		m_bShouldUpdateUITexture = SoTrue;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetImage(IDirect3DTexture9* pTexture)
	{
		if (m_nMyTextureID == Invalid_TextureID)
		{
			CreateUITexture();
		}
		GGUITexture* pUITexture = GGUITextureContainer::GetInstance()->GetUITexture(m_nMyTextureID);
		if (pUITexture)
		{
			pUITexture->SetTexture(pTexture);
		}
	}
	//-----------------------------------------------------------------------------
	bool GGUIWindow::SetImageByFileName(const tchar* pFileName)
	{
		bool bResult = false;
		if (m_nMyTextureID == Invalid_TextureID)
		{
			CreateUITexture();
		}
		GGUITexture* pUITexture = GGUITextureContainer::GetInstance()->GetUITexture(m_nMyTextureID);
		if (pUITexture)
		{
			bResult = pUITexture->LoadTexture(pFileName);
		}
		return bResult;
	}
	//-----------------------------------------------------------------------------
	SoFloat GGUIWindow::GetPositionX()
	{
		return m_fPositionX;
	}
	//-----------------------------------------------------------------------------
	SoFloat GGUIWindow::GetPositionY()
	{
		return m_fPositionY;
	}
	//-----------------------------------------------------------------------------
	SoFloat GGUIWindow::GetPositionZ()
	{
		return m_fPositionZ;
	}
	//-----------------------------------------------------------------------------
	SoFloat GGUIWindow::GetWidth()
	{
		return m_fWidth;
	}
	//-----------------------------------------------------------------------------
	SoFloat GGUIWindow::GetHeight()
	{
		return m_fHeight;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::GetColor(SoFloat& fR, SoFloat& fG, SoFloat& fB)
	{
		fR = m_fColorR;
		fG = m_fColorG;
		fB = m_fColorB;
	}
	//-----------------------------------------------------------------------------
	SoFloat GGUIWindow::GetAlpha()
	{
		return m_fColorA;
	}
	//-----------------------------------------------------------------------------
	WindowID GGUIWindow::GetWindowID()
	{
		return m_nMyWindowID;
	}
	//-----------------------------------------------------------------------------
	TextureID GGUIWindow::GetTextureID()
	{
		return m_nMyTextureID;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetWindowID(WindowID theID)
	{
		if (GGUIWindowContainer::GetInstance()->IsOperationByWindowContainer())
		{
			m_nMyWindowID = theID;
		}
		else
		{
			::MessageBox(NULL, TEXT("一定要使用GGUIWindowContainer来赋值WindowID！"), TEXT("GGUI Error"), MB_OK);
		}
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::CreateUITexture()
	{
		GGUITexture* pUITexture = GGUITextureContainer::GetInstance()->CreateUITexture();
		if (pUITexture)
		{
			m_nMyTextureID = pUITexture->GetTextureID();
		}
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::ReleaseUITexture()
	{
		if (m_nMyTextureID != Invalid_TextureID)
		{
			GGUITextureContainer::GetInstance()->ReleaseUITexture(m_nMyTextureID);
			m_nMyTextureID = Invalid_TextureID;
		}
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::UpdateUITexture()
	{
		GGUITexture* pUITexture = GGUITextureContainer::GetInstance()->GetUITexture(m_nMyTextureID);
		if (pUITexture)
		{
			SoUInt32 uiColor = SoMakeColorRGBA(m_fColorR, m_fColorG, m_fColorB, m_fColorA);
			pUITexture->UpdateVertexBuffer(m_fPositionX, m_fPositionY, m_fPositionZ, m_fWidth, m_fHeight, uiColor);
		}
	}
}
//-----------------------------------------------------------------------------
