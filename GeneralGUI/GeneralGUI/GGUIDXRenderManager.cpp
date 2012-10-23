//-----------------------------------------------------------------------------
// (C) oil
// 2012-10-21
//
// 顶点排列顺序，012组成一个三角形，023组成一个三角形。
// 0---1
// | \ |
// 3---2
//-----------------------------------------------------------------------------
#include "GGUIStdAfx.h"
#include "GGUIDXRenderManager.h"
#include "GGUISystem.h"
#include "GGUIWindow.h"
#include "GGUIImagesetManager.h"
#include "GGUIImageset.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	const SoUInt32 g_DXVertexFVF = (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1);
	//-----------------------------------------------------------------------------
	GGUIDXRenderManager::GGUIDXRenderManager()
	:m_pDXVertexBuffer(NULL)
	,m_nDXVertexCapacity(0)
	,m_pDXIndexBuffer(NULL)
	,m_nDXIndexCapacity(0)
	,m_arrayVertexContent(NULL)
	,m_nVertexContentCapacity(0)
	,m_nVertexContentIndexEnd(0)
	,m_theTargetImagesetID(Invalid_ImagesetID)
	,m_pTargetImageset(NULL)
	{

	}
	//-----------------------------------------------------------------------------
	GGUIDXRenderManager::~GGUIDXRenderManager()
	{
		ReleaseDXRenderManager();
	}
	//-----------------------------------------------------------------------------
	bool GGUIDXRenderManager::InitDXRenderManager()
	{
		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		//创建DX顶点缓冲区。
		m_nDXVertexCapacity = 100;
		SoUInt uiSize = m_nDXVertexCapacity * (SoUInt)(sizeof(stVertexContent));
		//顶点缓存区的数据会被频繁修改，所以使用D3DUSAGE_DYNAMIC。
		SoUInt uiUsage = D3DUSAGE_DYNAMIC;
		//顶点缓存区的数据会被频繁修改，所以使用D3DPOOL_DEFAULT。
		D3DPOOL ePool = D3DPOOL_DEFAULT;
		HRESULT hr = GGUISystem::GetInstance()->GetD3DDevice()->CreateVertexBuffer(
			uiSize, uiUsage, g_DXVertexFVF, ePool, &m_pDXVertexBuffer, NULL);
		if (FAILED(hr))
		{
			//Wait for add log
			return false;
		}
		//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		//创建DX索引缓冲区。
		m_nDXIndexCapacity = m_nDXVertexCapacity / 2;
		SoUInt SizeOfIndex = m_nDXIndexCapacity * (SoUInt)(sizeof(SoIndexBufferUnit));
		//索引缓冲区的数据不会被修改。
		SoUInt uiIndexBufferUsage = 0;
		//索引缓冲区的数据不会被修改。
		D3DPOOL eIndexBufferPool = D3DPOOL_MANAGED;
		HRESULT hrOfIndex = GGUISystem::GetInstance()->GetD3DDevice()->CreateIndexBuffer(
			SizeOfIndex, uiIndexBufferUsage, D3DFMT_INDEX16, eIndexBufferPool, &m_pDXIndexBuffer, NULL);
		if (FAILED(hrOfIndex))
		{
			//Wait for add log
			return false;
		}
		//
		SoIndexBufferUnit* pIndexData = NULL;
		hrOfIndex = m_pDXIndexBuffer->Lock(0, SizeOfIndex, (void**)&pIndexData, 0);
		if (FAILED(hrOfIndex))
		{
			//Wait for add log
			return false;
		}
		SoInt nIndexForIndexBuffer = 0;
		while (nIndexForIndexBuffer < m_nDXIndexCapacity)
		{
			pIndexData->_0 = 0;
			pIndexData->_1 = 1;
			pIndexData->_2 = 2;
			++pIndexData;
			++nIndexForIndexBuffer;
			pIndexData->_0 = 0;
			pIndexData->_1 = 2;
			pIndexData->_2 = 3;
			++pIndexData;
			++nIndexForIndexBuffer;
		}
		m_pDXIndexBuffer->Unlock();
		//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		//初始化SVertexType数组。
		m_nVertexContentCapacity = 100;
		m_arrayVertexContent = new stVertexContent[m_nVertexContentCapacity];
		memset(m_arrayVertexContent, 0, sizeof(stVertexContent)*m_nVertexContentCapacity);
		return true;
	}
	//-----------------------------------------------------------------------------
	void GGUIDXRenderManager::ReleaseDXRenderManager()
	{
		//
		SAFE_D3D_RELEASE(m_pDXVertexBuffer);
		SAFE_D3D_RELEASE(m_pDXIndexBuffer);
		//
		SAFE_DELETE_ARRAY(m_arrayVertexContent);
	}
	//-----------------------------------------------------------------------------
	void GGUIDXRenderManager::PreRender()
	{
		m_nVertexContentIndexEnd = 0;
		m_theTargetImagesetID = Invalid_ImagesetID;
		m_pTargetImageset = NULL;
		//保存原来的DX设备渲染状态。事后要还原为原来状态。
		IDirect3DDevice9* pD3DDevice = GGUISystem::GetInstance()->GetD3DDevice();
		pD3DDevice->GetRenderState(D3DRS_ALPHABLENDENABLE, &m_dwOldAlphaBlendEnable);
		pD3DDevice->GetRenderState(D3DRS_SRCBLEND, &m_dwOldSrcBlend);
		pD3DDevice->GetRenderState(D3DRS_DESTBLEND, &m_dwOldDestBlend);
		pD3DDevice->GetTextureStageState(0, D3DTSS_ALPHAARG1, &m_dwOldAlphaArg1);
		pD3DDevice->GetTextureStageState(0, D3DTSS_ALPHAARG2, &m_dwOldAlphaArg2);
		pD3DDevice->GetTextureStageState(0, D3DTSS_ALPHAOP, &m_dwOldAlphaOp);
	}
	//-----------------------------------------------------------------------------
	void GGUIDXRenderManager::AddRnederUnit(const GGUIWindow* pUIWindow)
	{
		if (pUIWindow == NULL)
		{
			return;
		}
		//检查数组容量是否足够。
		if (m_nVertexContentIndexEnd+4 >= m_nVertexContentCapacity)
		{
			//容器空间不够了，则把容器空间扩大到原来的2倍。
			SoUInt sizeOfOldArray = (SoUInt)sizeof(stVertexContent) * m_nVertexContentCapacity;
			m_nVertexContentCapacity *= 2;
			stVertexContent* pNewArray = new stVertexContent[m_nVertexContentCapacity];
			SoUInt sizeOfNewArray = (SoUInt)sizeof(stVertexContent) * m_nVertexContentCapacity;
			memset(pNewArray, 0, sizeOfNewArray);
			memcpy_s(pNewArray, sizeOfNewArray, m_arrayVertexContent, sizeOfOldArray);
			SAFE_DELETE_ARRAY(m_arrayVertexContent);
			m_arrayVertexContent = pNewArray;
		}
		//
		SoFloat fLeft = pUIWindow->GetPositionX();
		SoFloat fRight = fLeft + pUIWindow->GetWidth();
		SoFloat fTop = pUIWindow->GetPositionY();
		SoFloat fBottom = fTop + pUIWindow->GetHeight();
		SoFloat fDepth = pUIWindow->GetPositionZ();
		SoFloat fColorR = 0.0f;
		SoFloat fColorG = 0.0f;
		SoFloat fColorB = 0.0f;
		pUIWindow->GetColor(fColorR, fColorG, fColorB);
		SoFloat fColorA = pUIWindow->GetAlpha();
		SoUInt32 uiColor = SoMakeColorRGBA(fColorR, fColorG, fColorB, fColorA);
		SoFloat fUVLeft = 0.0f;
		SoFloat fUVRight = 0.0f;
		SoFloat fUVTop = 0.0f;
		SoFloat fUVBottom = 0.0f;
		//
		ImagesetID destImagesetID = pUIWindow->GetImagesetID();
		if (m_theTargetImagesetID != destImagesetID)
		{
			m_theTargetImagesetID = destImagesetID;
			m_pTargetImageset = GGUIImagesetManager::GetInstance()->GetImageset(destImagesetID);
		}
		if (m_pTargetImageset)
		{
			const GGUIRect* pRect = m_pTargetImageset->GetImageRect(pUIWindow->GetImageRectID());
			if (pRect)
			{
				fUVLeft = pRect->m_fLeft;
				fUVRight = pRect->m_fRight;
				fUVTop = pRect->m_fTop;
				fUVBottom = pRect->m_fBottom;
			}
		}
		//
		m_arrayVertexContent[m_nVertexContentIndexEnd].fX = fLeft;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fY = fTop;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fZ = fDepth;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fRHW = 1.0f;
		m_arrayVertexContent[m_nVertexContentIndexEnd].uiColor = uiColor;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fCoordX = fUVLeft;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fCoordY = fUVTop;
		++m_nVertexContentIndexEnd;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fX = fRight;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fY = fTop;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fZ = fDepth;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fRHW = 1.0f;
		m_arrayVertexContent[m_nVertexContentIndexEnd].uiColor = uiColor;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fCoordX = fUVRight;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fCoordY = fUVTop;
		++m_nVertexContentIndexEnd;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fX = fRight;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fY = fBottom;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fZ = fDepth;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fRHW = 1.0f;
		m_arrayVertexContent[m_nVertexContentIndexEnd].uiColor = uiColor;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fCoordX = fUVRight;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fCoordY = fUVBottom;
		++m_nVertexContentIndexEnd;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fX = fLeft;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fY = fBottom;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fZ = fDepth;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fRHW = 1.0f;
		m_arrayVertexContent[m_nVertexContentIndexEnd].uiColor = uiColor;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fCoordX = fUVLeft;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fCoordY = fUVBottom;
		++m_nVertexContentIndexEnd;
	}
	//-----------------------------------------------------------------------------
	void GGUIDXRenderManager::DoRender()
	{

	}
	//-----------------------------------------------------------------------------
	void GGUIDXRenderManager::PostRender()
	{
		m_theTargetImagesetID = Invalid_ImagesetID;
		m_pTargetImageset = NULL;
		//还原为原来的渲染状态。
		IDirect3DDevice9* pD3DDevice = GGUISystem::GetInstance()->GetD3DDevice();
		pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, m_dwOldAlphaBlendEnable);
		pD3DDevice->SetRenderState(D3DRS_SRCBLEND, m_dwOldSrcBlend);
		pD3DDevice->SetRenderState(D3DRS_DESTBLEND, m_dwOldDestBlend);
		pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, m_dwOldAlphaArg1);
		pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, m_dwOldAlphaArg2);
		pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, m_dwOldAlphaOp);
	}
} //namespace GGUI
//-----------------------------------------------------------------------------
