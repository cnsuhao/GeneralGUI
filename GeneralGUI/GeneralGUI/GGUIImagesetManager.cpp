//-----------------------------------------------------------------------------
// (C) oil
// 2012-10-20
//-----------------------------------------------------------------------------
#include "GGUIStdAfx.h"
#include "GGUIImagesetManager.h"
#include "GGUIImageset.h"
#include "GGUIDXTextureManager.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	//-----------------------------------------------------------------------------
	GGUIImagesetManager::GGUIImagesetManager()
	:m_arrayImageset(NULL)
	,m_nCapacity(0)
	,m_nIndexEnd(0)
	{

	}
	//-----------------------------------------------------------------------------
	GGUIImagesetManager::~GGUIImagesetManager()
	{
		ReleaseImagesetManager();
	}
	//-----------------------------------------------------------------------------
	bool GGUIImagesetManager::InitImagesetManager()
	{
		//��ʼ��GGUIImageset���顣
		m_nCapacity = 10;
		m_arrayImageset = new GGUIImageset*[m_nCapacity];
		memset(m_arrayImageset, 0, sizeof(GGUIImageset*)*m_nCapacity);
		return true;
	}
	//-----------------------------------------------------------------------------
	void GGUIImagesetManager::ReleaseImagesetManager()
	{
		m_mapImagesetName2ID.clear();
		//
		for (SoInt i=0; i<m_nIndexEnd; ++i)
		{
			if (m_arrayImageset[i])
			{
				SAFE_DELETE(m_arrayImageset[i]);
			}
		}
		SAFE_DELETE_ARRAY(m_arrayImageset);
	}
	//-----------------------------------------------------------------------------
	bool GGUIImagesetManager::CreateImagesetByFile(const tchar* pszImagesetFile, ImagesetID* pImagesetID)
	{
		return NULL;
	}
	//-----------------------------------------------------------------------------
	bool GGUIImagesetManager::CreateImagesetByTextureFile(const tchar* pszTextureFile, const GGUITinyString& strImagesetName, ImagesetID* pImagesetID, ImageRectID* pImageRectID)
	{
		DXTextureID newDXTextureID = Invalid_DXTextureID;
		bool bLoadTexture = GGUIDXTextureManager::GetInstance()->LoadTextureFromDisk(pszTextureFile, &newDXTextureID);
		if (!bLoadTexture)
		{
			return false;
		}
		ImagesetID newImagesetID = Invalid_ImagesetID;
		bool bCreateImageset = CreateImageset(strImagesetName, &newImagesetID);
		if (!bCreateImageset)
		{
			GGUIDXTextureManager::GetInstance()->ReleaseDXTexture(newDXTextureID);
			return false;
		}
		GGUIImageset* pNewImageset = GetImageset(newImagesetID);
		if (pNewImageset == NULL)
		{
			GGUIDXTextureManager::GetInstance()->ReleaseDXTexture(newDXTextureID);
			ReleaseImageset(newImagesetID);
			return false;
		}
		pNewImageset->SetDXTextureID(newDXTextureID);
		ImageRectID newImageRectID = Invalid_ImageRectID;
		pNewImageset->AddImageRect(GGUITinyString(TEXT("default")), 0.0f, 1.0f, 0.0f, 1.0f, &newImageRectID);
		if (pImagesetID)
		{
			*pImagesetID = newImagesetID;
		}
		if (pImageRectID)
		{
			*pImageRectID = newImageRectID;
		}
		return true;
	}
	//-----------------------------------------------------------------------------
	bool GGUIImagesetManager::CreateImageset(const GGUITinyString& strImagesetName, ImagesetID* pImagesetID)
	{
		//�ж�����ΪstrImagesetName�Ƿ��Ѿ����ڡ�
		ImagesetID alreadyExistImagesetID = GetImagesetIDByName(strImagesetName);
		if (alreadyExistImagesetID != Invalid_ImagesetID)
		{
			//�Ѿ����ڡ�
			if (pImagesetID)
			{
				*pImagesetID = alreadyExistImagesetID;
			}
			return false;
		}
		//����һ���µ�����Ԫ�ء�
		if (m_nIndexEnd >= m_nCapacity)
		{
			//�����ռ䲻���ˣ���������ռ�����ԭ����2����
			SoUInt sizeOfOldArray = sizeof(GGUIImageset*) * m_nCapacity;
			m_nCapacity *= 2;
			GGUIImageset** pNewArray = new GGUIImageset*[m_nCapacity];
			SoUInt sizeOfNewArray = sizeof(GGUIImageset*) * m_nCapacity;
			memset(pNewArray, 0, sizeOfNewArray);
			memcpy_s(pNewArray, sizeOfNewArray, m_arrayImageset, sizeOfOldArray);
			SAFE_DELETE_ARRAY(m_arrayImageset);
			m_arrayImageset = pNewArray;
		}
		ImagesetID newImagesetID = m_nIndexEnd;
		++m_nIndexEnd;
		//
		m_arrayImageset[newImagesetID] = new GGUIImageset;
		m_arrayImageset[newImagesetID]->SetImagesetID(newImagesetID);
		m_arrayImageset[newImagesetID]->SetImagesetName(strImagesetName.GetValue());
		//ά����map�С�
		m_mapImagesetName2ID.insert(std::make_pair(strImagesetName, newImagesetID));
		if (pImagesetID)
		{
			*pImagesetID = newImagesetID;
		}
		return true;
	}
	//-----------------------------------------------------------------------------
	void GGUIImagesetManager::ReleaseImageset(ImagesetID theImagesetID)
	{
		if (theImagesetID >= 0 && theImagesetID < m_nIndexEnd)
		{
			if (m_arrayImageset[theImagesetID])
			{
				SAFE_DELETE(m_arrayImageset[theImagesetID]);
			}
		}
		//
		for (mapImagesetName2ImagesetID::iterator it = m_mapImagesetName2ID.begin();
			it != m_mapImagesetName2ID.end();
			++it)
		{
			if (it->second == theImagesetID)
			{
				m_mapImagesetName2ID.erase(it);
				break;
			}
		}
	}

} //namespace GGUI
//-----------------------------------------------------------------------------
