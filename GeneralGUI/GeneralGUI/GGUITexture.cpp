//-----------------------------------------------------------------------------
// GGUI�ؼ���ʹ�õ���ͼ
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
			::MessageBox(NULL, TEXT("һ��Ҫʹ��GGUITextureContainer������GGUITexture��"), TEXT("GGUI Error"), MB_OK);
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
			::MessageBox(NULL, TEXT("һ��Ҫʹ��GGUITextureContainer���ͷ�GGUITexture��"), TEXT("GGUI Error"), MB_OK);
		}
	}
	//-----------------------------------------------------------------------------
	bool GGUITexture::LoadTexture(const tchar* pFileName)
	{
		if (!pFileName)
		{
			return false;
		}
		//����ɾ������ͼ��
		SAFE_D3D_RELEASE(m_pTexture);
		//���ʹ��ͼƬ�Ŀ�ߣ����Ҳ�Ҫ������2���ݡ�
		SoUInt uiWidth = D3DX_DEFAULT_NONPOW2;
		SoUInt uiHeight = D3DX_DEFAULT_NONPOW2;
		//��Ӧ��ʹ��MipMap��
		SoUInt uiMipLevels = 1;
		//��;��ʹ��Ĭ��ֵ��
		SoUInt uiUsage = 0;
		//���ظ�ʽ��
		D3DFORMAT eFormat = D3DFMT_UNKNOWN;
		//ʹ���й��ڴ�أ���Ϊ��ͼ�����ݲ��ᱻƵ���ı䣨��������ı䣩�����й��ڴ�صĺô����豸��ʧ�󲻱����´�����
		D3DPOOL ePool = D3DPOOL_MANAGED;
		//ͼƬ���˷�ʽ������Ҫ���ˣ���ΪTexture��û�������š�
		SoUInt uiFilter = D3DX_FILTER_NONE; //D3DX_FILTER_LINEAR;
		SoUInt uiMipFilter = D3DX_FILTER_NONE;
		//��ʹ�ùؼ�ɫ�滻��
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

		//���ں�����
		pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		//�����ں����������
		pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		//����Alpha��ֵ����Դ
		//ʹ�ö�����ɫ��Alphaֵ
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
			//�����������Ѿ��������ˣ�ֱ�ӷ��ء�
			return true;
		}
		//����������
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
			::MessageBox(NULL, TEXT("һ��Ҫʹ��GGUITextureContainer����ֵTextureID��"), TEXT("GGUI Error"), MB_OK);
		}
	}
	//-----------------------------------------------------------------------------
	bool GGUITexture::CreateVertexBuffer()
	{
		SoUInt uiSize = 4 * (SoUInt)(sizeof(SVertexType));
		//���㻺���������ݻᱻƵ���޸ģ�����ʹ��D3DUSAGE_DYNAMIC��
		SoUInt uiUsage = D3DUSAGE_DYNAMIC;
		//���㻺���������ݻᱻƵ���޸ģ�����ʹ��D3DPOOL_DEFAULT��
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
