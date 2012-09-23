//-----------------------------------------------------------------------------
// GGUI系统类
// (C) oil
// 2012-09-08
//-----------------------------------------------------------------------------
#include "GGUIStdAfx.h"
#include "GGUISystem.h"
#include "GGUIWindowContainer.h"
#include "GGUITextureContainer.h"
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
	bool GGUISystem::InitUISystem(IDirect3DDevice9* pDevice)
	{
		//首先为m_pD3DDevice赋值。
		m_pD3DDevice = pDevice;
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
		return true;
	}
	//-----------------------------------------------------------------------------
	void GGUISystem::ReleaseUISystem()
	{
		GGUITextureContainer::ReleaseInstance();
		GGUIWindowContainer::ReleaseInstance();
		m_pD3DDevice = 0;
	}
} //namespace GGUI
//-----------------------------------------------------------------------------
