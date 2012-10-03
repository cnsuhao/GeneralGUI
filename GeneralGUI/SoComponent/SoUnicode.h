/********************************************************************************
**                       SoUnicode.h  for  VS2005
**
**  1.由VS2005生成的项目都以继承方式,预定义了UNICODE和_UNICODE,
**    见项目属性-> C/C++ ->预编译器. 
**    所有既支持ANSI又支持Unicode的函数都偏向于Unicode版本.
**  2.char仍然占1个字节.
**  3.用TEXT()来包含字符串,就能满足两种版本. TEXT("oil你好")
**
**                                       (C)   oil
**                                    创建日期:08.05.31
**                                    更新日期:09.03.19
********************************************************************************/
#ifndef _SoUnicode_h_
#define _SoUnicode_h_
//-----------------------------------------------------------------------------
#include <tchar.h> //包含C运行期库的同时处理ANSI与Unicode字符集的头文件
#include <iostream> //使用STL中的string
#include <strsafe.h> //包含StringCbPrintfA等函数
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









//  ANSI         UNICODE       两栖
//  strcpy_s     wcscpy_s     _tcscpy_s  //对字符串指针赋值,需要三个参数;为字符数组赋值,需要两个参数
//  sprintf_s    swprintf_s   _stprintf_s  //同上


//下面这两个头文件涉及到ZeroMemory()
//#include <winbase.h>
//#include <winnt.h>


//包含拥有对两种字符集的字符串进行操作的Windows函数的头文件
//建议使用Windows函数,而不要使用C运行期库的函数
//#include <shlwapi.h>

//typedef TCHAR tchar;  //这里,tchar是Unicode版本的两栖函数


//使用Unicode字符集时,字符串的前面要添加L,下面定义一个宏
//则L("oil")就相当于L"oil"
//在tchar.h中有  #define __T(x)      L ## x
//               #define _T(x)       __T(x)
//               #define _TEXT(x)    __T(x)
//#ifdef UNICODE
//#define L(x) L##x
//#define tfopen _wfopen  //文件的打开
//
//
//#else //UNICODE//
//#define L(x) x
//#define tfopen fopen
//
//
//#endif //UNICODE//
/*
尽量使用Windows定义的数据类型,没有T和W的都是ANSI字符
字符        TCHAR
WCHAR
字符串指针  LPTSTR  LPCTSTR
LPWSTR  LPCWSTR
*/




////字符串复制的函数,在CListView::MsgProc()中有使用
//#define wstrcpy wcscpy
////返回字符的个数,包括结束符.
//#define wstrlen wcslen
////把字符串str2接到str1的后面,str1最后面的'\0'被取消
//#define wstrcat wcscat
//#define wstrcmp wcscmp
////字符串转换为数值
//#define StrToLong _wtol
//-------------------------------------
//#define wstrcpy strcpy
//#define wstrlen strlen
//#define wstrcat strcat
//#define wstrcmp strcmp
//#define StrToLong atol
//#define StrToDouble atof



