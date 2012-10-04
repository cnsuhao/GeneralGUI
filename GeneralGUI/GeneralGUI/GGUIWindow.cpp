//-----------------------------------------------------------------------------
// GGUI窗口基类
// (C) oil
// 2012-09-16
//-----------------------------------------------------------------------------
#include "GGUIStdAfx.h"
#include "GGUIWindow.h"
#include "GGUIWindowManager.h"
#include "GGUITexture.h"
#include "GGUITextureContainer.h"
//<<<<<<<<<<<
#include "GGUIFontManager.h"
#include "GGUIFreeTypeFont.h"
//>>>>>>>>>>>
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
	,m_eMyWindowType(WindowType_Base)
	,m_nMyWindowID(Invalid_WindowID)
	,m_nMyTextureID(Invalid_TextureID)
	,m_nMyDelegateID(Invalid_DelegateID)
	,m_bShouldUpdateUITexture(false)
	,m_bVisible(true)
	,m_bEnable(true)
	,m_bMouseInWindowArea(false)
	{
		if (!GGUIWindowManager::GetInstance()->IsOperationByWindowContainer())
		{
			::MessageBox(NULL, TEXT("一定要使用GGUIWindowContainer来创建GGUIWindow！"), TEXT("GGUI Error"), MB_OK);
		}
	}
	//-----------------------------------------------------------------------------
	GGUIWindow::~GGUIWindow()
	{
		ReleaseUITexture();
		if (!GGUIWindowManager::GetInstance()->IsOperationByWindowContainer())
		{
			::MessageBox(NULL, TEXT("一定要使用GGUIWindowContainer来释放GGUIWindow！"), TEXT("GGUI Error"), MB_OK);
		}
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::UpdateWindow(SoFloat fFrameTime)
	{

	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::RenderWindow()
	{
		if (!m_bVisible)
		{
			return;
		}

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
		m_bShouldUpdateUITexture = true;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetPositionY(SoFloat fPosY)
	{
		m_fPositionY = fPosY;
		m_bShouldUpdateUITexture = true;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetPositionZ(SoFloat fPosZ)
	{
		m_fPositionZ = fPosZ;
		m_bShouldUpdateUITexture = true;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetWidth(SoFloat fWidth)
	{
		m_fWidth = fWidth;
		m_bShouldUpdateUITexture = true;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetHeight(SoFloat fHeight)
	{
		m_fHeight = fHeight;
		m_bShouldUpdateUITexture = true;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetColor(SoFloat fR, SoFloat fG, SoFloat fB)
	{
		m_fColorR = fR;
		m_fColorG = fG;
		m_fColorB = fB;
		m_bShouldUpdateUITexture = true;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetAlpha(SoFloat fAlpha)
	{
		m_fColorA = fAlpha;
		m_bShouldUpdateUITexture = true;
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
	void GGUIWindow::SetVisible(bool bVisible)
	{
		m_bVisible = bVisible;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetEnable(bool bEnable)
	{
		m_bEnable = bEnable;
	}
	//-----------------------------------------------------------------------------
	SoFloat GGUIWindow::GetPositionX() const
	{
		return m_fPositionX;
	}
	//-----------------------------------------------------------------------------
	SoFloat GGUIWindow::GetPositionY() const
	{
		return m_fPositionY;
	}
	//-----------------------------------------------------------------------------
	SoFloat GGUIWindow::GetPositionZ() const
	{
		return m_fPositionZ;
	}
	//-----------------------------------------------------------------------------
	SoFloat GGUIWindow::GetWidth() const
	{
		return m_fWidth;
	}
	//-----------------------------------------------------------------------------
	SoFloat GGUIWindow::GetHeight() const
	{
		return m_fHeight;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::GetColor(SoFloat& fR, SoFloat& fG, SoFloat& fB) const
	{
		fR = m_fColorR;
		fG = m_fColorG;
		fB = m_fColorB;
	}
	//-----------------------------------------------------------------------------
	SoFloat GGUIWindow::GetAlpha() const
	{
		return m_fColorA;
	}
	//-----------------------------------------------------------------------------
	WindowID GGUIWindow::GetWindowID() const
	{
		return m_nMyWindowID;
	}
	//-----------------------------------------------------------------------------
	TextureID GGUIWindow::GetTextureID() const
	{
		return m_nMyTextureID;
	}
	//-----------------------------------------------------------------------------
	DelegateID GGUIWindow::GetDelegateID() const
	{
		return m_nMyDelegateID;
	}
	//-----------------------------------------------------------------------------
	bool GGUIWindow::GetVisible() const
	{
		return m_bVisible;
	}
	//-----------------------------------------------------------------------------
	bool GGUIWindow::GetEnable() const
	{
		return m_bEnable;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::OnMouseEnterWindowArea()
	{
		m_bMouseInWindowArea = true;
		GGUIWindowManager::GetInstance()->RaiseWindowEvent(m_nMyWindowID, m_nMyDelegateID, WindowEvent_MouseEnterWindowArea, 0);
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::OnMouseLeaveWindowArea()
	{
		m_bMouseInWindowArea = false;
		GGUIWindowManager::GetInstance()->RaiseWindowEvent(m_nMyWindowID, m_nMyDelegateID, WindowEvent_MouseLeaveWindowArea, 0);
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::OnMouseLeftButtonClickDown()
	{
		//<<<<<<<<<<<
		GGUIFreeTypeFont* pFont = GGUIFontManager::GetInstance()->GetFont(0);
		if (pFont)
		{
			GGUITexture* pUITexture = GGUITextureContainer::GetInstance()->GetUITexture(m_nMyTextureID);
			if (pUITexture)
			{
				pFont->SetDrawParam(pUITexture->GetDXTexture(), 1.0f, 0.0f, 0.0f, true, 0.0f, 0.0f, 0.0f);
				pFont->DrawString(TEXT("oil真棒！"), 6, 0, 0, 0, 0);
			}
		}
		//>>>>>>>>>>>

		GGUIWindowManager::GetInstance()->RaiseWindowEvent(m_nMyWindowID, m_nMyDelegateID, WindowEvent_MouseLeftButtonClickDown, 0);
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::OnMouseLeftButtonClickUp()
	{
		GGUIWindowManager::GetInstance()->RaiseWindowEvent(m_nMyWindowID, m_nMyDelegateID, WindowEvent_MouseLeftButtonClickUp, 0);
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetWindowID(WindowID theID)
	{
		if (GGUIWindowManager::GetInstance()->IsOperationByWindowContainer())
		{
			m_nMyWindowID = theID;
		}
		else
		{
			::MessageBox(NULL, TEXT("一定要使用GGUIWindowContainer来赋值WindowID！"), TEXT("GGUI Error"), MB_OK);
		}
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetDelegateID(DelegateID theID)
	{
		if (GGUIWindowManager::GetInstance()->IsOperationByWindowContainer())
		{
			m_nMyDelegateID = theID;
		}
		else
		{
			::MessageBox(NULL, TEXT("一定要使用GGUIWindowContainer来赋值DelegateID！"), TEXT("GGUI Error"), MB_OK);
		}
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::PostUpdateWindow()
	{
		if (m_bShouldUpdateUITexture)
		{
			m_bShouldUpdateUITexture = false;
			UpdateUITexture();
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
