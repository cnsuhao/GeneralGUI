//-----------------------------------------------------------------------------
// GGUI Picture控件
// (C) oil
// 2012-10-01
//-----------------------------------------------------------------------------
#ifndef _GGUIPicture_h_
#define _GGUIPicture_h_
//-----------------------------------------------------------------------------
#include "GGUIWindow.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	class GGUIPicture : public GGUIWindow
	{
		friend class GGUIWindowManager;
	public:
		enum ePictureShow
		{
			PictureShow_Auto, //自适应，维持图片的宽高比例，要么图片宽度等于窗口宽度，要么图片高度等于窗口高度
			PictureShow_Stretch, //拉伸，使图片撑满窗口的整个矩形区域
		};

	public:
		void SetPictureShowType(ePictureShow theShowType);
		ePictureShow GetPictureShowType() const;

	protected:
		GGUIPicture();
		virtual ~GGUIPicture();
		virtual void GenerateRenderUnit(stRenderUnit& theRenderUnit);

	protected:
		ePictureShow m_ePictureShow;
	};
}
//-----------------------------------------------------------------------------
#endif //_GGUIPicture_h_
//-----------------------------------------------------------------------------
