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
	//
	typedef SoInt DelegateID;
	static const DelegateID Invalid_DelegateID = -1;

	//窗口的各个类型。
	enum eWindowType
	{
		WindowType_Invalid = -1, 
		WindowType_Base = 0, //GGUIWindow类型
		WindowType_Button, //GGUIButton类型
		WindowType_Picture, //GGUIPicture类型
		WindowType_Max,
	};

	//窗口能够触发哪些消息事件。
	enum eWindowEvent
	{
		//无效值。
		WindowEvent_Invalid = -1,
		//鼠标进入了窗口的矩形区域。
		//触发条件：窗口可见，鼠标进入窗口矩形区域内。
		//注意：不考虑窗口是否被禁用。如果窗口重叠的话，会出现同一时刻鼠标处于多个窗口的矩形区域内。
		WindowEvent_MouseEnterWindowArea = 0,
		//鼠标离开了窗口的矩形区域。
		//触发条件：窗口可见，鼠标离开窗口矩形区域内。
		//注意：不考虑窗口是否被禁用。当鼠标处于窗口矩形区域内时，窗口由可见变为不可见，则也会触发这个事件。
		WindowEvent_MouseLeaveWindowArea,
		//鼠标左键在窗口上按下了。
		//触发条件：窗口没有被禁用，鼠标在窗口的矩形区域内，鼠标左键按下。
		WindowEvent_MouseLeftButtonClickDown,
		//鼠标左键在窗口上抬起了。
		//触发条件：窗口没有被禁用，鼠标在窗口的矩形区域内，鼠标左键抬起。
		WindowEvent_MouseLeftButtonClickUp,
		//最大值。
		WindowEvent_Max,
	};

	//窗口事件的delegate函数。
	typedef fastdelegate::FastDelegate2<SoUInt, SoUInt> DelegateForWindowEvent;
	//
	struct stWindowEventDelegate
	{
		DelegateForWindowEvent theFunction[WindowEvent_MouseLeftButtonClickUp];
	};
}
//-----------------------------------------------------------------------------
#endif //_GGUIWindowDefine_h_
//-----------------------------------------------------------------------------
