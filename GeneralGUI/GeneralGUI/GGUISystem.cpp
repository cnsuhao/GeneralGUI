//-----------------------------------------------------------------------------
// GGUI系统类
// (C) oil
// 2012-09-08
//-----------------------------------------------------------------------------
#include "GGUIStdAfx.h"
#include "GGUISystem.h"
#include "GGUIWindowManager.h"
#include "GGUIInputProcess.h"
#include "GGUIScreenParam.h"
#include "GGUIFontManager.h"
#include "GGUIDXRenderManager.h"
#include "GGUIDXTextureManager.h"
#include "GGUIImagesetManager.h"
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
		GGUIInputProcess::CreateInstance();
		if (!GGUIInputProcess::GetInstance()->InitInputProcess())
		{
			return false;
		}
		//
		new GGUIDXRenderManager;
		if (!GGUIDXRenderManager::GetInstance()->InitDXRenderManager())
		{
			return false;
		}
		//
		new GGUIDXTextureManager;
		if (!GGUIDXTextureManager::GetInstance()->InitDXTextureManager())
		{
			return false;
		}
		//
		GGUIImagesetManager::CreateInstance();
		if (!GGUIImagesetManager::GetInstance()->InitImagesetManager())
		{
			return false;
		}
		//
		GGUIFontManager::CreateInstance();
		//
		return true;
	}
	//-----------------------------------------------------------------------------
	void GGUISystem::ReleaseUISystem()
	{
		GGUIFontManager::ReleaseInstance();
		GGUIImagesetManager::ReleaseInstance();
		delete GGUIDXTextureManager::GetInstance();
		delete GGUIDXRenderManager::GetInstance();
		GGUIInputProcess::ReleaseInstance();
		GGUIWindowManager::ReleaseInstance();
		m_pD3DDevice = NULL;
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
