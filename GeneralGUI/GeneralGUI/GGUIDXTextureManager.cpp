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
	GGUIDXTextureManager* GGUIDXTextureManager::ms_pInstance = NULL;
	//-----------------------------------------------------------------------------
	GGUIDXTextureManager::GGUIDXTextureManager()
	:m_arrayDXTexture(NULL, 20)
	{
		ms_pInstance = this;
	}
	//-----------------------------------------------------------------------------
	GGUIDXTextureManager::~GGUIDXTextureManager()
	{
		SoInt nValidCount = m_arrayDXTexture.GetWriteIndex();
		for (SoInt i=0; i<nValidCount; ++i)
		{
			ReleaseDXTexture(i);
		}
		//
		ms_pInstance = NULL;
	}
	//-----------------------------------------------------------------------------
	bool GGUIDXTextureManager::InitDXTextureManager()
	{
		return true;
	}
	//-----------------------------------------------------------------------------
	DXTextureID GGUIDXTextureManager::LoadTextureFromDisk(const tchar* pszFileName)
	{
		DXTextureID theDXTextureID = Invalid_DXTextureID;
		if (!pszFileName)
		{
			LOG_ERROR(TEXT("GGUIDXTextureManager::LoadTextureFromDisk : invalid filename"));
			return theDXTextureID;
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
		//图片过滤方式。
		SoUInt uiFilter = D3DX_FILTER_LINEAR; //;D3DX_FILTER_NONE
		SoUInt uiMipFilter = D3DX_FILTER_NONE;
		//不使用关键色替换。
		D3DCOLOR dwColorKey = 0;
		HRESULT hr = D3DXCreateTextureFromFileEx(GGUISystem::GetInstance()->GetD3DDevice(), pszFileName,
			uiWidth, uiHeight, uiMipLevels, uiUsage, eFormat, ePool, uiFilter, uiMipFilter, dwColorKey,
			NULL, NULL, &pNewDXTexture);
		if (FAILED(hr))
		{
			LOG_ERROR(TEXT("GGUIDXTextureManager::LoadTextureFromDisk : D3DXCreateTextureFromFileEx Fail [%s]"), pszFileName);
			return theDXTextureID;
		}
		//
		m_arrayDXTexture.AddElement(pNewDXTexture);
		theDXTextureID = m_arrayDXTexture.GetWriteIndex() - 1;
		LOG_DEBUG(TEXT("GGUIDXTextureManager::LoadTextureFromDisk : success FileName[%s] DXTextureID[%d]"), pszFileName, theDXTextureID);
		return theDXTextureID;
	}
	//-----------------------------------------------------------------------------
	DXTextureID GGUIDXTextureManager::CreateFontTexture(SoUInt uiWidth, SoUInt uiHeight)
	{
		DXTextureID theDXTextureID = Invalid_DXTextureID;
		IDirect3DTexture9* pNewDXTexture = NULL;
		//产生几层Mipmap纹理层级，值为0表示产生完整的纹理层级链表。
		SoUInt uiLevels = 1;
		//取默认值。
		SoUInt uiUsage = 0;
		//图片像素格式，创建灰度图，只需要存储像素点的Alpha值即可。
		D3DFORMAT eFormat = D3DFMT_A8;
		//使用托管内存池，因为贴图的数据不会被频繁改变（甚至不会改变），用托管内存池的好处是设备丢失后不必重新创建。
		D3DPOOL ePool = D3DPOOL_MANAGED;
		//
		HRESULT hr = GGUISystem::GetInstance()->GetD3DDevice()->CreateTexture(uiWidth, uiHeight, 
			uiLevels, uiUsage, eFormat, ePool, &pNewDXTexture, NULL);
		if (FAILED(hr))
		{
			LOG_ERROR(TEXT("GGUIDXTextureManager::CreateFontTexture : CreateTexture Fail"));
			return theDXTextureID;
		}
		//
		m_arrayDXTexture.AddElement(pNewDXTexture);
		theDXTextureID = m_arrayDXTexture.GetWriteIndex() - 1;
		LOG_DEBUG(TEXT("GGUIDXTextureManager::CreateFontTexture : success Width[%u] Height[%u]"), uiWidth, uiHeight);
		return theDXTextureID;
	}
	//-----------------------------------------------------------------------------
	void GGUIDXTextureManager::ReleaseDXTexture(DXTextureID theTextureID)
	{
		IDirect3DTexture9* pDXTexture = m_arrayDXTexture.GetElement(theTextureID);
		if (pDXTexture)
		{
			SAFE_D3D_RELEASE(pDXTexture);
			m_arrayDXTexture.RemoveElement(theTextureID);
			LOG_DEBUG(TEXT("GGUIDXTextureManager::ReleaseDXTexture : DXTextureID[%d]"), theTextureID);
		}
	}
	//-----------------------------------------------------------------------------
	bool GGUIDXTextureManager::DrawFontGlyph(DXTextureID theDXTextureID, const RECT& dest_rect, 
		unsigned char* pPixelBuffer, SoInt nWidth, SoInt nHeight, bool bEdge)
	{
		IDirect3DTexture9* pTexture = GetDXTexture(theDXTextureID);
		if (pTexture == NULL)
		{
			return false;
		}
		//Lock顶层贴图。
		SoUInt uiLevel = 0;
		D3DLOCKED_RECT locked_rect;
		if (pTexture->LockRect(uiLevel, &locked_rect, &dest_rect, D3DLOCK_DISCARD) != D3D_OK)
		{
			return false;
		}
		//
		SoInt nIndex = 0;
		for (SoInt y = 0; y < nHeight; ++y)
		{
			unsigned char* pDestBuffer = ((unsigned char*)locked_rect.pBits) + locked_rect.Pitch * y;
			for (SoInt x = 0; x < nWidth; ++x)
			{
				if (bEdge)
				{
					if (pDestBuffer[x] == 0 && pPixelBuffer[nIndex] > 0)
						pDestBuffer[x] = 0xFF; //pPixelBuffer[nIndex]; //测试，0x50;
				}
				else
				{
					pDestBuffer[x] = pPixelBuffer[nIndex];
				}
				++nIndex;
			}
		}
		pTexture->UnlockRect(uiLevel);
		return true;
	}
} //namespace GGUI
//-----------------------------------------------------------------------------
