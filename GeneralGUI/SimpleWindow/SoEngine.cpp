//-----------------------------------------------------------------------------
//                             SoEngine.cpp
//
//                                                   (C) oil
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "SoEngine.h"
#include "SoD3DApp.h"
//-----------------------------------------------------------------------------
SoEngine::SoEngine(void)
:m_pD3DDevice(NULL)
,m_pStateBlockCapture(NULL)
{
}
//-----------------------------------------------------------------------------
SoEngine::~SoEngine(void)
{
	SAFE_D3D_RELEASE(m_pStateBlockCapture);
	m_pD3DDevice = NULL;
}
//-----------------------------------------------------------------------------
bool  SoEngine::InitEngine(void)
{
	m_pD3DDevice = SoD3DApp::GetD3DDevice();
	if( NULL==m_pD3DDevice )
		return false;

	HRESULT hr = m_pD3DDevice->CreateStateBlock(D3DSBT_ALL,&m_pStateBlockCapture);
	if(FAILED(hr))
	{
		return false;
	}

	return true;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//  SoEngine.cpp
//-----------------------------------------------------------------------------