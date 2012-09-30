//-----------------------------------------------------------------------------
// GGUI Button控件
// (C) oil
// 2012-09-30
//-----------------------------------------------------------------------------
#ifndef _GGUIButton_h_
#define _GGUIButton_h_
//-----------------------------------------------------------------------------
#include "GGUIWindow.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	class GGUIButton : public GGUIWindow
	{
	public:
		GGUIButton();
		virtual ~GGUIButton();

	protected:
		virtual void SetEnable(bool bEnable);
		virtual void UpdateUITexture();
	protected:
		//事件响应函数
		virtual void OnMouseEnterWindowArea();
		virtual void OnMouseLeaveWindowArea();
		virtual void OnMouseLeftButtonClickDown();
		virtual void OnMouseLeftButtonClickUp();

	protected:
		enum eButtonState
		{
			ButtonState_Normal,
			ButtonState_Hover,
			ButtonState_PushDown,
			ButtonState_Disable,
			ButtonState_Max,
		};

	protected:
		eButtonState m_eButtonState;
	};
}
//-----------------------------------------------------------------------------
#endif //_GGUIButton_h_
//-----------------------------------------------------------------------------
