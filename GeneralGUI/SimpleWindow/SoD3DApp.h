//-----------------------------------------------------------------------------
//                       D3D应用程序类  SoD3DApp.h
//
//1.既有原来CApplication类的内容,又有D3D的创建与销毁.
//
//2.窗口名,即窗口类名,在CreateWin()内部.
//4.WS_THICKFRAME控制能否改变改变窗口大小, 并一定要用m_bSizeAble来标记
//  默认为不能改变窗口大小
//5.图标,光标都在Init()函数中定义
//6.菜单栏和状态栏有单独的类,这里有其作为成员变量
//7.10-19,增加了SoFontManager
//                                                           (C)  oil
//                                                       开始日期:2008.06.10
//                                                       更新日期:2008.10.19
//-----------------------------------------------------------------------------
#pragma once
// this will assume smaller exe  
//拒绝接受MFC的东西,这将加速你的build时间
#define WIN32_LEAN_AND_MEAN 

#include <windows.h>


//-----------------------------------------------------------------------------
class SoD3DApp
{
private:

	HINSTANCE m_hInstance;  //进程句柄

protected:

    HWND      m_hMainHWND;  //窗口句柄
    long      m_lClientW;  //客户区的宽高
	long      m_lClientH;
    bool      m_bActive;   //窗口的激活状态
	bool      m_bSizeAble;  //是否可以调整窗口大小
	bool      m_bIsMinimize; //是否处于最小化状态
	tstring   m_strWinName;  //窗口的标题,同时也是窗口类的名字
	//WinAPI与D3DAPI使用的颜色值类型都是DWORD,
	//WinAPI由RGB()宏得到,D3DAPI由D3DCOLOR_ARGB()或者D3DCOLOR_XRGB()
	DWORD     m_dwBgColor;  


	LPDIRECT3D9         m_pD3D;           //D3D对象
	IDirect3DDevice9*   m_pDevice;        //D3D设备

	static SoD3DApp*  ms_pD3DApp;
	//ms_ppDevice存储了m_pDevice的地址,*ms_ppDevice等于m_pDevice
	//这样,不管m_pDevice发生了什么变化,*ms_ppDevice都反映了m_pDevice的值
	static IDirect3DDevice9**  ms_ppDevice;


private:   //不允许被继承的函数

	//只能在CreateWin()中使用的调整窗口大小的函数
	//判断是否拥有菜单栏和状态栏
	//将来可能还会判断是否拥有滚动条
	void AdjustTheWindow(bool IsMenu, bool IsStatusBar);

public:

	SoD3DApp(void);
	virtual ~SoD3DApp(void);


	//派生类必须实现这个函数
	static SoD3DApp* CreateInstance(void);
	//这个静态函数提供本类对象的指针
	static SoD3DApp* GetD3DApp(void);
	//这个静态函数提供设备指针
	static IDirect3DDevice9* GetD3DDevice(void);


	//初始化
	virtual bool Initialize( HINSTANCE hInstance );
	//Release
	virtual void Release(void);





	//创建窗口之前的设定
	//在这里可以为成员变量赋值
	//菜单栏和状态栏的信息也应该在这里传递
	//bSizeAble--窗口风格,只允许修改是否可以调整窗口大小
	virtual void BeforeCreateWindow(void);
	//初始化并创造窗口
	HWND CreateTheWindow( WNDPROC WinProc );
	////创建窗口之后的操作
	//virtual void AfterCreateWindow(void);


	//virtual void BeforeCreateD3D(void);
	virtual bool CreateD3D(void);
	//virtual void AfterCreateD3D(void);


	//创建和初始化D3D程序中所需要的各种对象资源
	virtual bool InitResource(void)  { return true; };
	virtual void ClearResource(void) { };

	//--------------------------------------------------------------更新

	virtual void BeforeUpdate(void)  { };
	virtual void Update(void)  { };


	//--------------------------------------------------------------渲染

	//主要是调用SetRenderTarget()
	virtual void PreRender(void)  { };

	virtual void Render(void);

	virtual void AfterRender(void)  { };

	//在BeginScene()与EndScene()函数对之间使用
	virtual void Draw(void);



    //处理主窗口消息(消息循环机制)
	//处理了消息则返回TRUE, 没有处理消息则返回FALSE
    virtual bool MsgProcess( UINT uMsg, WPARAM wParam, LPARAM lParam );




	//---------------------------------------------------------------访问操作函数

	//将窗口客户区的左上角和右下角在屏幕中的坐标值填充RECT结构体
	//只能在窗口被创建后使用
	void Get_ClientRect(RECT* pRect);
	HINSTANCE  GetAppInstance(void);
	HWND GetMainHWND(void);
    bool IsActive(void);
	bool IsMinimize(void);
    long GetClientWidth(void);
	long GetClientHeight(void);


	////在SoAllocateHierarchy::GenerateSkinnedMesh()中有使用
	//static DWORD GetMaxVertexBlendMatrixIndex();


};
//-----------------------------------------------------------------------------
//  内联函数的定义
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
