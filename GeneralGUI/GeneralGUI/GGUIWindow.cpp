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
	,m_nMyImagesetID(Invalid_ImagesetID)
	,m_nMyImageRectID(Invalid_ImageRectID)
	,m_nMyDelegateID(Invalid_DelegateID)
	,m_bDirty(false)
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

	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetPositionX(SoFloat fPosX)
	{
		m_fPositionX = fPosX;
		m_bDirty = true;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetPositionY(SoFloat fPosY)
	{
		m_fPositionY = fPosY;
		m_bDirty = true;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetPositionZ(SoFloat fPosZ)
	{
		m_fPositionZ = fPosZ;
		m_bDirty = true;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetWidth(SoFloat fWidth)
	{
		m_fWidth = fWidth;
		m_bDirty = true;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetHeight(SoFloat fHeight)
	{
		m_fHeight = fHeight;
		m_bDirty = true;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetColor(SoFloat fR, SoFloat fG, SoFloat fB)
	{
		m_fColorR = fR;
		m_fColorG = fG;
		m_fColorB = fB;
		m_bDirty = true;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetAlpha(SoFloat fAlpha)
	{
		m_fColorA = fAlpha;
		m_bDirty = true;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetImagesetID(ImagesetID theID)
	{
		m_nMyImagesetID = theID;
		m_bDirty = true;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindow::SetImageRectID(ImageRectID theID)
	{
		m_nMyImageRectID = theID;
		m_bDirty = true;
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
	ImagesetID GGUIWindow::GetImagesetID() const
	{
		return m_nMyImagesetID;
	}
	//-----------------------------------------------------------------------------
	ImageRectID GGUIWindow::GetImageRectID() const
	{
		return m_nMyImageRectID;
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
		if (m_bDirty)
		{
			m_bDirty = false;
			//UpdateUITexture();
		}
	}
}
//-----------------------------------------------------------------------------
