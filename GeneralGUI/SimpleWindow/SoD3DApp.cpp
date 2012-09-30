//-----------------------------------------------------------------------------
//                       D3D应用程序类  SoD3DApp.cpp
//
//                                                           (C)  oil
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "SoD3DApp.h"

SoD3DApp*           SoD3DApp::ms_pD3DApp = NULL;
IDirect3DDevice9**  SoD3DApp::ms_ppDevice = NULL;
//-----------------------------------------------------------------------------
//构造函数
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
//析构函数
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
//初始化
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
	m_strWinName = TEXT("So 3D程序");
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

	//定义背景画刷
	HBRUSH hBrush=CreateSolidBrush( m_dwBgColor );
	//定义图标
	HICON  hIcon=NULL;
    //hIcon=LoadIcon(m_hInstance,MAKEINTRESOURCE(IDI_ICON1));
	//定义光标
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
	//根据m_bSizeAble的值,对窗口风格进行调整
	if(m_bSizeAble)
		dwWinStyle |= WS_THICKFRAME;


	//窗口模式
	m_hMainHWND = CreateWindowEx(
            0,                   //扩展窗口风格,WS_EX_ACCEPTFILES支持文件拖放
            m_strWinName.c_str(), m_strWinName.c_str(),
            dwWinStyle,
            0,0,100,100,
            NULL,
            NULL,  //参数hMenu
            m_hInstance,
            NULL );


    if( !m_hMainHWND ) 
    {
		return NULL;	
	}

	////初始化窗口位置,窗口状态下才用
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

    //D3D对象
    m_pD3D = Direct3DCreate9( D3D_SDK_VERSION );
    if(m_pD3D==NULL)
	{
	    MessageBox(m_hMainHWND,TEXT("CreateD3D()失败"),NULL,MB_OK);
        return false;
	}

    D3DPRESENT_PARAMETERS d3dpp;             //创建设备的结构体
    ZeroMemory( &d3dpp, sizeof(d3dpp) );     //必须将结构体清零

	//d3dpp.BackBufferWidth            = 800;  //视口宽
	//d3dpp.BackBufferHeight           = 600;  //视口高

    d3dpp.BackBufferFormat           = D3DFMT_A8R8G8B8;  //  32位象素格式
	                                   //D3DFMT_UNKNOWN; 象素格式,建立一个与当前显示模式相匹配的后置缓冲

	d3dpp.BackBufferCount            = 1;  //后台缓存的个数
	d3dpp.MultiSampleType            = D3DMULTISAMPLE_NONE;  //后台缓存所使用的多重采样类型
	d3dpp.MultiSampleQuality         = 0;  //多重采样的质量水平

    d3dpp.SwapEffect                 = D3DSWAPEFFECT_DISCARD;//最有效的Swap效果
	//d3dpp.hDeviceWindow              = hWnd;
    d3dpp.Windowed                   = TRUE;                   //窗口模式

	d3dpp.EnableAutoDepthStencil     = TRUE;  //表示D3D自动创建并维护深度缓存和模板缓存
    d3dpp.AutoDepthStencilFormat     = D3DFMT_D24S8;  //深度缓存占24位,模板缓存占8位

	//d3dpp.Flags                      = 0;
	//d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	//d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;

    if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, //使用默认的显卡
		                            D3DDEVTYPE_HAL,     //创建HAL设备(使用HW加速装置)
									m_hMainHWND,
                 D3DCREATE_SOFTWARE_VERTEXPROCESSING, //顶点处理由支持所有显卡的SW处理创建,由HW创建性能更佳
                                    &d3dpp, &m_pDevice ) ) )
    {
	    MessageBox(m_hMainHWND,TEXT("CreateD3D()失败"),NULL,MB_OK);
        return false;
    }

	SoD3DApp::ms_pD3DApp = this;
	SoD3DApp::ms_ppDevice = &m_pDevice;

	//是否使用灯光,如果顶点有颜色,则顶点能起到光源作用,默认为使用灯光,这里把它关掉了
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
	//D3DFMT_A8R8G8B8 32位象素格式  D3DFMT_D24S8 深度缓存占24位,模板缓存占8位
	m_pDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL, //Z缓冲被重置为1.0f,模板缓冲被重置为0
		              m_dwBgColor, 1.0f, 0 );  //D3DCOLOR_XRGB(0,0,0)

	// Begin the scene
	if( SUCCEEDED( m_pDevice->BeginScene() ) )
	{

		//绘制内容
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
    //窗口激活状态消息的处理
	case WM_ACTIVATEAPP:
		m_bActive = ((BOOL)wParam)? true: false;
		return true;

    //窗口大小改变之后,就会得到这个消息
	case WM_SIZE:
		if(m_bSizeAble)
		{
			m_lClientW = LOWORD(lParam);  
			m_lClientH = HIWORD(lParam); 
		}
		return true;

	case WM_SYSCOMMAND:
		if(SC_MINIMIZE==wParam) //最小化
		{
			m_bIsMinimize = true;
		}
		else if(SC_RESTORE==wParam) //还原
		{
			m_bIsMinimize = false;
		}
		//不能返回true,返回false让Windows继续处理
		return false; 

    //销毁窗口消息的处理
    case WM_DESTROY:
		PostQuitMessage( 0 );
		return true;
	}

//	case WM_GETMINMAXINFO:  窗口大小改变之前来获取约束条件
//  不处理WM_CLOSE

	return false;
}
//-----------------------------------------------------------------------------
//只能在CreateWin()中使用的调整窗口大小的函数
void SoD3DApp::AdjustTheWindow(bool IsMenu,bool IsStatusBar)
{
	if(m_hMainHWND==NULL)  return;

    //获取系统屏幕大小
    long x1=GetSystemMetrics(SM_CXSCREEN);
    long y1=GetSystemMetrics(SM_CYSCREEN);
	//获得边框的宽高
	int SysFrameW   = GetSystemMetrics( SM_CXSIZEFRAME );
	int SysFrameH   = GetSystemMetrics( SM_CYSIZEFRAME );
	//获得标题栏高度
	int SysCaptionH = GetSystemMetrics( SM_CYCAPTION );


	int WindowW=m_lClientW+SysFrameW*2;
	//需要调整的主要是窗口高度
	int WindowH=m_lClientH+SysFrameH*2+SysCaptionH;
	if(IsMenu)
	{  WindowH += GetSystemMetrics( SM_CYMENU );  }
	if(IsStatusBar)
	{  WindowH += 20;  }	//获得状态栏高度, 我不知道怎样使用GetSystemMetrics()获得

	//求出窗口居于屏幕中央时的左上角位置
	x1=(x1-WindowW)/2;
	y1=(y1-WindowH)/2;

    //根据上面的值,调整窗口的位置  //BOOL AdjustWindowRect()
	MoveWindow(m_hMainHWND, x1, y1, WindowW, WindowH, TRUE);
	ShowWindow(m_hMainHWND, SW_SHOW);
}
//-----------------------------------------------------------------------------
void SoD3DApp::Get_ClientRect(RECT* pRect)
{
	//如果窗口还未创建,则失败,直接返回.
	if(m_hMainHWND==NULL)
		return;

	//获取窗口客户区的矩形范围
    //rect的值为0,0,宽,高
    GetClientRect( m_hMainHWND, pRect );

	//这个语句使rectWin的top,left变为窗口左上角相对于桌面的坐标.
    ClientToScreen( m_hMainHWND, (LPPOINT)pRect );

	//这个语句使rectWin的right,bottom变为窗口左上角相对于桌面的坐标.
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