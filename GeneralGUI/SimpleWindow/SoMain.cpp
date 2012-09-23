//-----------------------------------------------------------------------------
//                                  SoMain.cpp
//
//                                                   (C) oil
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "SoD3DApp.h"
#include "SoDefines.h"
#include "SoEngine.h"
//-------------------------------- ȫ�ֱ��� -----------------------------------
//Ӧ�ó������
SoD3DApp* pTheD3DApp = NULL;
HWND      hMainHWND = NULL;
//-----------------------------------------------------------------------------
// ��������Ϣ����
LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//-----------------------------------------------------------------------------

// WinMain�������
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

    //-------------------- �������ں����� -------------------
	pTheD3DApp->BeforeCreateWindow();
	hMainHWND = pTheD3DApp->CreateTheWindow(WinProc);
	if(NULL==hMainHWND)
	{
		SAFE_DELETE(pTheD3DApp);
		return 0;
	}
	//pTheD3DApp->AfterCreateWindow();


	//--------------------- ����D3D������ -----------------
	//pTheD3DApp->BeforeCreateD3D();
	if( !pTheD3DApp->CreateD3D() )
	{
		SAFE_DELETE(pTheD3DApp);
		return 0;
	}
	//pTheD3DApp->AfterCreateD3D();
	
	//------------------- ����SoEngine --------------
	if(NULL==SoEngine::CreateInstance())
	{
		goto _EXIT_APP_1;
	}
	if( !SoEngine::Instance()->InitEngine() )
	{
		goto _EXIT_APP_1;
	}

	//------------------- ������Դ --------------
	if( !pTheD3DApp->InitResource() )
	{
		goto _EXIT_APP_2;
	}


	ShowWindow(hMainHWND,1);
    UpdateWindow( hMainHWND );


    // ������Ϣ����
    MSG msg; 
	memset(&msg, 0, sizeof(msg));
    while( msg.message != WM_QUIT)
    {
		if(pTheD3DApp->IsMinimize())  //������С��״̬
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

//goto��ת��
_EXIT_APP_2:

	//-------------- �����Դ --------------
	pTheD3DApp->ClearResource();

//goto��ת��
_EXIT_APP_1:

	//-------------- ɾ����ʵ�� ------------
	SoEngine::ReleaseInstance();

	//-------------- ����D3D���� -----------
	SAFE_DELETE(pTheD3DApp);

	return (int)msg.wParam;
}//WinMain()����

//-----------------------------------------------------------------------------
// ��������Ϣ����
LRESULT CALLBACK WinProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//pTheD3DApp�϶�����Чָ��
	if( pTheD3DApp->MsgProcess( uMsg,wParam,lParam) )
		return 0;


	//���ٴ�����Ϣ�Ĵ���
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