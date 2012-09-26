//-----------------------------------------------------------------------------
// GGUI���ڵ�������
// (C) oil
// 2012-09-16
//-----------------------------------------------------------------------------
#ifndef _GGUIWindowContainer_h_
#define _GGUIWindowContainer_h_
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

		//���nIndex�����ŵ�Ԫ��Ϊ��Чֵ���򷵻ظ�Ԫ�أ�
		//�������Чֵ����ʹnIndex���������ҵ���ЧԪ��ʱ�����ظ�Ԫ�غ�nIndex��
		//��������������Ҳû���ҵ���ЧԪ�أ��򷵻�NULL��
		//--nIndex [In][Out]
		//--pWindow [Out]
		bool Next(SoInt& nIndex, GGUIWindow*& pWindow);

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
		//�ĺ����������������������������򱨴�
		//m_bOperationByWindowContainer��ȡֵֻ��SoTrue��SoFalse���֡�
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
