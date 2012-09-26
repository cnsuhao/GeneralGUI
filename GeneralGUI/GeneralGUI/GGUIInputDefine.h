//-----------------------------------------------------------------------------
// GGUI对用户输入的一些定义
// (C) oil
// 2012-09-16
//-----------------------------------------------------------------------------
#ifndef _GGUIInputDefine_h_
#define _GGUIInputDefine_h_
//-----------------------------------------------------------------------------
namespace GGUI
{
	enum eKeyButton
	{
		Key_Invalid = -1, //无效值

		Key_Max, //最大值
	};

	enum eMouseButton
	{
		Mouse_Invalid = -1, //无效值
		LeftMouse = 0, //鼠标左键
		RightMouse = 1, //鼠标右键
		MiddleMouse = 2, //鼠标中键
		Mouse_Max, //最大值
	};

	enum eInputEvent
	{
		InvalidEvent = -1, //无效值
		ButtonDown = 0, //按钮刚刚被按下了
		ButtonUp = 1, //按钮刚刚被抬起了
		MouseMove = 2, //鼠标移动了
		MouseWheel = 3, //鼠标滚轮滚动了
		MaxEvent, //最大值
	};
}
//-----------------------------------------------------------------------------
#endif //_GGUIInputDefine_h_
//-----------------------------------------------------------------------------
