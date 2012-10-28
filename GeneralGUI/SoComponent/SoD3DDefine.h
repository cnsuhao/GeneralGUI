//-----------------------------------------------------------------------------
// 包含D3D的头文件，对一些类型做重新定义。
//
// 1，DX版本为2006 April。
// (C) oil
// 2008-06-07
//-----------------------------------------------------------------------------
#ifndef _SoD3DDefine_h_
#define _SoD3DDefine_h_
//-----------------------------------------------------------------------------
#include <d3d9.h>
#include <d3dx9.h>
#include <D3dx9mesh.h>
//生成exe文件的工程要添加DX的库文件
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
	//安全的释放Windows COM接口对象
	#define SAFE_D3D_RELEASE(p)   { if(p) { (p)->Release(); (p)=NULL; } } 
	//-----------------------------------------------------------------------------
	//Color的最终类型就是DWORD SoUInt32
	#define SoMakeColorRGBA_UInt(r,g,b,a) ((SoUInt32)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
	#define SoMakeColorRGBA(r,g,b,a) SoMakeColorRGBA_UInt((SoUInt32)((r)*255.0f),(SoUInt32)((g)*255.0f),(SoUInt32)((b)*255.0f),(SoUInt32)((a)*255.0f))

	//-----------------------------------------------------------------------------
	//自定义索引缓冲区的结构体,索引值一般为16位
	#pragma pack(push) //保存对齐状态
	#pragma pack(2) //设定为2字节对齐
	struct SoIndexBufferUnit
	{
		SoUInt16 _0;
		SoUInt16 _1;
		SoUInt16 _2;
	};
	#pragma pack(pop) //恢复对齐状态

} //namespace SoComponent
//-----------------------------------------------------------------------------
#endif //_SoD3DDefine_h_
//-----------------------------------------------------------------------------
