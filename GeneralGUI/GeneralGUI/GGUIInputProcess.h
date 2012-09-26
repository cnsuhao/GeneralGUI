//-----------------------------------------------------------------------------
// GGUI处理用户的输入
// (C) oil
// 2012-09-26
//-----------------------------------------------------------------------------
#ifndef _GGUIInputProcess_h_
#define _GGUIInputProcess_h_
//-----------------------------------------------------------------------------
#include "GGUIScreenParam.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	class GGUIInputProcess : public SoTSingleton<GGUIInputProcess>
	{
	public:
		GGUIInputProcess();
		~GGUIInputProcess();
		static GGUIInputProcess* GetInstance();

		bool InitInputProcess();
		void ReleaseInputProcess();

		//--fNewPosX 以窗口客户区的左上角为(0,0)点，鼠标最新屏幕坐标的X值。可以为负数。
		//--fNewPosY 以窗口客户区的左上角为(0,0)点，鼠标最新屏幕坐标的Y值。可以为负数。
		//返回ture表示这个事件被本系统响应并处理了；
		//返回false表示本系统不关心并没有处理这个事件。
		bool OnMouseMove(SoFloat fNewPosX, SoFloat fNewPosY);

	private:
		//标记鼠标的各个操作状态。同一时刻，鼠标只能处于一个操作状态中。
		enum eMouseOpState
		{
			MouseOp_None, //没有鼠标操作。
			MouseOp_Hover, //鼠标悬浮在一个窗口上；这个窗口正在响应鼠标的悬浮状态。

		};

	private:
		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		//鼠标操作状态改变时处理函数
		void MouseOpHoverBegin(WindowID theWindowID);
		void MouseOpHoverEnd();
		//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

		bool IsMouseOutOfScreen(SoFloat fMousePosX, SoFloat fMousePosY);
		//根据鼠标坐标，得到鼠标落在了哪个窗口内部。
		WindowID GetWindowWhoContainMouse(SoFloat fMousePosX, SoFloat fMousePosY);

	private:
		//记录当前的鼠标操作状态。
		eMouseOpState m_eCurrentMouseOpState;
		//如果鼠标处于MouseOp_Hover中，则记录哪个窗口正在响应鼠标的悬浮状态。
		WindowID m_theWindowForMouseOpHover;
	};
	//-----------------------------------------------------------------------------
	inline GGUIInputProcess* GGUIInputProcess::GetInstance()
	{
		return GGUIInputProcess::Instance();
	}
	//-----------------------------------------------------------------------------
	inline bool GGUIInputProcess::IsMouseOutOfScreen(SoFloat fMousePosX, SoFloat fMousePosY)
	{
		if (fMousePosX < 0.0f || fMousePosX > GGUIScreenParam::ms_fScreenWidth)
		{
			return true;
		}
		if (fMousePosY < 0.0f || fMousePosY > GGUIScreenParam::ms_fScreenHeight)
		{
			return true;
		}
		return false;
	}
}
//-----------------------------------------------------------------------------
#endif //_GGUIInputProcess_h_
//-----------------------------------------------------------------------------
