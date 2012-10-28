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
#include "GGUIDXTextureManager.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	const SoUInt32 g_DXVertexFVF = (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1);
	//-----------------------------------------------------------------------------
	GGUIDXRenderManager::GGUIDXRenderManager()
	:m_pDXVertexBuffer(NULL)
	,m_pDXIndexBuffer(NULL)
	,m_pDXStateBlock(NULL)
	,m_arrayVertexContent(NULL)
	,m_nDXVertexCapacity(0)
	,m_nDXIndexCapacity(0)
	,m_nVertexContentCapacity(0)
	,m_nVertexContentIndexEnd(0)
	,m_theTargetImagesetID(Invalid_ImagesetID)
	,m_theTargetDXTextureID(Invalid_DXTextureID)
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
		SoInt nDefaultVertexCount = 100;
		//创建DX顶点缓冲区。
		CreateDXVertexBuffer(nDefaultVertexCount);
		//创建DX索引缓冲区。
		CreateDXIndexBuffer(nDefaultVertexCount / 2);
		//创建DX的StateBlock。
		HRESULT hr = GGUISystem::GetInstance()->GetD3DDevice()->CreateStateBlock(D3DSBT_ALL, &m_pDXStateBlock);
		if (FAILED(hr))
		{
			//Wait for add log
		}
		//初始化SVertexType数组。
		m_nVertexContentCapacity = nDefaultVertexCount;
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
		SAFE_D3D_RELEASE(m_pDXStateBlock);
		//
		SAFE_DELETE_ARRAY(m_arrayVertexContent);
	}
	//-----------------------------------------------------------------------------
	void GGUIDXRenderManager::PreRender()
	{
		m_nVertexContentIndexEnd = 0;
		m_theTargetImagesetID = Invalid_ImagesetID;
		m_theTargetDXTextureID = Invalid_DXTextureID;
		//保存原来的DX设备渲染状态。事后要还原为原来状态。
		if (m_pDXStateBlock)
		{
			m_pDXStateBlock->Capture();
		}
		//设置需要的渲染状态。
		IDirect3DDevice9* pD3DDevice = GGUISystem::GetInstance()->GetD3DDevice();
		//打开Alpha融合运算。
		pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		//设置Alpha数值的来源，来源于贴图Alpha值和顶点色的Alpha值。
		pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
		//打开Alpha值检测，接近透明的像素就不必绘制。
		pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000010);
		//关闭深度值检测。
		pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
		//关闭写深度值。
		pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
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
			//同步的扩充顶点缓冲区和索引缓冲区。
			CreateDXVertexBuffer(m_nVertexContentCapacity);
			CreateDXIndexBuffer(m_nVertexContentCapacity / 2);
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
		//s_pTargetImageset没有放到头文件中作为成员变量，是因为不想为了字节对齐而
		//考虑s_pTargetImageset在成员列表中的排序问题。
		//这样做有缺陷，如果在一系列的AddRnederUnit()调用过程中做了删除Imageset的操作，
		//s_pTargetImageset有可能变成野指针。
		static GGUIImageset* s_pTargetImageset = NULL;
		ImagesetID destImagesetID = pUIWindow->GetImagesetID();
		if (m_theTargetImagesetID != destImagesetID)
		{
			m_theTargetImagesetID = destImagesetID;
			s_pTargetImageset = GGUIImagesetManager::GetInstance()->GetImageset(destImagesetID);
			m_theTargetDXTextureID = s_pTargetImageset->GetDXTextureID();
		}
		if (s_pTargetImageset)
		{
			const GGUIRect* pRect = s_pTargetImageset->GetImageRect(pUIWindow->GetImageRectID());
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
		if (m_pDXVertexBuffer == NULL)
		{
			return;
		}
		if (m_pDXIndexBuffer == NULL)
		{
			return;
		}
		IDirect3DTexture9* pDXTexture = GGUIDXTextureManager::GetInstance()->GetDXTexture(m_theTargetDXTextureID);
		if (pDXTexture == NULL)
		{
			return;
		}
		//对顶点缓冲区执行lock操作。
		void* pVertices = 0;
		HRESULT hr = m_pDXVertexBuffer->Lock(0, 0, (void**)&pVertices, 0);
		if (FAILED(hr))
		{
			return;
		}
		//为顶点缓冲区赋值。
		SoUInt uiSize = m_nVertexContentIndexEnd * (SoUInt)(sizeof(stVertexContent));
		memcpy_s(pVertices, uiSize, m_arrayVertexContent, uiSize);
		m_pDXVertexBuffer->Unlock();
		//绘制。
		IDirect3DDevice9* pD3DDevice = GGUISystem::GetInstance()->GetD3DDevice();
		pD3DDevice->SetTexture(0, pDXTexture);
		pD3DDevice->SetStreamSource(0, m_pDXVertexBuffer, 0, (SoUInt)sizeof(stVertexContent));
		pD3DDevice->SetFVF(g_DXVertexFVF);
		pD3DDevice->SetIndices(m_pDXIndexBuffer);
		pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_nVertexContentIndexEnd, 0, m_nVertexContentIndexEnd/2);
	}
	//-----------------------------------------------------------------------------
	void GGUIDXRenderManager::PostRender()
	{
		m_theTargetImagesetID = Invalid_ImagesetID;
		m_theTargetDXTextureID = Invalid_DXTextureID;
		//还原为原来的渲染状态。
		if (m_pDXStateBlock)
		{
			m_pDXStateBlock->Apply();
		}
	}
	//-----------------------------------------------------------------------------
	bool GGUIDXRenderManager::CreateDXVertexBuffer(SoInt nCapacity)
	{
		//尝试删除已有的DX顶点缓冲区。
		SAFE_D3D_RELEASE(m_pDXVertexBuffer);
		//创建DX顶点缓冲区。
		m_nDXVertexCapacity = nCapacity;
		SoUInt uiSize = m_nDXVertexCapacity * (SoUInt)(sizeof(stVertexContent));
		//顶点缓冲区会频繁做写操作，所以适合D3DPOOL_DEFAULT和D3DUSAGE_WRITEONLY搭配使用。
		//需要主动处理设备丢失。
		SoUInt uiUsage = D3DUSAGE_WRITEONLY;
		D3DPOOL ePool = D3DPOOL_DEFAULT;
		HRESULT hr = GGUISystem::GetInstance()->GetD3DDevice()->CreateVertexBuffer(
			uiSize, uiUsage, g_DXVertexFVF, ePool, &m_pDXVertexBuffer, NULL);
		if (FAILED(hr))
		{
			//Wait for add log
			return false;
		}
		return true;
	}
	//-----------------------------------------------------------------------------
	bool GGUIDXRenderManager::CreateDXIndexBuffer(SoInt nCapacity)
	{
		//尝试删除已有的DX索引缓冲区。
		SAFE_D3D_RELEASE(m_pDXIndexBuffer);
		//创建DX索引缓冲区。
		m_nDXIndexCapacity = nCapacity;
		SoUInt uiSize = m_nDXIndexCapacity * (SoUInt)(sizeof(SoIndexBufferUnit));
		//索引缓冲区数据不会变化，所以使用D3DPOOL_MANAGED。
		SoUInt uiUsage = 0;
		D3DPOOL ePool = D3DPOOL_MANAGED;
		HRESULT hr = GGUISystem::GetInstance()->GetD3DDevice()->CreateIndexBuffer(
			uiSize, uiUsage, D3DFMT_INDEX16, ePool, &m_pDXIndexBuffer, NULL);
		if (FAILED(hr))
		{
			//Wait for add log
			return false;
		}
		//
		SoIndexBufferUnit* pIndexData = NULL;
		hr = m_pDXIndexBuffer->Lock(0, uiSize, (void**)&pIndexData, 0);
		if (FAILED(hr))
		{
			//Wait for add log
			return false;
		}
		SoInt nRectCount = m_nDXIndexCapacity / 2;
		SoInt nRectIndex = 0;
		while (nRectIndex < nRectCount)
		{
			SoInt nVertexIndex = nRectIndex * 4;
			pIndexData->_0 = nVertexIndex + 0;
			pIndexData->_1 = nVertexIndex + 1;
			pIndexData->_2 = nVertexIndex + 2;
			++pIndexData;
			pIndexData->_0 = nVertexIndex + 0;
			pIndexData->_1 = nVertexIndex + 2;
			pIndexData->_2 = nVertexIndex + 3;
			++pIndexData;
			//
			++nRectIndex;
		}
		m_pDXIndexBuffer->Unlock();
		return true;
	}
} //namespace GGUI
//-----------------------------------------------------------------------------
