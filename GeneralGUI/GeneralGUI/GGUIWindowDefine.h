//-----------------------------------------------------------------------------
// GGUI��Window��һЩ����
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

	//���ڵĸ������͡�
	enum eWindowType
	{
		WindowType_Invalid = -1, 
		WindowType_Base = 0, //GGUIWindow����
		WindowType_Button, //GGUIButton����
		WindowType_Picture, //GGUIPicture����
		WindowType_Max,
	};

	//�����ܹ�������Щ��Ϣ�¼���
	enum eWindowEvent
	{
		//��Чֵ��
		WindowEvent_Invalid = -1,
		//�������˴��ڵľ�������
		//�������������ڿɼ��������봰�ھ��������ڡ�
		//ע�⣺�����Ǵ����Ƿ񱻽��á���������ص��Ļ��������ͬһʱ����괦�ڶ�����ڵľ��������ڡ�
		WindowEvent_MouseEnterWindowArea = 0,
		//����뿪�˴��ڵľ�������
		//�������������ڿɼ�������뿪���ھ��������ڡ�
		//ע�⣺�����Ǵ����Ƿ񱻽��á�����괦�ڴ��ھ���������ʱ�������ɿɼ���Ϊ���ɼ�����Ҳ�ᴥ������¼���
		WindowEvent_MouseLeaveWindowArea,
		//�������ڴ����ϰ����ˡ�
		//��������������û�б����ã�����ڴ��ڵľ��������ڣ����������¡�
		WindowEvent_MouseLeftButtonClickDown,
		//�������ڴ�����̧���ˡ�
		//��������������û�б����ã�����ڴ��ڵľ��������ڣ�������̧��
		WindowEvent_MouseLeftButtonClickUp,
		//���ֵ��
		WindowEvent_Max,
	};

	//�����¼���delegate������
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
