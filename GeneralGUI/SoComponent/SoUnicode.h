/********************************************************************************
**                       SoUnicode.h  for  VS2005
**
**  1.��VS2005���ɵ���Ŀ���Լ̳з�ʽ,Ԥ������UNICODE��_UNICODE,
**    ����Ŀ����-> C/C++ ->Ԥ������. 
**    ���м�֧��ANSI��֧��Unicode�ĺ�����ƫ����Unicode�汾.
**  2.char��Ȼռ1���ֽ�.
**  3.��TEXT()�������ַ���,�����������ְ汾. TEXT("oil���")
**
**                                       (C)   oil
**                                    ��������:08.05.31
**                                    ��������:09.03.19
********************************************************************************/
#ifndef _SoUnicode_h_
#define _SoUnicode_h_
//-----------------------------------------------------------------------------
#include <tchar.h> //����C�����ڿ��ͬʱ����ANSI��Unicode�ַ�����ͷ�ļ�
#include <iostream> //ʹ��STL�е�string
#include <strsafe.h> //����StringCbPrintfA�Ⱥ���
//-----------------------------------------------------------------------------
namespace SoComponent
{

#if defined(_UNICODE) || defined(UNICODE)
	typedef  wchar_t  tchar;
	typedef  std::wstring  tstring;
#else
	typedef  char  tchar;
	typedef  std::string  tstring;
#endif

#if defined(_UNICODE) || defined(UNICODE)
	#define tstrlen wcslen
	#define SoPrintf StringCbPrintfW
#else
	#define tstrlen strlen
	#define SoPrintf StringCbPrintfA
#endif

} //namespace SoComponent
//-----------------------------------------------------------------------------
#endif //_SoUnicode_h_
//-----------------------------------------------------------------------------









//  ANSI         UNICODE       ����
//  strcpy_s     wcscpy_s     _tcscpy_s  //���ַ���ָ�븳ֵ,��Ҫ��������;Ϊ�ַ����鸳ֵ,��Ҫ��������
//  sprintf_s    swprintf_s   _stprintf_s  //ͬ��


//����������ͷ�ļ��漰��ZeroMemory()
//#include <winbase.h>
//#include <winnt.h>


//����ӵ�ж������ַ������ַ������в�����Windows������ͷ�ļ�
//����ʹ��Windows����,����Ҫʹ��C�����ڿ�ĺ���
//#include <shlwapi.h>

//typedef TCHAR tchar;  //����,tchar��Unicode�汾�����ܺ���


//ʹ��Unicode�ַ���ʱ,�ַ�����ǰ��Ҫ���L,���涨��һ����
//��L("oil")���൱��L"oil"
//��tchar.h����  #define __T(x)      L ## x
//               #define _T(x)       __T(x)
//               #define _TEXT(x)    __T(x)
//#ifdef UNICODE
//#define L(x) L##x
//#define tfopen _wfopen  //�ļ��Ĵ�
//
//
//#else //UNICODE//
//#define L(x) x
//#define tfopen fopen
//
//
//#endif //UNICODE//
/*
����ʹ��Windows�������������,û��T��W�Ķ���ANSI�ַ�
�ַ�        TCHAR
WCHAR
�ַ���ָ��  LPTSTR  LPCTSTR
LPWSTR  LPCWSTR
*/




////�ַ������Ƶĺ���,��CListView::MsgProc()����ʹ��
//#define wstrcpy wcscpy
////�����ַ��ĸ���,����������.
//#define wstrlen wcslen
////���ַ���str2�ӵ�str1�ĺ���,str1������'\0'��ȡ��
//#define wstrcat wcscat
//#define wstrcmp wcscmp
////�ַ���ת��Ϊ��ֵ
//#define StrToLong _wtol
//-------------------------------------
//#define wstrcpy strcpy
//#define wstrlen strlen
//#define wstrcat strcat
//#define wstrcmp strcmp
//#define StrToLong atol
//#define StrToDouble atof



