//-----------------------------------------------------------------------------
// GGUI对Window的一些定义
// (C) oil
// 2012-09-23
//-----------------------------------------------------------------------------
#ifndef _GGUIWindowDefine_h_
#define _GGUIWindowDefine_h_
//-----------------------------------------------------------------------------
namespace GGUI
{
	typedef SoInt WindowID;
	static const WindowID Invalid_WindowID = -1;

	enum eWindowType
	{
		WindowType_Invalid = -1, 
		WindowType_Base = 0, //GGUIWindow类型
		WindowType_Button, //GGUIButton类型
		WindowType_Max,
	};
}
//-----------------------------------------------------------------------------
#endif //_GGUIWindowDefine_h_
//-----------------------------------------------------------------------------
