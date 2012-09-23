//-----------------------------------------------------------------------------
//                       D3DӦ�ó�����  SoD3DApp.h
//
//1.����ԭ��CApplication�������,����D3D�Ĵ���������.
//
//2.������,����������,��CreateWin()�ڲ�.
//4.WS_THICKFRAME�����ܷ�ı�ı䴰�ڴ�С, ��һ��Ҫ��m_bSizeAble�����
//  Ĭ��Ϊ���ܸı䴰�ڴ�С
//5.ͼ��,��궼��Init()�����ж���
//6.�˵�����״̬���е�������,����������Ϊ��Ա����
//7.10-19,������SoFontManager
//                                                           (C)  oil
//                                                       ��ʼ����:2008.06.10
//                                                       ��������:2008.10.19
//-----------------------------------------------------------------------------
#pragma once
// this will assume smaller exe  
//�ܾ�����MFC�Ķ���,�⽫�������buildʱ��
#define WIN32_LEAN_AND_MEAN 

#include <windows.h>


//-----------------------------------------------------------------------------
class SoD3DApp
{
private:

	HINSTANCE m_hInstance;  //���̾��

protected:

    HWND      m_hMainHWND;  //���ھ��
    long      m_lClientW;  //�ͻ����Ŀ��
	long      m_lClientH;
    bool      m_bActive;   //���ڵļ���״̬
	bool      m_bSizeAble;  //�Ƿ���Ե������ڴ�С
	bool      m_bIsMinimize; //�Ƿ�����С��״̬
	tstring   m_strWinName;  //���ڵı���,ͬʱҲ�Ǵ����������
	//WinAPI��D3DAPIʹ�õ���ɫֵ���Ͷ���DWORD,
	//WinAPI��RGB()��õ�,D3DAPI��D3DCOLOR_ARGB()����D3DCOLOR_XRGB()
	DWORD     m_dwBgColor;  


	LPDIRECT3D9         m_pD3D;           //D3D����
	IDirect3DDevice9*   m_pDevice;        //D3D�豸

	static SoD3DApp*  ms_pD3DApp;
	//ms_ppDevice�洢��m_pDevice�ĵ�ַ,*ms_ppDevice����m_pDevice
	//����,����m_pDevice������ʲô�仯,*ms_ppDevice����ӳ��m_pDevice��ֵ
	static IDirect3DDevice9**  ms_ppDevice;


private:   //�������̳еĺ���

	//ֻ����CreateWin()��ʹ�õĵ������ڴ�С�ĺ���
	//�ж��Ƿ�ӵ�в˵�����״̬��
	//�������ܻ����ж��Ƿ�ӵ�й�����
	void AdjustTheWindow(bool IsMenu, bool IsStatusBar);

public:

	SoD3DApp(void);
	virtual ~SoD3DApp(void);


	//���������ʵ���������
	static SoD3DApp* CreateInstance(void);
	//�����̬�����ṩ��������ָ��
	static SoD3DApp* GetD3DApp(void);
	//�����̬�����ṩ�豸ָ��
	static IDirect3DDevice9* GetD3DDevice(void);


	//��ʼ��
	virtual bool Initialize( HINSTANCE hInstance );
	//Release
	virtual void Release(void);





	//��������֮ǰ���趨
	//���������Ϊ��Ա������ֵ
	//�˵�����״̬������ϢҲӦ�������ﴫ��
	//bSizeAble--���ڷ��,ֻ�����޸��Ƿ���Ե������ڴ�С
	virtual void BeforeCreateWindow(void);
	//��ʼ�������촰��
	HWND CreateTheWindow( WNDPROC WinProc );
	////��������֮��Ĳ���
	//virtual void AfterCreateWindow(void);


	//virtual void BeforeCreateD3D(void);
	virtual bool CreateD3D(void);
	//virtual void AfterCreateD3D(void);


	//�����ͳ�ʼ��D3D����������Ҫ�ĸ��ֶ�����Դ
	virtual bool InitResource(void)  { return true; };
	virtual void ClearResource(void) { };

	//--------------------------------------------------------------����

	virtual void BeforeUpdate(void)  { };
	virtual void Update(void)  { };


	//--------------------------------------------------------------��Ⱦ

	//��Ҫ�ǵ���SetRenderTarget()
	virtual void PreRender(void)  { };

	virtual void Render(void);

	virtual void AfterRender(void)  { };

	//��BeginScene()��EndScene()������֮��ʹ��
	virtual void Draw(void);



    //������������Ϣ(��Ϣѭ������)
	//��������Ϣ�򷵻�TRUE, û�д�����Ϣ�򷵻�FALSE
    virtual bool MsgProcess( UINT uMsg, WPARAM wParam, LPARAM lParam );




	//---------------------------------------------------------------���ʲ�������

	//�����ڿͻ��������ϽǺ����½�����Ļ�е�����ֵ���RECT�ṹ��
	//ֻ���ڴ��ڱ�������ʹ��
	void Get_ClientRect(RECT* pRect);
	HINSTANCE  GetAppInstance(void);
	HWND GetMainHWND(void);
    bool IsActive(void);
	bool IsMinimize(void);
    long GetClientWidth(void);
	long GetClientHeight(void);


	////��SoAllocateHierarchy::GenerateSkinnedMesh()����ʹ��
	//static DWORD GetMaxVertexBlendMatrixIndex();


};
//-----------------------------------------------------------------------------
//  ���������Ķ���
//-----------------------------------------------------------------------------
inline HINSTANCE  SoD3DApp::GetAppInstance(void)
{
	return m_hInstance;
}
//-----------------------------------------------------------------------------
inline HWND  SoD3DApp::GetMainHWND(void)
{
	return m_hMainHWND;
}
//-----------------------------------------------------------------------------
inline bool  SoD3DApp::IsActive(void)
{
	return m_bActive;
}
//-----------------------------------------------------------------------------
inline bool  SoD3DApp::IsMinimize(void)
{
	return m_bIsMinimize;
}
//-----------------------------------------------------------------------------
inline long  SoD3DApp::GetClientWidth(void)
{
	return m_lClientW;
}
//-----------------------------------------------------------------------------
inline long  SoD3DApp::GetClientHeight(void)
{
	return m_lClientH;
}
//-----------------------------------------------------------------------------
//  SoD3DApp.h
//-----------------------------------------------------------------------------
