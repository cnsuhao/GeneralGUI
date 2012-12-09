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
		//������m_mapImagesetName2ID�������m_arrayImageset��
		//��m_mapImagesetName2IDΪ�պ󣬵���ReleaseImageset()ʱ������map�ͻ��ܶࡣ
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
		//
		GGUIImageset* pImageset = new GGUIImageset;
		m_arrayImageset.AddElement(pImageset);
		ImagesetID newImagesetID = m_arrayImageset.GetWriteIndex() - 1;
		pImageset->SetImagesetID(newImagesetID);
		pImageset->SetImagesetName(strImagesetName.GetValue());
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
	//-----------------------------------------------------------------------------
	bool GGUIImagesetManager::CreateFontImageset(const GGUITinyString& strImagesetName, 
		SoUInt uiWidth, SoUInt uiHeight, ImagesetID* pImagesetID)
	{
		ImagesetID newImagesetID = Invalid_ImagesetID;
		bool bCreateImageset = CreateImageset(strImagesetName, &newImagesetID);
		if (!bCreateImageset)
		{
			if (pImagesetID)
			{
				*pImagesetID = newImagesetID;
			}
			LOG_ERROR(TEXT("GGUIImagesetManager::CreateFontImageset : CreateImageset fail. ImagesetName[%s]"), strImagesetName.GetValue());
			return false;
		}
		GGUIImageset* pNewImageset = GetImageset(newImagesetID);
		if (pNewImageset == NULL)
		{
			if (pImagesetID)
			{
				*pImagesetID = newImagesetID;
			}
			LOG_ERROR(TEXT("GGUIImagesetManager::CreateFontImageset : pNewImageset == NULL"));
			return false;
		}
		//
		DXTextureID newDXTextureID = GGUIDXTextureManager::GetInstance()->CreateFontTexture(uiWidth, uiHeight);
		pNewImageset->SetDXTextureID(newDXTextureID);
		if (pImagesetID)
		{
			*pImagesetID = newImagesetID;
		}
		LOG_DEBUG(TEXT("GGUIImagesetManager::CreateFontImageset : success. ImagesetName[%s]"), strImagesetName.GetValue());
		return false;
	}
	//-----------------------------------------------------------------------------
	bool GGUIImagesetManager::AddFontGlyph(ImagesetID theImagesetID, const RECT& dest_rect, 
		unsigned char* pPixelBuffer, SoInt nWidth, SoInt nHeight, bool bEdge)
	{
		GGUIImageset* pImageset = GetImageset(theImagesetID);
		if (pImageset == NULL)
		{
			LOG_DEBUG(TEXT("GGUIImagesetManager::AddFontGlyph : pImageset == NULL; ImagesetID[%d]"), theImagesetID);
			return false;
		}
		DXTextureID theDXTextureID = pImageset->GetDXTextureID();
		return GGUIDXTextureManager::GetInstance()->DrawFontGlyph(theDXTextureID, dest_rect, pPixelBuffer, nWidth, nHeight, bEdge);
	}
} //namespace GGUI
//-----------------------------------------------------------------------------
