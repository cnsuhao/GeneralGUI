//-----------------------------------------------------------------------------
// GGUI窗口的管理类
// (C) oil
// 2012-09-16
//-----------------------------------------------------------------------------
#ifndef _GGUIWindowManager_h_
#define _GGUIWindowManager_h_
//-----------------------------------------------------------------------------
namespace GGUI
{
	//-----------------------------------------------------------------------------
	#define RegisterWindowEventA(theWindowID, theWindowEventID, theFuncPointer) \
	{ \
		GGUI::stWindowEventDelegate* pDelegate = GGUI::GGUIWindowManager::GetInstance()->GetWindowEventDelegate(theWindowID); \
		if (pDelegate) \
		{ \
			if (theWindowEventID >= 0 && theWindowEventID < GGUI::WindowEvent_Max) \
			{ \
				pDelegate->theFunction[theWindowEventID].bind(theFuncPointer); \
			} \
		} \
	}
	//-----------------------------------------------------------------------------
	#define RegisterWindowEventB(theWindowID, theWindowEventID, theObjectPoint, theFuncPointer) \
	{ \
		GGUI::stWindowEventDelegate* pDelegate = GGUI::GGUIWindowManager::GetInstance()->GetWindowEventDelegate(theWindowID); \
		if (pDelegate) \
		{ \
			if (theWindowEventID >= 0 && theWindowEventID < GGUI::WindowEvent_Max) \
			{ \
				pDelegate->theFunction[theWindowEventID].bind(theObjectPoint, theFuncPointer); \
			} \
		} \
	}
	//-----------------------------------------------------------------------------
	class GGUIWindow;
	//-----------------------------------------------------------------------------
	class GGUIWindowManager : public SoTSingleton<GGUIWindowManager>
	{
	public:
		GGUIWindowManager();
		~GGUIWindowManager();
		static GGUIWindowManager* GetInstance();

		bool InitWindowManager();
		void ReleaseWindowManager();
		void UpdateWindowManager(SoFloat fFrameTime);
		void RenderWindowManager();

		GGUIWindow* CreateUIWindow(eWindowType theType);
		void ReleaseUIWindow(WindowID theWindowID);
		GGUIWindow* GetUIWindow(WindowID theWindowID);
		bool IsOperationByWindowContainer();

		//根据WindowID获取这个窗口所对应的Delegate结构体。
		//如果这个窗口没有对应的Delegate，则为其申请一个。
		stWindowEventDelegate* GetWindowEventDelegate(WindowID theWindowID);
		void RaiseWindowEvent(WindowID theWindowID, DelegateID theDelegateID, eWindowEvent theEvent, SoUInt uiParam);

		//如果nIndex索引号的元素为有效值，则返回该元素；
		//如果是无效值，则使nIndex自增，当找到有效元素时，返回该元素和nIndex；
		//如果遍历数组完毕也没有找到有效元素，则返回NULL。
		//--nIndex [In][Out]
		//--pWindow [Out]
		bool Next(SoInt& nIndex, GGUIWindow*& pWindow);

	protected:
		void PostUpdateWindowManager();
		//创建一个stWindowEventDelegate对象。返回该对象在数组中的索引值。
		//目前看来不需要删除一个stWindowEventDelegate对象，所以没有删除函数。
		DelegateID CreateDelegate();

	private:
		//一个WindowID对应着一个GGUIWindow对象。
		//用new出来的数组存储ID到对象的映射。WindowID也即数组的索引号（下标）。
		//目前，数组中的元素还没有实现重复利用。一个窗口被delete后，其对应的数组
		//元素就被置为NULL，之后不会再次被使用。数组中有空洞，有空元素。
		//数组中存储的是窗口指针，用意是，当扩充数组时，我们只需要把窗口指针从
		//旧数组的内存中拷贝到新数组的内存中即可，不必拷贝窗口对象。
		GGUIWindow** m_pWindowID2Window;
		//记录数组中最多存储多少个元素。
		SoInt m_nCapacity;
		//记录数组中索引号最大的有效元素的下一个索引号。
		//如果数组中最后一个有效元素的下标为M，则该值为(M+1）。
		SoInt m_nIndexEnd;
		//对GGUIWindow的创建，删除，赋值WindowID等操作，必须通过调用GGUIWindowContainer
		//的函数来操作；如果不按照这个规则，则报错。
		//m_bOperationByWindowContainer的取值只有SoTrue和SoFalse两种。
		SoBool m_bOperationByWindowContainer;

		//如果用户为一个窗口注册了事件响应函数，则这个窗口就拥有一个有效的DelegateID，
		//这个ID就是事件响应结构体stWindowEventDelegate在数组中的索引号。
		//如果一个窗口没有注册任何事件响应函数，则它的DelegateID为无效值。
		//数组中存储的是结构体指针，用意是，当扩充数组时，我们只需要把结构体指针从
		//旧数组的内存中拷贝到新数组的内存中即可，不必拷贝结构体对象。
		stWindowEventDelegate** m_pDelegateID2Delegate;
		//记录Delegate数组中最多存储多少个元素。
		SoInt m_nDelegateCapacity;
		//记录数组中索引号最大的有效元素的下一个索引号。
		//如果数组中最后一个有效元素的下标为M，则该值为(M+1）。
		SoInt m_nDelegateIndexEnd;

	};
	//-----------------------------------------------------------------------------
	inline GGUIWindowManager* GGUIWindowManager::GetInstance()
	{
		return GGUIWindowManager::Instance();
	}
	//-----------------------------------------------------------------------------
	inline GGUIWindow* GGUIWindowManager::GetUIWindow(WindowID theWindowID)
	{
		if (theWindowID >= 0 && theWindowID < m_nIndexEnd)
		{
			return m_pWindowID2Window[theWindowID];
		}
		else
		{
			return NULL;
		}
	}
	//-----------------------------------------------------------------------------
	inline bool GGUIWindowManager::IsOperationByWindowContainer()
	{
		return (m_bOperationByWindowContainer == SoTrue);
	}
	//-----------------------------------------------------------------------------
	inline void GGUIWindowManager::RaiseWindowEvent(WindowID theWindowID, DelegateID theDelegateID, eWindowEvent theEvent, SoUInt uiParam)
	{
		if (theDelegateID >= 0 && theDelegateID < m_nDelegateIndexEnd)
		{
			if (theEvent >= 0 && theEvent < WindowEvent_Max)
			{
				DelegateForWindowEvent& theDelegate = m_pDelegateID2Delegate[theDelegateID]->theFunction[theEvent];
				if (!theDelegate.empty())
				{
					theDelegate(theWindowID, uiParam);
				}
			}
		}
	}
}
//-----------------------------------------------------------------------------
#endif //_GGUIWindowManager_h_
//-----------------------------------------------------------------------------
