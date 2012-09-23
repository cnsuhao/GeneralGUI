//-----------------------------------------------------------------------------
//                             SoEngine.h
//
//                                                   (C) oil
//                                              创建日期:2008-10-12
//                                              更新日期:2008-10-12
//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include "SoDefines.h"
//-----------------------------------------------------------------------------
class SoEngine : public SoTSingleton<SoEngine>
{
private:
	IDirect3DDevice9*  m_pD3DDevice;
	IDirect3DStateBlock9*  m_pStateBlockCapture;

public:
	SoEngine(void);
	~SoEngine(void);

	bool  InitEngine(void);
	
	//Capture()会失败吗? 是否应该设置返回类型为bool??
	void  BeginStateBlockCapture(void);
	void  EndStateBlockCapture(void);

	IDirect3DDevice9*  GetD3DDevice(void);
};
//-----------------------------------------------------------------------------
//                               内联函数的定义
//-----------------------------------------------------------------------------
inline void  SoEngine::BeginStateBlockCapture(void)
{
	m_pStateBlockCapture->Capture();
}
//-----------------------------------------------------------------------------
inline void  SoEngine::EndStateBlockCapture(void)
{
	m_pStateBlockCapture->Apply();
}
//-----------------------------------------------------------------------------
inline IDirect3DDevice9*  SoEngine::GetD3DDevice(void)
{
	return m_pD3DDevice;
}
//-----------------------------------------------------------------------------
//  SoEngine.h
//-----------------------------------------------------------------------------