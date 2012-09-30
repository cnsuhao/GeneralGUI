//-----------------------------------------------------------------------------
// GGUI系统类
// (C) oil
// 2012-09-08
//-----------------------------------------------------------------------------
#include "GGUIStdAfx.h"
#include "GGUISystem.h"
#include "GGUIWindowManager.h"
#include "GGUITextureContainer.h"
#include "GGUIInputProcess.h"
#include "GGUIScreenParam.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	GGUISystem::GGUISystem()
	:m_pD3DDevice(0)
	{

	}
	//-----------------------------------------------------------------------------
	GGUISystem::~GGUISystem()
	{
		ReleaseUISystem();
	}
	//-----------------------------------------------------------------------------
	bool GGUISystem::InitUISystem(IDirect3DDevice9* pDevice, SoFloat fScreenWidth, SoFloat fScreenHeight)
	{
		//首先为m_pD3DDevice赋值。
		m_pD3DDevice = pDevice;
		GGUIScreenParam::ms_fScreenWidth = fScreenWidth;
		GGUIScreenParam::ms_fScreenHeight = fScreenHeight;
		//
		GGUIWindowManager::CreateInstance();
		if (!GGUIWindowManager::GetInstance()->InitWindowManager())
		{
			return false;
		}
		//
		GGUITextureContainer::CreateInstance();
		if (!GGUITextureContainer::GetInstance()->InitTextureContainer())
		{
			return false;
		}
		//
		GGUIInputProcess::CreateInstance();
		if (!GGUIInputProcess::GetInstance()->InitInputProcess())
		{
			return false;
		}
		//
		return true;
	}
	//-----------------------------------------------------------------------------
	void GGUISystem::ReleaseUISystem()
	{
		GGUIInputProcess::ReleaseInstance();
		GGUITextureContainer::ReleaseInstance();
		GGUIWindowManager::ReleaseInstance();
		m_pD3DDevice = 0;
	}
	//-----------------------------------------------------------------------------
	void GGUISystem::UpdateGGUI(SoFloat fFrameTime)
	{
		GGUIWindowManager::GetInstance()->UpdateWindowManager(fFrameTime);
	}
	//-----------------------------------------------------------------------------
	void GGUISystem::RenderGGUI()
	{
		GGUIWindowManager::GetInstance()->RenderWindowManager();
	}
	//-----------------------------------------------------------------------------
	bool GGUISystem::InjectKeyEvent(eInputEvent theEvent, eKeyButton theKey)
	{
		bool bResult = false;
		switch (theEvent)
		{
		case ButtonDown:
			{
				
			}
			break;
		case ButtonUp:
			{

			}
		default:
			break;
		}
		return bResult;
	}
	//-----------------------------------------------------------------------------
	bool GGUISystem::InjectMouseEvent(eInputEvent theEvent, eMouseButton theButton, SoFloat fParamA, SoFloat fParamB)
	{
		bool bResult = false;
		switch (theEvent)
		{
		case ButtonDown:
			{
				switch (theButton)
				{
				case LeftMouse:
					GGUIInputProcess::GetInstance()->OnMouseLeftButtonDown();
					break;
				default:
					break;
				}
			}
			break;
		case ButtonUp:
			{
				switch (theButton)
				{
				case LeftMouse:
					GGUIInputProcess::GetInstance()->OnMouseLeftButtonUp();
					break;
				default:
					break;
				}
			}
			break;
		case MouseMove:
			{
				bResult = GGUIInputProcess::GetInstance()->OnMouseMove(fParamA, fParamB);
			}
			break;
		default:
			break;
		}
		return bResult;
	}
} //namespace GGUI
//-----------------------------------------------------------------------------
