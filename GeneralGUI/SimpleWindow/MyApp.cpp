//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "MyApp.h"
#include "SoNSD3D.h"

//-----------------------------------------------------------------------------
SoD3DApp* SoD3DApp::CreateInstance(void)
{
	return new MyApp;
}
//-----------------------------------------------------------------------------
MyApp::MyApp(void)
:SoD3DApp()
,m_pUIWindow(NULL)
{

}
//-----------------------------------------------------------------------------
MyApp::~MyApp(void)
{

}
//-----------------------------------------------------------------------------
void MyApp::BeforeCreateWindow(void)
{
	m_strWinName = TEXT("TEST");
	m_bSizeAble = false;
	m_lClientW = 800;
	m_lClientH = 600;
	m_dwBgColor = RGB(188,188,188);
}

//-----------------------------------------------------------------------------
bool MyApp::InitResource(void)
{
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//创建GGUI系统
	GGUISystem::CreateInstance();
	GGUISystem::GetInstance()->InitUISystem(SoD3DApp::GetD3DDevice(), (SoFloat)m_lClientW, (SoFloat)m_lClientH);
	//
	CreateUIWindowA();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	return true;
}

//-----------------------------------------------------------------------------
void MyApp::ClearResource(void)
{
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	ReleaseUIWindowA();
	//释放GGUI系统
	GGUISystem::ReleaseInstance();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
}

//-----------------------------------------------------------------------------
void MyApp::Update(void)
{
	m_pUIWindow->UpdateWindow(0.0f);
}

//-----------------------------------------------------------------------------
void MyApp::Draw(void)
{
	if (m_pUIWindow)
	{
		m_pUIWindow->RenderWindow();
	}
}

//-----------------------------------------------------------------------------
LRESULT MyApp::MsgProcess(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_MOUSEMOVE:
		{
			//本窗口处理了这个消息。
			int xPos = LOWORD(lParam);
			int yPos = HIWORD(lParam);
			GGUISystem::GetInstance()->InjectMouseEvent(MouseMove, Mouse_Invalid, (SoFloat)xPos, (SoFloat)yPos);
		}
		break;
	default:
		break;
	}
	//
	return __super::MsgProcess(uMsg, wParam, lParam);
}

//-----------------------------------------------------------------------------
void MyApp::CreateUIWindowA()
{
	m_pUIWindow = GGUIWindowContainer::GetInstance()->CreateUIWindow();
	m_pUIWindow->SetPositionX(10.0f);
	m_pUIWindow->SetPositionY(10.0f);
	m_pUIWindow->SetPositionZ(0.5f);
	m_pUIWindow->SetWidth(300.0f);
	m_pUIWindow->SetHeight(300.0f);
	m_pUIWindow->SetColor(1.0f, 1.0f, 1.0f);
	m_pUIWindow->SetAlpha(1.0f);
	//m_pUIWindow->SetImageByFileName(TEXT("A.jpg"));
	m_pUIWindow->SetImageByFileName(TEXT("B.tga"));
	m_pUIWindow->UpdateWindow(0.0f);
}
//-----------------------------------------------------------------------------
void MyApp::ReleaseUIWindowA()
{
	GGUIWindowContainer::GetInstance()->ReleaseUIWindow(m_pUIWindow->GetWindowID());
}
//-----------------------------------------------------------------------------
//  MyApp.cpp
//-----------------------------------------------------------------------------
