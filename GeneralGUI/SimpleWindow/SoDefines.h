//-----------------------------------------------------------------------------
//              本文件包含了要使用到的所有宏的定义 SoDefines.h
//
// 1.定义宏时要注意多使用大括号
// 2.带有if语句的宏,绝对不能在if/else语句之后直接使用
//				if(br)
//				  SAFE_DELETE(ptr);
//上面写法错误.
//正确的写法如下:
//				 if(br)
//				 {
//				   SAFE_DELETE(ptr);
//				 }
//                                                      (C) oil
//                                                 创建日期:2008-08-03
//                                                 更新日期:2008-09-14
//-----------------------------------------------------------------------------
#pragma once

//一定要用FAILED(hr)来判断是否失败
#define HR_OK    S_OK
#define HR_FAIL  E_FAIL

//用于标示函数参数的用途
#define _IN
#define _OUT

//正确的析构不再使用的SoRefObject对象
//注意,是先引用计数减1,再判断引用计数是否小于等于0
#define SoIncreaseRef(p);  { if(p) { (p)->IncRefCount(); } }
#define SoDecreaseRef(p);  { if(p) { if( 0>= ((p)->DecRefCount()) ) { delete (p); (p)=NULL; } } }


//指针类型的list中,对所有指针指向的对象正确减少引用次数
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


////类型辨别
//#define  SoIsKindOf(_type, _pointer)  ( dynamic_cast<_type>(_point) != NULL )


//定义函数指针类型,用于回调函数
#define  SOCALLBACK  _cdecl

typedef  void  (SOCALLBACK *TimerFunction)(void);


////-----------------------------------------------------------------------------
////自定义顶点格式,D3DFVF_XYZRHW表示已经对顶点做过变换,
////不需要应用程序再自动对顶点作世界矩阵,观察矩阵,投影矩阵的变换
//const DWORD D3DFVF_01 = (D3DFVF_XYZ|D3DFVF_DIFFUSE);
//const DWORD D3DFVF_02 = (D3DFVF_XYZ|D3DFVF_TEX1);
//const DWORD D3DFVF_03 = (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1);

//-----------------------------------------------------------------------------
////空间直线的定义
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