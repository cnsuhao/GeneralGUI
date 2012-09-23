//-----------------------------------------------------------------------------
//                                 SoNSD3D.h
//
//                                                       (C) oil
//                                                  创建日期:2008-10-11
//                                                  更新日期:2008-10-11
//-----------------------------------------------------------------------------
#pragma once

#include "SoEngine.h"
#include "SoD3DApp.h"
//-----------------------------------------------------------------------------
#define  SoCreateIndexBuffer(pD3DDevice, pIB, uiLength)  \
	pD3DDevice->CreateIndexBuffer(uiLength, 0U, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pIB, NULL)
#define  SoCreateIB(pIB, uiLength)  \
	SoD3DApp::GetD3DDevice()->CreateIndexBuffer(uiLength, 0U, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pIB, NULL)

#define  SoCreateVertexBuffer(pD3DDevice, pVB, uiLength, dwFVF)  \
	pD3DDevice->CreateVertexBuffer(uiLength, 0U, dwFVF, D3DPOOL_MANAGED, &pVB, NULL)
#define  SoCreateVB(pVB, uiLength, dwFVF)  \
	SoD3DApp::GetD3DDevice()->CreateVertexBuffer(uiLength, 0U, dwFVF, D3DPOOL_MANAGED, &pVB, NULL)

//宽高被扩充为2的次方
//不使用MipLevels
//不能作为RenderTarget
//纹理像素格式由图片像素格式决定
//D3DPOOL_MANAGED
//二次线性过滤
//透明关键色可以设置为0x88ffffff(ARGB),表示黑色的Alpha值是0x88;传入0,表示不使用关键色
#define  SoLoadTexture(pD3DTexture,pFileName,dwColorKey)  \
	D3DXCreateTextureFromFileEx(SoD3DApp::GetD3DDevice(),pFileName,0U,0U,D3DX_FROM_FILE,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_FILTER_LINEAR,D3DX_FILTER_NONE,dwColorKey,NULL,NULL,&pD3DTexture)
//-----------------------------------------------------------------------------
namespace SoNSD3D
{

}