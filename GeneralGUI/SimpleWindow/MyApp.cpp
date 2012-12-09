//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "MyApp.h"
#include "SoNSD3D.h"
#include "../GeneralGUI/GGUIImagesetManager.h"
//-----------------------------------------------------------------------------
SoD3DApp* SoD3DApp::CreateInstance(void)
{
	return new MyApp;
}
//-----------------------------------------------------------------------------
MyApp::MyApp(void)
:SoD3DApp()
,m_pUIWindow(NULL)
,m_eTransformState(Transform_None)
,m_nTransformWindowID(Invalid_WindowID)
,m_fAccTimeForTransform(0.0f)
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
	GGUIFontManager::GetInstance()->AddFont(0, "simhei.ttf", 0, 24, 1);
	//
	GGUILog* pLog = new GGUILog;
	pLog->InitLog(TEXT("oil.txt"), true, true);
	GGUILog::SetInstance(pLog);
	//
	//CreateUIWindowA();
	CreateWindowList();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	return true;
}

//-----------------------------------------------------------------------------
void MyApp::ClearResource(void)
{
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//ReleaseWindowList();
	ReleaseUIWindowA();
	//释放GGUI系统
	GGUISystem::ReleaseInstance();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
}

//-----------------------------------------------------------------------------
void MyApp::Update(float fAccTime, float fFrameTime)
{
	if (m_eTransformState != Transform_None)
	{
		m_fAccTimeForTransform += fFrameTime;
		if (m_fAccTimeForTransform >= TransformTime)
		{
			if (m_eTransformState == Transform_Large)
			{
				ForceLarge(m_nTransformWindowID);
				m_eTransformState = Transform_WaitForRestore;
			}
			else if (m_eTransformState == Transform_Restore)
			{
				ForceRestore(m_nTransformWindowID);
				m_eTransformState = Transform_None;
			}
			m_nTransformWindowID = Invalid_WindowID;
			m_fAccTimeForTransform = 0.0f;
		}
		else
		{
			float fDestPosLeft = 0.0f;
			float fDestPosRight = 0.0f;
			float fDestPosUp = 0.0f;
			float fDestPosDown = 0.0f;
			float fRemainTime = TransformTime - (m_fAccTimeForTransform-fFrameTime);
			//
			if (m_eTransformState == Transform_Large)
			{
				fDestPosLeft = 0.0f;
				fDestPosRight = (float)m_lClientW;
				fDestPosUp = 0.0f;
				fDestPosDown = (float)m_lClientH;
			}
			else if (m_eTransformState == Transform_Restore)
			{
				int x = m_nTransformWindowID % PictureCountX;
				int y = m_nTransformWindowID / PictureCountY;
				fDestPosLeft = MarginX + x*(MarginX+PictureWindowWidth);
				fDestPosRight = fDestPosLeft + PictureWindowWidth;
				fDestPosUp = MarginY + y*(MarginY+PictureWindowHeight);
				fDestPosDown = fDestPosUp + PictureWindowHeight;
			}
			//
			GGUIWindow* pWindow = GGUIWindowManager::GetInstance()->GetUIWindow(m_nTransformWindowID);
			if (pWindow)
			{
				float fCurrentPosLeft = pWindow->GetPositionX();
				float fCurrentPosRight = fCurrentPosLeft + pWindow->GetWidth();
				float fCurrentPosUp = pWindow->GetPositionY();
				float fCurrentPosDown = fCurrentPosUp + pWindow->GetHeight();
				//求出矩形的四个顶点的移动速度，包含方向。
				//值为正表示Transform_Large，值为负表示Transform_Restore。
				float fSpeedLeft = (fDestPosLeft - fCurrentPosLeft) / fRemainTime;
				float fSpeedRight = (fDestPosRight - fCurrentPosRight) / fRemainTime;
				float fSpeedUp = (fDestPosUp - fCurrentPosUp) / fRemainTime;
				float fSpeedDown = (fDestPosDown - fCurrentPosDown) / fRemainTime;
				//
				float fNewPosLeft = fCurrentPosLeft + fSpeedLeft * fFrameTime;
				float fNewPosRight = fCurrentPosRight + fSpeedRight * fFrameTime;
				float fNewPosUp = fCurrentPosUp + fSpeedUp * fFrameTime;
				float fNewPosDown = fCurrentPosDown + fSpeedDown * fFrameTime;
				//
				pWindow->SetPositionX(fNewPosLeft);
				pWindow->SetPositionY(fNewPosUp);
				pWindow->SetWidth(fNewPosRight - fNewPosLeft);
				pWindow->SetHeight(fNewPosDown - fNewPosUp);
				pWindow->SetPositionZ(0.3f);
			}
		}
	}

	GGUISystem::GetInstance()->UpdateGGUI(fFrameTime);
}

//-----------------------------------------------------------------------------
void MyApp::Draw(void)
{
	GGUISystem::GetInstance()->RenderGGUI();
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
	case WM_LBUTTONDOWN:
		{
			GGUISystem::GetInstance()->InjectMouseEvent(ButtonDown, LeftMouse, 0.0f, 0.0f);
		}
		break;
	case WM_LBUTTONUP:
		{
			GGUISystem::GetInstance()->InjectMouseEvent(ButtonUp, LeftMouse, 0.0f, 0.0f);
		}
		break;
	default:
		break;
	}
	//
	return __super::MsgProcess(uMsg, wParam, lParam);
}

//-----------------------------------------------------------------------------
void MyApp::OnMouseClick(WindowID theWindowID, SoUInt uiParam)
{

}
//-----------------------------------------------------------------------------
void MyApp::OnMouseClickWindowList(WindowID theWindowID, SoUInt uiParam)
{
	if (m_eTransformState == Transform_None)
	{
		m_eTransformState = Transform_Large;
		m_nTransformWindowID = theWindowID;
		m_fAccTimeForTransform = 0.0f;
	}
	else if (m_eTransformState == Transform_Large)
	{
		if (m_nTransformWindowID == theWindowID)
		{
			m_eTransformState = Transform_Restore;
			m_nTransformWindowID = theWindowID;
			m_fAccTimeForTransform = TransformTime - m_fAccTimeForTransform;
		}
		else
		{
			//立即恢复原状
			ForceRestore(m_nTransformWindowID);
			m_eTransformState = Transform_Large;
			m_nTransformWindowID = theWindowID;
			m_fAccTimeForTransform = 0.0f;
		}
	}
	else if (m_eTransformState == Transform_WaitForRestore)
	{
		m_eTransformState = Transform_Restore;
		m_nTransformWindowID = theWindowID;
		m_fAccTimeForTransform = 0.0f;
	}
	else if (m_eTransformState == Transform_Restore)
	{
		if (m_nTransformWindowID == theWindowID)
		{
			m_eTransformState = Transform_Large;
			m_nTransformWindowID = theWindowID;
			m_fAccTimeForTransform = TransformTime - m_fAccTimeForTransform;
		}
		else
		{
			//立即恢复原状
			ForceRestore(m_nTransformWindowID);
			m_eTransformState = Transform_Large;
			m_nTransformWindowID = theWindowID;
			m_fAccTimeForTransform = 0.0f;
		}
	}
}
//-----------------------------------------------------------------------------
void MyApp::CreateUIWindowA()
{
	m_pUIWindow = GGUIWindowManager::GetInstance()->CreateUIWindow(WindowType_Picture);
	m_pUIWindow->SetPositionX(0.0f);
	m_pUIWindow->SetPositionY(0.0f);
	m_pUIWindow->SetPositionZ(0.5f);
	m_pUIWindow->SetWidth(600.0f);
	m_pUIWindow->SetHeight(403.0f);
	m_pUIWindow->SetColor(1.0f, 1.0f, 1.0f);
	m_pUIWindow->SetAlpha(1.0f);

	ImagesetID theImagesetID = Invalid_ImagesetID;
	ImageRectID theImageRectID = Invalid_ImageRectID;
	GGUIImagesetManager::GetInstance()->CreateImagesetByTextureFile(TEXT("A.jpg"), GGUITinyString(TEXT("Ajpg")), &theImagesetID, &theImageRectID);
	m_pUIWindow->SetImagesetID(theImagesetID);
	m_pUIWindow->SetImageRectID(theImageRectID);
	//m_pUIWindow->SetImageByFileName(TEXT("B.tga"));
	m_pUIWindow->UpdateWindow(0.0f);

	RegisterWindowEventB(m_pUIWindow->GetWindowID(), WindowEvent_MouseEnterWindowArea, this, &MyApp::OnMouseClick);
}
//-----------------------------------------------------------------------------
void MyApp::ReleaseUIWindowA()
{
	if (m_pUIWindow)
	{
		GGUIWindowManager::GetInstance()->ReleaseUIWindow(m_pUIWindow->GetWindowID());
	}
}
//-----------------------------------------------------------------------------
void MyApp::CreateWindowList()
{
	tchar szBuff[56] = {0};
	//
	for (int y=0; y<PictureCountY; ++y)
	{
		for (int x=0; x<PictureCountX; ++x)
		{
			GGUIWindow* pWindow = GGUIWindowManager::GetInstance()->CreateUIWindow(WindowType_Picture);
			pWindow->SetPositionX(MarginX + x*(MarginX+PictureWindowWidth));
			pWindow->SetPositionY(MarginY + y*(MarginY+PictureWindowHeight));
			pWindow->SetPositionZ(0.5f);
			pWindow->SetWidth(PictureWindowWidth);
			pWindow->SetHeight(PictureWindowHeight);
			pWindow->SetColor(1.0f, 1.0f, 1.0f);
			pWindow->SetAlpha(1.0f);
			SoPrintf(szBuff, sizeof(szBuff), TEXT("Pic/%d.bmp"), y*PictureCountX+x);
			ImagesetID theImagesetID = Invalid_ImagesetID;
			ImageRectID theImageRectID = Invalid_ImageRectID;
			GGUIImagesetManager::GetInstance()->CreateImagesetByTextureFile(szBuff, GGUITinyString(szBuff), &theImagesetID, &theImageRectID);
			pWindow->SetImagesetID(theImagesetID);
			pWindow->SetImageRectID(theImageRectID);
			RegisterWindowEventB(pWindow->GetWindowID(), WindowEvent_MouseLeftButtonClickDown, this, &MyApp::OnMouseClickWindowList);
			m_theWindowList.push_back(pWindow->GetWindowID());
		}
	}
}
//-----------------------------------------------------------------------------
void MyApp::ReleaseWindowList()
{

}
//-----------------------------------------------------------------------------
void MyApp::ForceRestore(WindowID theWindowID)
{
	GGUIWindow* pWindow = GGUIWindowManager::GetInstance()->GetUIWindow(theWindowID);
	if (pWindow == NULL)
	{
		return;
	}
	//
	int x = theWindowID % PictureCountX;
	int y = theWindowID / PictureCountY;
	pWindow->SetPositionX(MarginX + x*(MarginX+PictureWindowWidth));
	pWindow->SetPositionY(MarginY + y*(MarginY+PictureWindowHeight));
	pWindow->SetPositionZ(0.5f);
	pWindow->SetWidth(PictureWindowWidth);
	pWindow->SetHeight(PictureWindowHeight);
	pWindow->SetColor(1.0f, 1.0f, 1.0f);
	pWindow->SetAlpha(1.0f);
}
//-----------------------------------------------------------------------------
void MyApp::ForceLarge(WindowID theWindowID)
{
	GGUIWindow* pWindow = GGUIWindowManager::GetInstance()->GetUIWindow(theWindowID);
	if (pWindow == NULL)
	{
		return;
	}
	//
	pWindow->SetPositionX(0.0f);
	pWindow->SetPositionY(0.0f);
	pWindow->SetPositionZ(0.3f);
	pWindow->SetWidth((float)m_lClientW);
	pWindow->SetHeight((float)m_lClientH);
	pWindow->SetColor(1.0f, 1.0f, 1.0f);
	pWindow->SetAlpha(1.0f);
}
//-----------------------------------------------------------------------------
//  MyApp.cpp
//-----------------------------------------------------------------------------
