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

		//如果nIndex索引号的元素为有效值，则返回该元素；
		//如果是无效值，则使nIndex自增，当找到有效元素时，返回该元素和nIndex；
		//如果遍历数组完毕也没有找到有效元素，则返回NULL。
		//--nIndex [In][Out]
		//--pWindow [Out]
		bool Next(SoInt& nIndex, GGUIWindow*& pWindow);

	protected:
		void PostUpdateWindowManager();

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
	inline GGUIWindowManager* GGUIWindowManager::GetInstance()
	{
		return GGUIWindowManager::Instance();
	}
	//-----------------------------------------------------------------------------
	inline GGUIWindow* GGUIWindowManager::GetUIWindow(WindowID theWindowID)
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
	inline bool GGUIWindowManager::IsOperationByWindowContainer()
	{
		return (m_bOperationByWindowContainer == SoTrue);
	}
}
//-----------------------------------------------------------------------------
#endif //_GGUIWindowManager_h_
//-----------------------------------------------------------------------------
