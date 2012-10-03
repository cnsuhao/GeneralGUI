//-----------------------------------------------------------------------------
// GGUI贴图的容器类
// (C) oil
// 2012-09-16
//
// 2012-09-21，每新建一个贴图对象，容器的有效下标就自增一次；每删除一个贴图对象，
// 容器的一个元素就被置为空。一旦容器的某个元素置为空后，我们就永远不再复用这个
// 元素了，这个元素的值就一直为空。
//-----------------------------------------------------------------------------
#include "GGUIStdAfx.h"
#include "GGUITextureContainer.h"
#include "GGUITexture.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	//-----------------------------------------------------------------------------
	GGUITextureContainer::GGUITextureContainer()
	:m_pTextureID2Object(0)
	,m_nCapacity(0)
	,m_nIndexEnd(0)
	,m_bOperationByTextureContainer(SoFalse)
	{

	}
	//-----------------------------------------------------------------------------
	GGUITextureContainer::~GGUITextureContainer()
	{
		ReleaseTextureContainer();
	}
	//-----------------------------------------------------------------------------
	bool GGUITextureContainer::InitTextureContainer()
	{
		m_nCapacity = 1000;
		m_pTextureID2Object = new GGUITexture*[m_nCapacity];
		memset(m_pTextureID2Object, 0, sizeof(GGUITexture*)*m_nCapacity);
		//
		GGUITexture::CreateIndexBuffer();
		return true;
	}
	//-----------------------------------------------------------------------------
	void GGUITextureContainer::ReleaseTextureContainer()
	{
		m_bOperationByTextureContainer = SoTrue;
		for (SoInt i=0; i<m_nIndexEnd; ++i)
		{
			if (m_pTextureID2Object[i])
			{
				delete m_pTextureID2Object[i];
				m_pTextureID2Object[i] = 0;
			}
		}
		m_bOperationByTextureContainer = SoFalse;
		delete [] m_pTextureID2Object;
		m_pTextureID2Object = 0;
		//
		GGUITexture::ReleaseIndexBuffer();
	}
	//-----------------------------------------------------------------------------
	GGUITexture* GGUITextureContainer::CreateUITexture()
	{
		if (m_nIndexEnd >= m_nCapacity)
		{
			//m_pTextureID2Object容器空间不够了，则把容器空间扩大到原来的2倍。
			SoUInt sizeOfOldArray = sizeof(GGUITexture*) * m_nCapacity;
			m_nCapacity *= 2;
			GGUITexture** pNewArray = new GGUITexture*[m_nCapacity];
			SoUInt sizeOfNewArray = sizeof(GGUITexture*) * m_nCapacity;
			memset(pNewArray, 0, sizeOfNewArray);
			memcpy_s(pNewArray, sizeOfNewArray, m_pTextureID2Object, sizeOfOldArray);
			delete [] m_pTextureID2Object;
			m_pTextureID2Object = pNewArray;
		}
		m_bOperationByTextureContainer = SoTrue;
		m_pTextureID2Object[m_nIndexEnd] = new GGUITexture;
		m_pTextureID2Object[m_nIndexEnd]->SetTextureID(m_nIndexEnd);
		m_bOperationByTextureContainer = SoFalse;
		++m_nIndexEnd;
		return m_pTextureID2Object[m_nIndexEnd-1];
	}
	//-----------------------------------------------------------------------------
	void GGUITextureContainer::ReleaseUITexture(TextureID theTextureID)
	{
		if (theTextureID >= 0 && theTextureID < m_nIndexEnd)
		{
			if (m_pTextureID2Object[theTextureID])
			{
				m_bOperationByTextureContainer = SoTrue;
				delete m_pTextureID2Object[theTextureID];
				m_pTextureID2Object[theTextureID] = 0;
				m_bOperationByTextureContainer = SoFalse;
			}
		}
		else
		{
			//Wait for add log
		}
	}
}
//-----------------------------------------------------------------------------
