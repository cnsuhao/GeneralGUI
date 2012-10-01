//-----------------------------------------------------------------------------
//  (C) oil
//  CreateDate : 2009-02-21
//  UpdateDate : 2009-02-21
//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include "SoD3DApp.h"
//-----------------------------------------------------------------------------
class MyApp : public SoD3DApp
{
public:
	MyApp(void);
	virtual ~MyApp(void);

	virtual void BeforeCreateWindow(void);
	//创建和初始化D3D程序中所需要的各种对象资源
	virtual bool InitResource(void);
	virtual void ClearResource(void);

	virtual void Update(float fAccTime, float fFrameTime);
	virtual void Draw(void);

protected:
	virtual LRESULT MsgProcess(UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	void CreateUIWindowA();
	void ReleaseUIWindowA();

private:
	GGUIWindow* m_pUIWindow;

};