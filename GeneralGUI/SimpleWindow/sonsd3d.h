//-----------------------------------------------------------------------------
//                                 SoNSD3D.h
//
//                                                       (C) oil
//                                                  ��������:2008-10-11
//                                                  ��������:2008-10-11
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

//��߱�����Ϊ2�Ĵη�
//��ʹ��MipLevels
//������ΪRenderTarget
//�������ظ�ʽ��ͼƬ���ظ�ʽ����
//D3DPOOL_MANAGED
//�������Թ���
//͸���ؼ�ɫ��������Ϊ0x88ffffff(ARGB),��ʾ��ɫ��Alphaֵ��0x88;����0,��ʾ��ʹ�ùؼ�ɫ
#define  SoLoadTexture(pD3DTexture,pFileName,dwColorKey)  \
	D3DXCreateTextureFromFileEx(SoD3DApp::GetD3DDevice(),pFileName,0U,0U,D3DX_FROM_FILE,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_FILTER_LINEAR,D3DX_FILTER_NONE,dwColorKey,NULL,NULL,&pD3DTexture)
//-----------------------------------------------------------------------------
namespace SoNSD3D
{

}