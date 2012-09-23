//-----------------------------------------------------------------------------
// GGUI窗口的容器类
// (C) oil
// 2012-09-16
//-----------------------------------------------------------------------------
#ifndef _GGUIWindowContainer_h_
#define _GGUIWindowContainer_h_
//-----------------------------------------------------------------------------
#include "GGUIWindowDefine.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	class GGUIWindow;
	//-----------------------------------------------------------------------------
	class GGUIWindowContainer : public SoTSingleton<GGUIWindowContainer>
	{
	public:
		GGUIWindowContainer();
		~GGUIWindowContainer();
		static GGUIWindowContainer* GetInstance();

		bool InitWindowContainer();
		void ReleaseWindowContainer();

		GGUIWindow* CreateUIWindow();
		void ReleaseUIWindow(WindowID theWindowID);
		GGUIWindow* GetUIWindow(WindowID theWindowID);
		bool IsOperationByWindowContainer();

	private:
		//一个WindowID对应着一个GGUIWindow对象。
		//用new出来的数组存储ID到对象的映射。WindowID也即数组的索引号（下标）。
		GGUIWindow** m_pWindowID2Object;
		//记录数组中最多存储多少个元素。
		SoInt m_nCapacity;
		//记录数组中索引号最大的有效元素的下一个索引号。
		//如果数组中最后一个有效元素的下标为M，则该值为(M+1）。
		SoInt m_nIndexEnd;
		//对GGUIWindow的创建，删除，赋值WindowID等操作，必须通过调用GGUIWindowContainer
		//的函数来操作；如果不按照这个规则，则报错。
		//m_bOperationByWindowContainer的取值只有SoTrue和SoFalse两种。
		SoBool m_bOperationByWindowContainer;
	};
	//-----------------------------------------------------------------------------
	inline GGUIWindowContainer* GGUIWindowContainer::GetInstance()
	{
		return GGUIWindowContainer::Instance();
	}
	//-----------------------------------------------------------------------------
	inline GGUIWindow* GGUIWindowContainer::GetUIWindow(WindowID theWindowID)
	{
		if (theWindowID >= 0 && theWindowID < m_nIndexEnd)
		{
			return m_pWindowID2Object[theWindowID];
		}
		else
		{
			return NULL;
		}
	}
	//-----------------------------------------------------------------------------
	inline bool GGUIWindowContainer::IsOperationByWindowContainer()
	{
		return (m_bOperationByWindowContainer == SoTrue);
	}
}
//-----------------------------------------------------------------------------
#endif //_GGUIWindowContainer_h_
//-----------------------------------------------------------------------------
