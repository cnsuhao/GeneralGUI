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
	GGUIImagesetManager* GGUIImagesetManager::ms_pInstance = NULL;
	//-----------------------------------------------------------------------------
	GGUIImagesetManager::GGUIImagesetManager()
	:m_arrayImageset(NULL, 10)
	{
		ms_pInstance = this;
	}
	//-----------------------------------------------------------------------------
	GGUIImagesetManager::~GGUIImagesetManager()
	{
		ReleaseImagesetManager();
		ms_pInstance = NULL;
	}
	//-----------------------------------------------------------------------------
	bool GGUIImagesetManager::InitImagesetManager()
	{
		return true;
	}
	//-----------------------------------------------------------------------------
	void GGUIImagesetManager::ReleaseImagesetManager()
	{
		//先清零m_mapImagesetName2ID，再清除m_arrayImageset，
		//当m_mapImagesetName2ID为空后，调用ReleaseImageset()时遍历空map就会快很多。
		m_mapImagesetName2ID.clear();
		//
		SoInt nValidCount = m_arrayImageset.GetWriteIndex();
		for (SoInt i=0; i<nValidCount; ++i)
		{
			ReleaseImageset(i);
		}
	}
	//-----------------------------------------------------------------------------
	bool GGUIImagesetManager::CreateImagesetByFile(const tchar* pszImagesetFile, ImagesetID* pImagesetID)
	{
		return NULL;
	}
	//-----------------------------------------------------------------------------
	bool GGUIImagesetManager::CreateImagesetByTextureFile(const tchar* pszTextureFile, const GGUITinyString& strImagesetName, ImagesetID* pImagesetID, ImageRectID* pImageRectID)
	{
		DXTextureID newDXTextureID = GGUIDXTextureManager::GetInstance()->LoadTextureFromDisk(pszTextureFile);
		if (newDXTextureID == Invalid_DXTextureID)
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
		//判断名字为strImagesetName是否已经存在。
		ImagesetID alreadyExistImagesetID = GetImagesetIDByName(strImagesetName);
		if (alreadyExistImagesetID != Invalid_ImagesetID)
		{
			//已经存在。
			if (pImagesetID)
			{
				*pImagesetID = alreadyExistImagesetID;
			}
			return false;
		}
		//
		GGUIImageset* pImageset = new GGUIImageset;
		m_arrayImageset.AddElement(pImageset);
		ImagesetID newImagesetID = m_arrayImageset.GetWriteIndex() - 1;
		pImageset->SetImagesetID(newImagesetID);
		pImageset->SetImagesetName(strImagesetName.GetValue());
		//维护在map中。
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
		GGUIImageset* pImageset = m_arrayImageset.GetElement(theImagesetID);
		if (pImageset)
		{
			SAFE_DELETE(pImageset);
			m_arrayImageset.RemoveElement(theImagesetID);
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
