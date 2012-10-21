//-----------------------------------------------------------------------------
// (C) oil
// 2012-10-21
//-----------------------------------------------------------------------------
#include "GGUIStdAfx.h"
#include "GGUIDXRenderManager.h"
#include "GGUISystem.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	const SoUInt32 g_TextureFVF = (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1);
	//-----------------------------------------------------------------------------
	GGUIDXRenderManager::GGUIDXRenderManager()
	:m_pVertex(NULL)
	,m_arrayVertexBuffer(NULL)
	,m_nCapacity(0)
	,m_nIndexEnd(0)
	{

	}
	//-----------------------------------------------------------------------------
	GGUIDXRenderManager::~GGUIDXRenderManager()
	{

	}
	//-----------------------------------------------------------------------------
	bool GGUIDXRenderManager::InitDXRenderManager()
	{
		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		//创建DX顶点缓冲区。
		SoUInt uiSize = 4 * (SoUInt)(sizeof(SVertexType));
		//顶点缓存区的数据会被频繁修改，所以使用D3DUSAGE_DYNAMIC。
		SoUInt uiUsage = D3DUSAGE_DYNAMIC;
		//顶点缓存区的数据会被频繁修改，所以使用D3DPOOL_DEFAULT。
		D3DPOOL ePool = D3DPOOL_DEFAULT;
		HRESULT hr = GGUISystem::GetInstance()->GetD3DDevice()->CreateVertexBuffer(
			uiSize, uiUsage, g_TextureFVF, ePool, &m_pVertex, NULL);
		if (FAILED(hr))
		{
			//Wait for add log
			return false;
		}
		//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		//初始化SVertexType数组。
		m_nCapacity = 100;
		m_arrayVertexBuffer = new SVertexType*[m_nCapacity];
		memset(m_arrayVertexBuffer, 0, sizeof(SVertexType*)*m_nCapacity);
		return true;
	}
	//-----------------------------------------------------------------------------
	void GGUIDXRenderManager::ReleaseDXRenderManager()
	{
		//
		SAFE_D3D_RELEASE(m_pVertex);
		//
		for (SoInt i=0; i<m_nIndexEnd; ++i)
		{
			if (m_arrayVertexBuffer[i])
			{
				SAFE_DELETE(m_arrayVertexBuffer[i]);
			}
		}
		SAFE_DELETE_ARRAY(m_arrayVertexBuffer);
	}
	//-----------------------------------------------------------------------------
	void GGUIDXRenderManager::PreRender()
	{
		//保存原来的DX设备渲染状态。事后要还原为原来状态。
		IDirect3DDevice9* pD3DDevice = GGUISystem::GetInstance()->GetD3DDevice();
		pD3DDevice->GetRenderState(D3DRS_ALPHABLENDENABLE, &m_uiOldAlphaBlendEnable);
		pD3DDevice->GetRenderState(D3DRS_SRCBLEND, &m_uiOldSrcBlend);
		pD3DDevice->GetRenderState(D3DRS_DESTBLEND, &m_uiOldDestBlend);
		pD3DDevice->GetTextureStageState(0, D3DTSS_ALPHAARG1, &m_uiOldAlphaArg1);
		pD3DDevice->GetTextureStageState(0, D3DTSS_ALPHAARG2, &m_uiOldAlphaArg2);
		pD3DDevice->GetTextureStageState(0, D3DTSS_ALPHAOP, &m_uiOldAlphaOp);
	}
	//-----------------------------------------------------------------------------
	void GGUIDXRenderManager::AddRnederUnit()
	{

	}
	//-----------------------------------------------------------------------------
	void GGUIDXRenderManager::DoRender()
	{

	}
	//-----------------------------------------------------------------------------
	void GGUIDXRenderManager::PostRender()
	{

	}
} //namespace GGUI
//-----------------------------------------------------------------------------
