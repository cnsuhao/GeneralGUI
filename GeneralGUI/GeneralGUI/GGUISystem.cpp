//-----------------------------------------------------------------------------
// GGUI系统类
// (C) oil
// 2012-09-08
//-----------------------------------------------------------------------------
#include "GGUIStdAfx.h"
#include "GGUISystem.h"
#include "GGUIWindowContainer.h"
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
		GGUIWindowContainer::CreateInstance();
		if (!GGUIWindowContainer::GetInstance()->InitWindowContainer())
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
		GGUIWindowContainer::ReleaseInstance();
		m_pD3DDevice = 0;
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

			}
			break;
		case ButtonUp:
			{

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
