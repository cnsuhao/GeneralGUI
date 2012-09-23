//-----------------------------------------------------------------------------
// GGUI控件所使用的贴图
// (C) oil
// 2012-09-02
//-----------------------------------------------------------------------------
#include "GGUIStdAfx.h"
#include "GGUITexture.h"
#include "GGUITextureContainer.h"
#include "GGUISystem.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	SoUInt32 GGUITexture::ms_TextureFVF = (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1);
	IDirect3DIndexBuffer9* GGUITexture::ms_pTextureIB = NULL;
	//-----------------------------------------------------------------------------
	GGUITexture::GGUITexture()
	:m_pTexture(NULL)
	,m_pVertex(NULL)
	,m_nTextureID(Invalid_TextureID)
	{
		if (!GGUITextureContainer::GetInstance()->IsOperationByTextureContainer())
		{
			::MessageBox(NULL, TEXT("一定要使用GGUITextureContainer来创建GGUITexture！"), TEXT("GGUI Error"), MB_OK);
		}
		//
		CreateVertexBuffer();
	}
	//-----------------------------------------------------------------------------
	GGUITexture::~GGUITexture()
	{
		ReleaseVertexBuffer();
		//
		if (!GGUITextureContainer::GetInstance()->IsOperationByTextureContainer())
		{
			::MessageBox(NULL, TEXT("一定要使用GGUITextureContainer来释放GGUITexture！"), TEXT("GGUI Error"), MB_OK);
		}
	}
	//-----------------------------------------------------------------------------
	bool GGUITexture::LoadTexture(const tchar* pFileName)
	{
		if (!pFileName)
		{
			return false;
		}
		//尝试删除旧贴图。
		SAFE_D3D_RELEASE(m_pTexture);
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
		HRESULT hr = D3DXCreateTextureFromFileEx(GGUISystem::GetInstance()->GetD3DDevice(), pFileName,
			uiWidth, uiHeight, uiMipLevels, uiUsage, eFormat, ePool, uiFilter, uiMipFilter, dwColorKey,
			NULL, NULL, &m_pTexture);
		if (FAILED(hr))
		{
			//Wait for add log
			return false;
		}
		else
		{
			return true;
		}
	}
	//-----------------------------------------------------------------------------
	void GGUITexture::SetTexture(IDirect3DTexture9* pNewTexture)
	{
		SAFE_D3D_RELEASE(m_pTexture);
		m_pTexture = pNewTexture;
	}
	//-----------------------------------------------------------------------------
	void GGUITexture::UpdateVertexBuffer(SoFloat fX, SoFloat fY, SoFloat fZ, SoFloat fWidth, SoFloat fHeight, SoUInt32 uiColor)
	{
		float fLeft = fX;
		float fRight = fX + fWidth;
		float fTop = fY;
		float fBottom = fY + fHeight;
		float fDepth = fZ;
		//
		SVertexType vertices[4] =
		{
			{ fLeft, fTop, fDepth, 1.0f, uiColor, 0.0f, 0.0f },
			{ fRight, fTop, fDepth, 1.0f, uiColor, 1.0f, 0.0f },
			{ fRight, fBottom, fDepth, 1.0f, uiColor, 1.0f, 1.0f },
			{ fLeft, fBottom, fDepth, 1.0f, uiColor, 0.0f, 1.0f },
		};
		SoUInt uiSize = 4 * (SoUInt)(sizeof(SVertexType));
		//
		void* pVertices = 0;
		const DWORD dwLockFlags = D3DLOCK_DISCARD;
		HRESULT hr = m_pVertex->Lock(0, 0, (void**)&pVertices, dwLockFlags);
		if (FAILED(hr))
		{
			return;
		}
		//
		memcpy_s(pVertices, uiSize, vertices, uiSize);
		m_pVertex->Unlock();
	}
	//-----------------------------------------------------------------------------
	void GGUITexture::RenderTexture()
	{
		if (m_pTexture == NULL || m_pVertex == NULL)
		{
			return;
		}
		IDirect3DDevice9* pD3DDevice = GGUISystem::GetInstance()->GetD3DDevice();

		//打开融合运算
		pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		//设置融合运算的类型
		pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		//设置Alpha数值的来源
		//使用顶点颜色的Alpha值
		//pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		//pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

		pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
		pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

		pD3DDevice->SetTexture(0, m_pTexture);
		pD3DDevice->SetStreamSource(0, m_pVertex, 0, sizeof(SVertexType));
		pD3DDevice->SetFVF(ms_TextureFVF);
		pD3DDevice->SetIndices(ms_pTextureIB);
		pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
	}
	//-----------------------------------------------------------------------------
	bool GGUITexture::CreateIndexBuffer()
	{
		if (ms_pTextureIB)
		{
			//索引缓冲区已经创建过了，直接返回。
			return true;
		}
		//索引缓冲区
		SoIndexBufferUnit index[2] = { {0,1,2}, {0,2,3} };
		SoUInt SizeOfIndex = (SoUInt)sizeof(index);

		HRESULT hr = GGUISystem::GetInstance()->GetD3DDevice()->CreateIndexBuffer(
			SizeOfIndex, 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &ms_pTextureIB, NULL);
		if (FAILED(hr))
		{
			//Wait for add log
			ReleaseIndexBuffer();
			return false;
		}

		void* pIndex = NULL;
		hr = ms_pTextureIB->Lock(0, SizeOfIndex, (void**)&pIndex, 0);
		if (FAILED(hr))
		{
			//Wait for add log
			ReleaseIndexBuffer();
			return false;
		}

		memcpy(pIndex, index, SizeOfIndex);
		ms_pTextureIB->Unlock();
		return true;
	}
	//-----------------------------------------------------------------------------
	void GGUITexture::ReleaseIndexBuffer()
	{
		SAFE_D3D_RELEASE(ms_pTextureIB);
	}
	//-----------------------------------------------------------------------------
	void GGUITexture::SetTextureID(TextureID newTextureID)
	{
		if (GGUITextureContainer::GetInstance()->IsOperationByTextureContainer())
		{
			m_nTextureID = newTextureID;
		}
		else
		{
			::MessageBox(NULL, TEXT("一定要使用GGUITextureContainer来赋值TextureID！"), TEXT("GGUI Error"), MB_OK);
		}
	}
	//-----------------------------------------------------------------------------
	bool GGUITexture::CreateVertexBuffer()
	{
		SoUInt uiSize = 4 * (SoUInt)(sizeof(SVertexType));
		//顶点缓存区的数据会被频繁修改，所以使用D3DUSAGE_DYNAMIC。
		SoUInt uiUsage = D3DUSAGE_DYNAMIC;
		//顶点缓存区的数据会被频繁修改，所以使用D3DPOOL_DEFAULT。
		D3DPOOL ePool = D3DPOOL_DEFAULT;
		HRESULT hr = GGUISystem::GetInstance()->GetD3DDevice()->CreateVertexBuffer(
			uiSize, uiUsage, ms_TextureFVF, ePool, &m_pVertex, NULL);
		if (FAILED(hr))
		{
			//Wait for add log
			return false;
		}
		else
		{
			return true;
		}
	}
	//-----------------------------------------------------------------------------
	void GGUITexture::ReleaseVertexBuffer()
	{
		SAFE_D3D_RELEASE(m_pVertex);
	}
} //namespace GGUI
//-----------------------------------------------------------------------------
