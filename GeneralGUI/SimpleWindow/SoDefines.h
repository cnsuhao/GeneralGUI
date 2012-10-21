//-----------------------------------------------------------------------------
//              ���ļ�������Ҫʹ�õ������к�Ķ��� SoDefines.h
//
// 1.�����ʱҪע���ʹ�ô�����
// 2.����if���ĺ�,���Բ�����if/else���֮��ֱ��ʹ��
//				if(br)
//				  SAFE_DELETE(ptr);
//����д������.
//��ȷ��д������:
//				 if(br)
//				 {
//				   SAFE_DELETE(ptr);
//				 }
//                                                      (C) oil
//                                                 ��������:2008-08-03
//                                                 ��������:2008-09-14
//-----------------------------------------------------------------------------
#pragma once

//һ��Ҫ��FAILED(hr)���ж��Ƿ�ʧ��
#define HR_OK    S_OK
#define HR_FAIL  E_FAIL

//���ڱ�ʾ������������;
#define _IN
#define _OUT

//��ȷ����������ʹ�õ�SoRefObject����
//ע��,�������ü�����1,���ж����ü����Ƿ�С�ڵ���0
#define SoIncreaseRef(p);  { if(p) { (p)->IncRefCount(); } }
#define SoDecreaseRef(p);  { if(p) { if( 0>= ((p)->DecRefCount()) ) { delete (p); (p)=NULL; } } }


//ָ�����͵�list��,������ָ��ָ��Ķ�����ȷ�������ô���
#define SOREF_pLIST_CLEAR(theList,ListType);					\
		{														\
			if( !theList.empty() )								\
			{													\
				ListType::iterator Itor = theList.begin();		\
				for( ; Itor!=theList.end(); ++Itor)				\
				{												\
					SoDecreaseRef((*Itor)); 					\
				}												\
				theList.clear();								\
			}													\
		}								


////���ͱ��
//#define  SoIsKindOf(_type, _pointer)  ( dynamic_cast<_type>(_point) != NULL )


//���庯��ָ������,���ڻص�����
#define  SOCALLBACK  _cdecl

typedef  void  (SOCALLBACK *TimerFunction)(void);


////-----------------------------------------------------------------------------
////�Զ��嶥���ʽ,D3DFVF_XYZRHW��ʾ�Ѿ��Զ��������任,
////����ҪӦ�ó������Զ��Զ������������,�۲����,ͶӰ����ı任
//const DWORD D3DFVF_01 = (D3DFVF_XYZ|D3DFVF_DIFFUSE);
//const DWORD D3DFVF_02 = (D3DFVF_XYZ|D3DFVF_TEX1);
//const DWORD D3DFVF_03 = (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1);

//-----------------------------------------------------------------------------
////�ռ�ֱ�ߵĶ���
//typedef struct Ray
//{
//	D3DXVECTOR3 _origin;
//	D3DXVECTOR3 _direction;
//	Ray()
//	{
//		_origin.x=0.0f;  _origin.y=0.0f;  _origin.z=0.0f;
//		_direction.x=1.0f;  _direction.y=0.0f;  _direction.z=0.0f;  
//	}
//}oil_RAY,*oil_LPRAY;
//-----------------------------------------------------------------------------
//  SoDefines.h
//-----------------------------------------------------------------------------