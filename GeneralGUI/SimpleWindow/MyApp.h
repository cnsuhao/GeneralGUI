//-----------------------------------------------------------------------------
//  (C) oil
//  CreateDate : 2009-02-21
//  UpdateDate : 2009-02-21
//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include "SoD3DApp.h"
#include <vector>
//-----------------------------------------------------------------------------
#define PictureCountX 4
#define PictureCountY 4
#define PictureWindowWidth 160
#define PictureWindowHeight 120
#define MarginX 32
#define MarginY 24
#define TransformTime 0.5f
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
	void OnMouseClick(WindowID theWindowID, SoUInt uiParam);
	void OnMouseClickWindowList(WindowID theWindowID, SoUInt uiParam);

protected:
	void CreateUIWindowA();
	void ReleaseUIWindowA();
	void CreateWindowList();
	void ReleaseWindowList();
	//
	void ForceRestore(WindowID theWindowID);
	void ForceLarge(WindowID theWindowID);


private:
	enum eTransformState
	{
		Transform_None,
		Transform_Large,
		Transform_WaitForRestore,
		Transform_Restore,
	};
private:
	GGUIWindow* m_pUIWindow;
	std::vector<WindowID> m_theWindowList;
	eTransformState m_eTransformState;
	WindowID m_nTransformWindowID;
	float m_fAccTimeForTransform;
};

