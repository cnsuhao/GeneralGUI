//-----------------------------------------------------------------------------
//                             SoEngine.h
//
//                                                   (C) oil
//                                              ��������:2008-10-12
//                                              ��������:2008-10-12
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
	
	//Capture()��ʧ����? �Ƿ�Ӧ�����÷�������Ϊbool??
	void  BeginStateBlockCapture(void);
	void  EndStateBlockCapture(void);

	IDirect3DDevice9*  GetD3DDevice(void);
};
//-----------------------------------------------------------------------------
//                               ���������Ķ���
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