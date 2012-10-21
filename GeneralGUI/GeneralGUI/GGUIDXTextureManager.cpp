//-----------------------------------------------------------------------------
// (C) oil
// 2012-10-21
//-----------------------------------------------------------------------------
#include "GGUIStdAfx.h"
#include "GGUIDXTextureManager.h"
#include "GGUISystem.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	//-----------------------------------------------------------------------------
	GGUIDXTextureManager::GGUIDXTextureManager()
	:m_arrayDXTexture(NULL)
	,m_nCapacity(0)
	,m_nIndexEnd(0)
	{

	}
	//-----------------------------------------------------------------------------
	GGUIDXTextureManager::~GGUIDXTextureManager()
	{
		ReleaseDXTextureManager();
	}
	//-----------------------------------------------------------------------------
	bool GGUIDXTextureManager::InitDXTextureManager()
	{
		//初始化m_arrayDXTexture数组。
		m_nCapacity = 20;
		m_arrayDXTexture = new IDirect3DTexture9*[m_nCapacity];
		memset(m_arrayDXTexture, 0, sizeof(IDirect3DTexture9*)*m_nCapacity);
		return true;
	}
	//-----------------------------------------------------------------------------
	void GGUIDXTextureManager::ReleaseDXTextureManager()
	{
		for (SoInt i=0; i<m_nIndexEnd; ++i)
		{
			if (m_arrayDXTexture[i])
			{
				SAFE_D3D_RELEASE(m_arrayDXTexture[i]);
			}
		}
		SAFE_DELETE_ARRAY(m_arrayDXTexture);
	}
	//-----------------------------------------------------------------------------
	bool GGUIDXTextureManager::LoadTextureFromDisk(const tchar* pszFileName, DXTextureID* pDXTextureID)
	{
		if (!pszFileName)
		{
			return false;
		}
		IDirect3DTexture9* pNewDXTexture = NULL;
		//宽高使用图片的宽高，并且不要调整到2的幂。
		SoUInt uiWidth = D3DX_DEFAULT_NONPOW2;
		SoUInt uiHeight = D3DX_DEFAULT_NONPOW2;
		//不应该使用MipMap。
		SoUInt uiMipLevels = 1;
		//用途，使用默认值。
		SoUInt uiUsage = 0;
		//像素格式。
		D3DFORMAT eFormat = D3DFMT_UNKNOWN;
		//使用托管内存池，因为贴图的数据不会被频繁改变（甚至不会改变），用托管内存池的好处是设备丢失后不必重新创建。
		D3DPOOL ePool = D3DPOOL_MANAGED;
		//图片过滤方式。不需要过滤，因为Texture并没有做缩放。
		SoUInt uiFilter = D3DX_FILTER_NONE; //D3DX_FILTER_LINEAR;
		SoUInt uiMipFilter = D3DX_FILTER_NONE;
		//不使用关键色替换。
		D3DCOLOR dwColorKey = 0;
		HRESULT hr = D3DXCreateTextureFromFileEx(GGUISystem::GetInstance()->GetD3DDevice(), pszFileName,
			uiWidth, uiHeight, uiMipLevels, uiUsage, eFormat, ePool, uiFilter, uiMipFilter, dwColorKey,
			NULL, NULL, &pNewDXTexture);
		if (FAILED(hr))
		{
			//Wait for add log
			return false;
		}
		//
		m_arrayDXTexture[m_nIndexEnd] = pNewDXTexture;
		++m_nIndexEnd;
		return true;
	}
	//-----------------------------------------------------------------------------
	void GGUIDXTextureManager::ReleaseDXTexture(DXTextureID theTextureID)
	{
		if (theTextureID >= 0 && theTextureID < m_nCapacity)
		{
			if (m_arrayDXTexture[theTextureID])
			{
				SAFE_D3D_RELEASE(m_arrayDXTexture[theTextureID]);
			}
		}
	}
} //namespace GGUI
//-----------------------------------------------------------------------------
