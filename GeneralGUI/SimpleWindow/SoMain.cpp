//-----------------------------------------------------------------------------
// SoMain.cpp
// (C) oil
// 2012-09-30
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "SoD3DApp.h"
#include "SoDefines.h"
#include "SoEngine.h"
//-----------------------------------------------------------------------------
//Ӧ�ó������
SoD3DApp* g_pTheD3DApp = NULL;
HWND g_hMainHWND = NULL;
//-----------------------------------------------------------------------------
//��������Ϣ����
LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//-----------------------------------------------------------------------------
//WinMain�������
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	g_pTheD3DApp = SoD3DApp::CreateInstance();
	if (NULL == g_pTheD3DApp)
		return 0;

	if (!g_pTheD3DApp->Initialize(hInstance))
	{
		SAFE_DELETE(g_pTheD3DApp);
		return 0;
	}

    //-------------------- �������ں����� -------------------
	g_pTheD3DApp->BeforeCreateWindow();
	g_hMainHWND = g_pTheD3DApp->CreateTheWindow(WinProc);
	if (NULL == g_hMainHWND)
	{
		SAFE_DELETE(g_pTheD3DApp);
		return 0;
	}
	//g_pTheD3DApp->AfterCreateWindow();


	//--------------------- ����D3D������ -----------------
	//g_pTheD3DApp->BeforeCreateD3D();
	if (!g_pTheD3DApp->CreateD3D())
	{
		SAFE_DELETE(g_pTheD3DApp);
		return 0;
	}
	//g_pTheD3DApp->AfterCreateD3D();
	
	//------------------- ����SoEngine --------------
	if (NULL==SoEngine::CreateInstance())
	{
		goto _EXIT_APP_1;
	}
	if (!SoEngine::Instance()->InitEngine())
	{
		goto _EXIT_APP_1;
	}

	//------------------- ������Դ --------------
	if (!g_pTheD3DApp->InitResource())
	{
		goto _EXIT_APP_2;
	}

	//ShowWindow(g_hMainHWND,1);
    //UpdateWindow( g_hMainHWND );


    // ������Ϣ����
    MSG msg;
	memset(&msg, 0, sizeof(msg));
    while( msg.message != WM_QUIT)
    {
		if(g_pTheD3DApp->IsMinimize())  //������С��״̬
		{
			if( GetMessage( &msg, NULL, 0U, 0U ) )
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		}
		else
		{
			if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
			else
			{
				//g_pTheD3DApp->BeforeUpdate();
				g_pTheD3DApp->Update();

				g_pTheD3DApp->PreRender();
				g_pTheD3DApp->Render();
				g_pTheD3DApp->AfterRender();
			}
			//if( g_pTheD3DApp->GetActive() )
			//{
			//}
		}



	}  

//goto��ת��
_EXIT_APP_2:

	//-------------- �����Դ --------------
	g_pTheD3DApp->ClearResource();

//goto��ת��
_EXIT_APP_1:

	//-------------- ɾ����ʵ�� ------------
	SoEngine::ReleaseInstance();

	//-------------- ����D3D���� -----------
	SAFE_DELETE(g_pTheD3DApp);

	return (int)msg.wParam;
}//WinMain()����

//-----------------------------------------------------------------------------
// ��������Ϣ����
LRESULT CALLBACK WinProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if( g_pTheD3DApp->MsgProcess( uMsg,wParam,lParam) )
		return 0;

	if( uMsg == WM_CLOSE )
	{
		DestroyWindow( g_hMainHWND );
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}


	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//-----------------------------------------------------------------------------
//  SoMain.cpp
//-----------------------------------------------------------------------------
/*
	else if(uMsg==WM_KEYDOWN)
	{
		if(KEYDOWN(VK_SPACE))  
		{

			return 0;
		}
	}

	if(uMsg==WM_MOUSEWHEEL)
	{
		return 0;
	}
*/