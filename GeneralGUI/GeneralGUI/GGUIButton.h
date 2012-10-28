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
		friend class GGUIWindowManager;
	protected:
		GGUIButton();
		virtual ~GGUIButton();
		virtual void SetEnable(bool bEnable);

	protected:
		//事件响应函数
		virtual void OnMouseEnterWindowArea();
		virtual void OnMouseLeaveWindowArea();
		virtual void OnMouseLeftButtonClickDown();
		virtual void OnMouseLeftButtonClickUp();
		//
		virtual void GenerateRenderUnit(stRenderUnit& theRenderUnit);

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
