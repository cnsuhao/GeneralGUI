//-----------------------------------------------------------------------------
// ����D3D��ͷ�ļ�����һЩ���������¶��塣
//
// 1��DX�汾Ϊ2006 April��
// (C) oil
// 2008-06-07
//-----------------------------------------------------------------------------
#ifndef _SoD3DDefine_h_
#define _SoD3DDefine_h_
//-----------------------------------------------------------------------------
#include <d3d9.h>
#include <d3dx9.h>
#include <D3dx9mesh.h>
//����exe�ļ��Ĺ���Ҫ���DX�Ŀ��ļ�
//#pragma comment(lib,"d3d9.lib")
//#pragma comment(lib,"d3dx9.lib")
//-----------------------------------------------------------------------------
#include "SoBaseTypeDefine.h"
//-----------------------------------------------------------------------------
//  D3D to SoSystem
//-----------------------------------------------------------------------------
namespace SoComponent
{
	typedef D3DXVECTOR2  SoPoint2;
	typedef D3DXVECTOR3  SoPoint3;
	//typedef struct D3DMATRIX  SoMatrix4;
	typedef D3DX_ALIGN16 _D3DXMATRIXA16  SoMatrix4;
	typedef D3DXQUATERNION  SoQuaternion;

	//-----------------------------------------------------------------------------
	//��ȫ���ͷ�Windows COM�ӿڶ���
	#define SAFE_D3D_RELEASE(p)   { if(p) { (p)->Release(); (p)=NULL; } } 
	//-----------------------------------------------------------------------------
	//Color���������;���DWORD SoUInt32
	#define SoMakeColorRGBA_UInt(r,g,b,a) ((SoUInt32)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
	#define SoMakeColorRGBA(r,g,b,a) SoMakeColorRGBA_UInt((SoUInt32)((r)*255.0f),(SoUInt32)((g)*255.0f),(SoUInt32)((b)*255.0f),(SoUInt32)((a)*255.0f))

	//-----------------------------------------------------------------------------
	//�Զ��������������Ľṹ��,����ֵһ��Ϊ16λ
	#pragma pack(push) //�������״̬
	#pragma pack(2) //�趨Ϊ2�ֽڶ���
	struct SoIndexBufferUnit
	{
		SoUInt16 _0;
		SoUInt16 _1;
		SoUInt16 _2;
	};
	#pragma pack(pop) //�ָ�����״̬

} //namespace SoComponent
//-----------------------------------------------------------------------------
#endif //_SoD3DDefine_h_
//-----------------------------------------------------------------------------
