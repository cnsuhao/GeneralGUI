//-----------------------------------------------------------------------------
// GGUI处理用户的输入
// (C) oil
// 2012-09-26
//-----------------------------------------------------------------------------
#include "GGUIStdAfx.h"
#include "GGUIInputProcess.h"
#include "GGUIWindow.h"
#include "GGUIWindowContainer.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	//-----------------------------------------------------------------------------
	GGUIInputProcess::GGUIInputProcess()
	:m_eCurrentMouseOpState(MouseOp_None)
	,m_theWindowForMouseOpHover(Invalid_WindowID)
	{

	}
	//-----------------------------------------------------------------------------
	GGUIInputProcess::~GGUIInputProcess()
	{
		ReleaseInputProcess();
	}
	//-----------------------------------------------------------------------------
	bool GGUIInputProcess::InitInputProcess()
	{
		return true;
	}
	//-----------------------------------------------------------------------------
	void GGUIInputProcess::ReleaseInputProcess()
	{

	}
	//-----------------------------------------------------------------------------
	bool GGUIInputProcess::OnMouseMove(SoFloat fNewPosX, SoFloat fNewPosY)
	{
		bool bResult = false;
		//判断鼠标是否落在了用户窗口的外面。
		bool bOutOfScreen = IsMouseOutOfScreen(fNewPosX, fNewPosY);
		//判断鼠标落在了哪个窗口内部。
		WindowID theWindowWhoContainMouse = Invalid_WindowID;
		if (!bOutOfScreen)
		{
			//如果之前鼠标操作状态为MouseOp_Hover，则先判断鼠标是否仍然落在那个窗口内。
			if (m_eCurrentMouseOpState == MouseOp_Hover)
			{
				GGUIWindow* pPreWindow = GGUIWindowContainer::GetInstance()->GetUIWindow(m_theWindowForMouseOpHover);
				if (pPreWindow && pPreWindow->IsContainMouse(fNewPosX, fNewPosY))
				{
					theWindowWhoContainMouse = m_theWindowForMouseOpHover;
				}
			}
			//如果不确定鼠标落在哪个窗口内，则遍历所有的窗口。
			if (theWindowWhoContainMouse == Invalid_WindowID)
			{
				theWindowWhoContainMouse = GetWindowWhoContainMouse(fNewPosX, fNewPosY);
			}
		}

		switch (m_eCurrentMouseOpState)
		{
		case MouseOp_None:
			{
				if (theWindowWhoContainMouse != Invalid_WindowID)
				{
					MouseOpHoverBegin(theWindowWhoContainMouse);
				}
			}
			break;
		case MouseOp_Hover:
			{
				if (theWindowWhoContainMouse != m_theWindowForMouseOpHover)
				{
					MouseOpHoverEnd();
				}
				if (theWindowWhoContainMouse != Invalid_WindowID)
				{
					MouseOpHoverBegin(theWindowWhoContainMouse);
				}
			}
			break;
		default:
			break;
		}
		return bResult;
	}
	//-----------------------------------------------------------------------------
	void GGUIInputProcess::MouseOpHoverBegin(WindowID theWindowID)
	{
		m_eCurrentMouseOpState = MouseOp_Hover;
		m_theWindowForMouseOpHover = theWindowID;
	}
	//-----------------------------------------------------------------------------
	void GGUIInputProcess::MouseOpHoverEnd()
	{
		m_eCurrentMouseOpState = MouseOp_None;
		m_theWindowForMouseOpHover = Invalid_WindowID;
	}
	//-----------------------------------------------------------------------------
	WindowID GGUIInputProcess::GetWindowWhoContainMouse(SoFloat fMousePosX, SoFloat fMousePosY)
	{
		WindowID theResult = Invalid_WindowID;
		GGUIWindowContainer* pWindowContainer = GGUIWindowContainer::GetInstance();
		SoInt nIndex = 0;
		GGUIWindow* pWindow = NULL;
		while (pWindowContainer->Next(nIndex, pWindow))
		{
			if (pWindow->IsContainMouse(fMousePosX, fMousePosY))
			{
				theResult = pWindow->GetWindowID();
				break;
			}
		}
		return theResult;
	}
}
//-----------------------------------------------------------------------------
