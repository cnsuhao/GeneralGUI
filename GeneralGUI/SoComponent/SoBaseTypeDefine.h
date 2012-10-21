//-----------------------------------------------------------------------------
// �Ա����Ļ������������¶��塣
// (C) oil
// 2012-09-08
//-----------------------------------------------------------------------------
#ifndef _SoBaseTypeDefine_h_
#define _SoBaseTypeDefine_h_
//-----------------------------------------------------------------------------
namespace SoComponent
{
	typedef __int8  SoInt8;
	typedef __int16 SoInt16;
	typedef __int32 SoInt32;
	typedef __int64 SoInt64;
	typedef __int32 SoInt;
	//
	typedef unsigned __int8  SoUInt8;
	typedef unsigned __int16 SoUInt16;
	typedef unsigned __int32 SoUInt32;
	typedef unsigned __int64 SoUInt64;
	typedef unsigned __int32 SoUInt;
	//
	typedef float SoFloat; //32λ�ĸ���������ȷ��6λ��Ч���֡�
	typedef double SoDouble; //64λ�ĸ���������ȷ��16λ��Ч���֡�
	//
	//�ĸ��ֽڵ�bool���͡������ֽڶ��롣
	//SoBool������ȡֵ��SoTrue��SoFalse��SoNone��
	//SoNone��ʾ��δ��ֵ����δ�����жϣ�û����Чֵ��
	//���һ��SoBool���͵ı���ֻ��SoTrue��SoFalse����״̬�������ʹ��if(SoBool����)������֧�жϣ�
	//���һ��SoBool���͵ı���������״̬�Ļ��������ʹ��if(SoBool����==SoTrue)������֧�жϡ�
	typedef __int32 SoBool;
	#define SoTrue 1
	#define SoFalse 0
	#define SoNone -1

	//-----------------------------------------------------------------------------
	//��ȫ��ɾ��һ������
	#define SAFE_DELETE(p);  { if(p) { delete (p); (p)=NULL; } }
	//��ȫ��ɾ��һ���������顣
	#define SAFE_DELETE_ARRAY(p);  { if(p) { delete [] (p); (p)=NULL; } }

} //namespace SoComponent
//-----------------------------------------------------------------------------
#endif //_SoBaseTypeDefine_h_
//-----------------------------------------------------------------------------
