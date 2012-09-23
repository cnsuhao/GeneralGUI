//-----------------------------------------------------------------------------
//                                  SoMain.cpp
//
//                                                   (C) oil
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "SoD3DApp.h"
#include "SoDefines.h"
#include "SoEngine.h"
//-------------------------------- 全局变量 -----------------------------------
//应用程序对象
SoD3DApp* pTheD3DApp = NULL;
HWND      hMainHWND = NULL;
//-----------------------------------------------------------------------------
// 主窗口消息处理
LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//-----------------------------------------------------------------------------

// WinMain程序入口
int WINAPI WinMain(	HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	pTheD3DApp = SoD3DApp::CreateInstance();
	if(NULL==pTheD3DApp)
		return 0;

	if( !pTheD3DApp->Initialize(hInstance) )
	{
		SAFE_DELETE(pTheD3DApp);
		return 0;
	}

    //-------------------- 创建窗口函数组 -------------------
	pTheD3DApp->BeforeCreateWindow();
	hMainHWND = pTheD3DApp->CreateTheWindow(WinProc);
	if(NULL==hMainHWND)
	{
		SAFE_DELETE(pTheD3DApp);
		return 0;
	}
	//pTheD3DApp->AfterCreateWindow();


	//--------------------- 创建D3D函数组 -----------------
	//pTheD3DApp->BeforeCreateD3D();
	if( !pTheD3DApp->CreateD3D() )
	{
		SAFE_DELETE(pTheD3DApp);
		return 0;
	}
	//pTheD3DApp->AfterCreateD3D();
	
	//------------------- 创建SoEngine --------------
	if(NULL==SoEngine::CreateInstance())
	{
		goto _EXIT_APP_1;
	}
	if( !SoEngine::Instance()->InitEngine() )
	{
		goto _EXIT_APP_1;
	}

	//------------------- 加载资源 --------------
	if( !pTheD3DApp->InitResource() )
	{
		goto _EXIT_APP_2;
	}


	ShowWindow(hMainHWND,1);
    UpdateWindow( hMainHWND );


    // 运行消息机制
    MSG msg; 
	memset(&msg, 0, sizeof(msg));
    while( msg.message != WM_QUIT)
    {
		if(pTheD3DApp->IsMinimize())  //处于最小化状态
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
				//pTheD3DApp->BeforeUpdate();
				pTheD3DApp->Update();

				pTheD3DApp->PreRender();
				pTheD3DApp->Render();
				pTheD3DApp->AfterRender();
			}
			//if( pTheD3DApp->GetActive() )
			//{
			//}
		}



	}  

//goto跳转点
_EXIT_APP_2:

	//-------------- 清除资源 --------------
	pTheD3DApp->ClearResource();

//goto跳转点
_EXIT_APP_1:

	//-------------- 删除单实例 ------------
	SoEngine::ReleaseInstance();

	//-------------- 结束D3D环境 -----------
	SAFE_DELETE(pTheD3DApp);

	return (int)msg.wParam;
}//WinMain()结束

//-----------------------------------------------------------------------------
// 主窗口消息处理
LRESULT CALLBACK WinProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//pTheD3DApp肯定是有效指针
	if( pTheD3DApp->MsgProcess( uMsg,wParam,lParam) )
		return 0;


	//销毁窗口消息的处理
	if( uMsg == WM_CLOSE )
	{
		DestroyWindow( hMainHWND );
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