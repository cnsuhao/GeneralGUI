//-----------------------------------------------------------------------------
//                       D3DӦ�ó�����  SoD3DApp.cpp
//
//                                                           (C)  oil
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "SoD3DApp.h"

SoD3DApp*           SoD3DApp::ms_pD3DApp = NULL;
IDirect3DDevice9**  SoD3DApp::ms_ppDevice = NULL;
//-----------------------------------------------------------------------------
//���캯��
SoD3DApp::SoD3DApp(void)
{
    m_hInstance = NULL;
	m_hMainHWND = NULL;
	m_lClientW  = 640;
	m_lClientH  = 480;
    m_bActive   = false;
	m_bSizeAble = false;
	m_bIsMinimize = false;
	m_dwBgColor = 0U;

	m_pD3D    = NULL;
	m_pDevice = NULL;
}
//-----------------------------------------------------------------------------
//��������
SoD3DApp::~SoD3DApp(void)
{
	Release();
}
//-----------------------------------------------------------------------------
SoD3DApp* SoD3DApp::GetD3DApp(void)
{
	return SoD3DApp::ms_pD3DApp;
}
//-----------------------------------------------------------------------------
IDirect3DDevice9* SoD3DApp::GetD3DDevice(void)
{
	return (*ms_ppDevice);
}
//-----------------------------------------------------------------------------
//��ʼ��
bool SoD3DApp::Initialize( HINSTANCE hInstance )
{
	if(!hInstance)
		return false;

	m_hInstance = hInstance;
	return true;
}
//-----------------------------------------------------------------------------
void SoD3DApp::Release(void)
{

	if( m_pDevice != NULL) 
	{  m_pDevice->Release();  m_pDevice=NULL;  }

	if( m_pD3D != NULL)
	{  m_pD3D->Release();  m_pD3D=NULL;  }

	m_hMainHWND = NULL;
	SoD3DApp::ms_pD3DApp = NULL;
	SoD3DApp::ms_ppDevice = NULL;
}
//-----------------------------------------------------------------------------
void SoD3DApp::BeforeCreateWindow(void)
{
	m_strWinName = TEXT("So 3D����");
	m_bSizeAble = false;
	m_lClientW = 800;
	m_lClientH = 600;
	m_dwBgColor = RGB(128,128,128);

}
//-----------------------------------------------------------------------------
HWND SoD3DApp::CreateTheWindow(WNDPROC WinProc)
{
	if(m_hMainHWND!=NULL)
		return NULL;

	//���屳����ˢ
	HBRUSH hBrush=CreateSolidBrush( m_dwBgColor );
	//����ͼ��
	HICON  hIcon=NULL;
    //hIcon=LoadIcon(m_hInstance,MAKEINTRESOURCE(IDI_ICON1));
	//������
	HCURSOR hCursor=LoadCursor(NULL,IDC_ARROW);  //m_hInstance

    WNDCLASS wc={ CS_HREDRAW | CS_VREDRAW, WinProc,
		          0,0,
				  m_hInstance, 
				  hIcon, hCursor, hBrush,
				  NULL, m_strWinName.c_str()
				};

    if( !RegisterClass( &wc ) )
    {
		return NULL;	
	}

	//DWORD dwWinStyle = WS_BORDER|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX; //|WS_MAXIMIZEBOX|WS_THICKFRAME
	DWORD dwWinStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_POPUP | WS_VISIBLE;
	//����m_bSizeAble��ֵ,�Դ��ڷ����е���
	if(m_bSizeAble)
		dwWinStyle |= WS_THICKFRAME;


	//����ģʽ
	m_hMainHWND = CreateWindowEx(
            0,                   //��չ���ڷ��,WS_EX_ACCEPTFILES֧���ļ��Ϸ�
            m_strWinName.c_str(), m_strWinName.c_str(),
            dwWinStyle,
            0,0,100,100,
            NULL,
            NULL,  //����hMenu
            m_hInstance,
            NULL );


    if( !m_hMainHWND ) 
    {
		return NULL;	
	}

	////��ʼ������λ��,����״̬�²���
	//bool bIsMenu = (hMenu)? 1: 0;
	//bool bIsStatusBar = 0;           //( )? 1: 0;
	AdjustTheWindow(0,0);

    return m_hMainHWND;
}
//-----------------------------------------------------------------------------
//void SoD3DApp::AfterCreateWindow(void)
//{
//
//}
//-----------------------------------------------------------------------------
//void SoD3DApp::BeforeCreateD3D(void)
//{
//
//}
//-----------------------------------------------------------------------------
bool SoD3DApp::CreateD3D(void)
{
	if( !m_hMainHWND || m_pD3D)
		return false;

    //D3D����
    m_pD3D = Direct3DCreate9( D3D_SDK_VERSION );
    if(m_pD3D==NULL)
	{
	    MessageBox(m_hMainHWND,TEXT("CreateD3D()ʧ��"),NULL,MB_OK);
        return false;
	}

    D3DPRESENT_PARAMETERS d3dpp;             //�����豸�Ľṹ��
    ZeroMemory( &d3dpp, sizeof(d3dpp) );     //���뽫�ṹ������

	//d3dpp.BackBufferWidth            = 800;  //�ӿڿ�
	//d3dpp.BackBufferHeight           = 600;  //�ӿڸ�

    d3dpp.BackBufferFormat           = D3DFMT_A8R8G8B8;  //  32λ���ظ�ʽ
	                                   //D3DFMT_UNKNOWN; ���ظ�ʽ,����һ���뵱ǰ��ʾģʽ��ƥ��ĺ��û���

	d3dpp.BackBufferCount            = 1;  //��̨����ĸ���
	d3dpp.MultiSampleType            = D3DMULTISAMPLE_NONE;  //��̨������ʹ�õĶ��ز�������
	d3dpp.MultiSampleQuality         = 0;  //���ز���������ˮƽ

    d3dpp.SwapEffect                 = D3DSWAPEFFECT_DISCARD;//����Ч��SwapЧ��
	//d3dpp.hDeviceWindow              = hWnd;
    d3dpp.Windowed                   = TRUE;                   //����ģʽ

	d3dpp.EnableAutoDepthStencil     = TRUE;  //��ʾD3D�Զ�������ά����Ȼ����ģ�建��
    d3dpp.AutoDepthStencilFormat     = D3DFMT_D24S8;  //��Ȼ���ռ24λ,ģ�建��ռ8λ

	//d3dpp.Flags                      = 0;
	//d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	//d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;

    if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, //ʹ��Ĭ�ϵ��Կ�
		                            D3DDEVTYPE_HAL,     //����HAL�豸(ʹ��HW����װ��)
									m_hMainHWND,
                 D3DCREATE_SOFTWARE_VERTEXPROCESSING, //���㴦����֧�������Կ���SW������,��HW�������ܸ���
                                    &d3dpp, &m_pDevice ) ) )
    {
	    MessageBox(m_hMainHWND,TEXT("CreateD3D()ʧ��"),NULL,MB_OK);
        return false;
    }

	SoD3DApp::ms_pD3DApp = this;
	SoD3DApp::ms_ppDevice = &m_pDevice;

	//�Ƿ�ʹ�õƹ�,�����������ɫ,�򶥵����𵽹�Դ����,Ĭ��Ϊʹ�õƹ�,��������ص���
    m_pDevice->SetRenderState( D3DRS_LIGHTING, false );


	return true;
}
//-----------------------------------------------------------------------------
//void SoD3DApp::AfterCreateD3D(void)
//{
//
//}
//-----------------------------------------------------------------------------
void SoD3DApp::Render(void)
{
	//D3DFMT_A8R8G8B8 32λ���ظ�ʽ  D3DFMT_D24S8 ��Ȼ���ռ24λ,ģ�建��ռ8λ
	m_pDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL, //Z���屻����Ϊ1.0f,ģ�建�屻����Ϊ0
		              m_dwBgColor, 1.0f, 0 );  //D3DCOLOR_XRGB(0,0,0)

	// Begin the scene
	if( SUCCEEDED( m_pDevice->BeginScene() ) )
	{

		//��������
		Draw();

		m_pDevice->EndScene();
	}

	//RenderTarget();


	// Present the backbuffer contents to the display
	m_pDevice->Present( NULL, NULL, NULL, NULL );
}
//-----------------------------------------------------------------------------
void SoD3DApp::Draw(void)
{

}
//-----------------------------------------------------------------------------
LRESULT SoD3DApp::MsgProcess( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    switch( uMsg )
    {
    //���ڼ���״̬��Ϣ�Ĵ���
	case WM_ACTIVATEAPP:
		m_bActive = ((BOOL)wParam)? true: false;
		return true;

    //���ڴ�С�ı�֮��,�ͻ�õ������Ϣ
	case WM_SIZE:
		if(m_bSizeAble)
		{
			m_lClientW = LOWORD(lParam);  
			m_lClientH = HIWORD(lParam); 
		}
		return true;

	case WM_SYSCOMMAND:
		if(SC_MINIMIZE==wParam) //��С��
		{
			m_bIsMinimize = true;
		}
		else if(SC_RESTORE==wParam) //��ԭ
		{
			m_bIsMinimize = false;
		}
		//���ܷ���true,����false��Windows��������
		return false; 

    //���ٴ�����Ϣ�Ĵ���
    case WM_DESTROY:
		PostQuitMessage( 0 );
		return true;
	}

//	case WM_GETMINMAXINFO:  ���ڴ�С�ı�֮ǰ����ȡԼ������
//  ������WM_CLOSE

	return false;
}
//-----------------------------------------------------------------------------
//ֻ����CreateWin()��ʹ�õĵ������ڴ�С�ĺ���
void SoD3DApp::AdjustTheWindow(bool IsMenu,bool IsStatusBar)
{
	if(m_hMainHWND==NULL)  return;

    //��ȡϵͳ��Ļ��С
    long x1=GetSystemMetrics(SM_CXSCREEN);
    long y1=GetSystemMetrics(SM_CYSCREEN);
	//��ñ߿�Ŀ��
	int SysFrameW   = GetSystemMetrics( SM_CXSIZEFRAME );
	int SysFrameH   = GetSystemMetrics( SM_CYSIZEFRAME );
	//��ñ������߶�
	int SysCaptionH = GetSystemMetrics( SM_CYCAPTION );


	int WindowW=m_lClientW+SysFrameW*2;
	//��Ҫ��������Ҫ�Ǵ��ڸ߶�
	int WindowH=m_lClientH+SysFrameH*2+SysCaptionH;
	if(IsMenu)
	{  WindowH += GetSystemMetrics( SM_CYMENU );  }
	if(IsStatusBar)
	{  WindowH += 20;  }	//���״̬���߶�, �Ҳ�֪������ʹ��GetSystemMetrics()���

	//������ھ�����Ļ����ʱ�����Ͻ�λ��
	x1=(x1-WindowW)/2;
	y1=(y1-WindowH)/2;

    //���������ֵ,�������ڵ�λ��  //BOOL AdjustWindowRect()
	MoveWindow(m_hMainHWND, x1, y1, WindowW, WindowH, TRUE);
	ShowWindow(m_hMainHWND, SW_SHOW);
}
//-----------------------------------------------------------------------------
void SoD3DApp::Get_ClientRect(RECT* pRect)
{
	//������ڻ�δ����,��ʧ��,ֱ�ӷ���.
	if(m_hMainHWND==NULL)
		return;

	//��ȡ���ڿͻ����ľ��η�Χ
    //rect��ֵΪ0,0,��,��
    GetClientRect( m_hMainHWND, pRect );

	//������ʹrectWin��top,left��Ϊ�������Ͻ���������������.
    ClientToScreen( m_hMainHWND, (LPPOINT)pRect );

	//������ʹrectWin��right,bottom��Ϊ�������Ͻ���������������.
    ClientToScreen( m_hMainHWND, (LPPOINT)pRect + 1 );
}
////-----------------------------------------------------------------------------
//DWORD SoD3DApp::GetMaxVertexBlendMatrixIndex()
//{
//	D3DCAPS9 d3dCaps;
//	(*SoD3DApp::ms_ppDevice)->GetDeviceCaps( &d3dCaps );
//	return d3dCaps.MaxVertexBlendMatrixIndex;
//}
//-----------------------------------------------------------------------------
//  SoD3DApp.cpp
//-----------------------------------------------------------------------------