//-----------------------------------------------------------------------------
// GGUI窗口的容器类
// (C) oil
// 2012-09-16
//-----------------------------------------------------------------------------
#include "GGUIStdAfx.h"
#include "GGUIWindowContainer.h"
#include "GGUIWindow.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	//-----------------------------------------------------------------------------
	GGUIWindowContainer::GGUIWindowContainer()
	:m_pWindowID2Object(0)
	,m_nCapacity(0)
	,m_nIndexEnd(0)
	,m_bOperationByWindowContainer(SoFalse)
	{

	}
	//-----------------------------------------------------------------------------
	GGUIWindowContainer::~GGUIWindowContainer()
	{
		ReleaseWindowContainer();
	}
	//-----------------------------------------------------------------------------
	bool GGUIWindowContainer::InitWindowContainer()
	{
		m_nCapacity = 1000;
		m_pWindowID2Object = new GGUIWindow*[m_nCapacity];
		memset(m_pWindowID2Object, 0, sizeof(GGUIWindow*)*m_nCapacity);
		return true;
	}
	//-----------------------------------------------------------------------------
	void GGUIWindowContainer::ReleaseWindowContainer()
	{
		for (SoInt i=0; i<m_nIndexEnd; ++i)
		{
			if (m_pWindowID2Object[i])
			{
				delete m_pWindowID2Object[i];
				m_pWindowID2Object[i] = 0;
			}
		}
		delete [] m_pWindowID2Object;
		m_pWindowID2Object = 0;
	}
	//-----------------------------------------------------------------------------
	GGUIWindow* GGUIWindowContainer::CreateUIWindow()
	{
		if (m_nIndexEnd >= m_nCapacity)
		{
			//m_pWindowID2Object容器空间不够了，则把容器空间扩大到原来的2倍。
			SoUInt sizeOfOldArray = sizeof(GGUIWindow*) * m_nCapacity;
			m_nCapacity *= 2;
			GGUIWindow** pNewArray = new GGUIWindow*[m_nCapacity];
			SoUInt sizeOfNewArray = sizeof(GGUIWindow*) * m_nCapacity;
			memset(pNewArray, 0, sizeOfNewArray);
			memcpy_s(pNewArray, sizeOfNewArray, m_pWindowID2Object, sizeOfOldArray);
			delete [] m_pWindowID2Object;
			m_pWindowID2Object = pNewArray;
		}
		m_bOperationByWindowContainer = SoTrue;
		m_pWindowID2Object[m_nIndexEnd] = new GGUIWindow;
		m_pWindowID2Object[m_nIndexEnd]->SetWindowID(m_nIndexEnd);
		m_bOperationByWindowContainer = SoFalse;
		++m_nIndexEnd;
		return m_pWindowID2Object[m_nIndexEnd-1];
	}
	//-----------------------------------------------------------------------------
	void GGUIWindowContainer::ReleaseUIWindow(WindowID theWindowID)
	{
		if (theWindowID >= 0 && theWindowID < m_nIndexEnd)
		{
			if (m_pWindowID2Object[theWindowID])
			{
				m_bOperationByWindowContainer = SoTrue;
				delete m_pWindowID2Object[theWindowID];
				m_pWindowID2Object[theWindowID] = 0;
				m_bOperationByWindowContainer = SoFalse;
			}
		}
		else
		{
			//Wait for add log
		}
	}
	//-----------------------------------------------------------------------------
	bool GGUIWindowContainer::Next(SoInt& nIndex, GGUIWindow*& pWindow)
	{
		if (nIndex >= 0 && nIndex < m_nIndexEnd)
		{
			if (m_pWindowID2Object[nIndex])
			{
				pWindow = m_pWindowID2Object[nIndex];
				return true;
			}
			else
			{
				++nIndex;
				return Next(nIndex, pWindow);
			}
		}
		else
		{
			pWindow = NULL;
			return false;
		}
	}
}
//-----------------------------------------------------------------------------
