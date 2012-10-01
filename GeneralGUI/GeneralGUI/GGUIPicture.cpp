//-----------------------------------------------------------------------------
// GGUI Button�ؼ�
// (C) oil
// 2012-09-30
//-----------------------------------------------------------------------------
#include "GGUIStdAfx.h"
#include "GGUIPicture.h"
#include "GGUITexture.h"
#include "GGUITextureContainer.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	//-----------------------------------------------------------------------------
	GGUIPicture::GGUIPicture()
	:m_ePictureShow(PictureShow_Auto)
	{
		m_eMyWindowType = WindowType_Picture;
	}
	//-----------------------------------------------------------------------------
	GGUIPicture::~GGUIPicture()
	{

	}
	//-----------------------------------------------------------------------------
	void GGUIPicture::SetPictureShowType(ePictureShow theShowType)
	{
		m_ePictureShow = theShowType;
		m_bShouldUpdateUITexture = true;
	}
	//-----------------------------------------------------------------------------
	GGUIPicture::ePictureShow GGUIPicture::GetPictureShowType()
	{
		return m_ePictureShow;
	}
	//-----------------------------------------------------------------------------
	void GGUIPicture::UpdateUITexture()
	{
		if (m_ePictureShow == PictureShow_Auto)
		{
			SoFloat fDestPosX = m_fPositionX;
			SoFloat fDestPosY = m_fPositionY;
			SoFloat fDestWidth = m_fWidth;
			SoFloat fDestHeight = m_fHeight;
			//��ȡͼƬԴ�ļ��Ŀ�ߡ�
			GGUITexture* pUITexture = GGUITextureContainer::GetInstance()->GetUITexture(m_nMyTextureID);
			if (pUITexture)
			{
				SoFloat fTextureSourceWidth = (SoFloat)pUITexture->GetSourceWidth();
				SoFloat fTextureSourceHeight = (SoFloat)pUITexture->GetSourceHeight();
				SoFloat fWindowHeightWidth = m_fHeight / m_fWidth;
				SoFloat fTextureHeightWidth = fTextureSourceHeight / fTextureSourceWidth;
				if (fWindowHeightWidth > fTextureHeightWidth)
				{
					//��Ȳ��䣬�Ը߶Ƚ��е�����
					fDestHeight = m_fWidth * fTextureHeightWidth;
					fDestPosY += (m_fHeight - fDestHeight) * 0.5f;
				}
				else if (fWindowHeightWidth < fTextureHeightWidth)
				{
					fDestWidth = m_fHeight / fTextureHeightWidth;
					fDestPosX += (m_fWidth - fDestWidth) * 0.5f;
				}
				else
				{
					//ʲô��������
				}
			}
			SoUInt32 uiColor = SoMakeColorRGBA(m_fColorR, m_fColorG, m_fColorB, m_fColorA);
			pUITexture->UpdateVertexBuffer(fDestPosX, fDestPosY, m_fPositionZ, fDestWidth, fDestHeight, uiColor);
		}
	}
}
//-----------------------------------------------------------------------------
