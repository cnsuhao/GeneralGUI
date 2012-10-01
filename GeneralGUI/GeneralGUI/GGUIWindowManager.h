//-----------------------------------------------------------------------------
// GGUI���ڵĹ�����
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

		//���nIndex�����ŵ�Ԫ��Ϊ��Чֵ���򷵻ظ�Ԫ�أ�
		//�������Чֵ����ʹnIndex���������ҵ���ЧԪ��ʱ�����ظ�Ԫ�غ�nIndex��
		//��������������Ҳû���ҵ���ЧԪ�أ��򷵻�NULL��
		//--nIndex [In][Out]
		//--pWindow [Out]
		bool Next(SoInt& nIndex, GGUIWindow*& pWindow);

	protected:
		void PostUpdateWindowManager();

	private:
		//һ��WindowID��Ӧ��һ��GGUIWindow����
		//��new����������洢ID�������ӳ�䡣WindowIDҲ������������ţ��±꣩��
		GGUIWindow** m_pWindowID2Object;
		//��¼���������洢���ٸ�Ԫ�ء�
		SoInt m_nCapacity;
		//��¼������������������ЧԪ�ص���һ�������š�
		//������������һ����ЧԪ�ص��±�ΪM�����ֵΪ(M+1����
		SoInt m_nIndexEnd;
		//��GGUIWindow�Ĵ�����ɾ������ֵWindowID�Ȳ���������ͨ������GGUIWindowContainer
		//�ĺ����������������������������򱨴���
		//m_bOperationByWindowContainer��ȡֵֻ��SoTrue��SoFalse���֡�
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