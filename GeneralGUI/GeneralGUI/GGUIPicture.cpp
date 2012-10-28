//-----------------------------------------------------------------------------
// GGUI Button控件
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
		m_bDirty = true;
	}
	//-----------------------------------------------------------------------------
	GGUIPicture::ePictureShow GGUIPicture::GetPictureShowType()
	{
		return m_ePictureShow;
	}
}
//-----------------------------------------------------------------------------
