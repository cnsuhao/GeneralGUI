//--------------------------------------------------------------------
//  SoStringHelp.cpp
//  (C) oil
//  2012-04-29
//--------------------------------------------------------------------
#include <Windows.h>
#include "SoStringHelp.h"
//--------------------------------------------------------------------
namespace SoComponent
{
	//--------------------------------------------------------------------
	int UnicodeCountFromAnsi(const char* pString)
	{
		return ::MultiByteToWideChar(CP_ACP, 0, pString, -1, NULL, 0);
	}
	//--------------------------------------------------------------------
	int AnsiCountFromUnicode(const wchar_t* pString)
	{
		return ::WideCharToMultiByte(CP_ACP, 0, pString, -1, NULL, 0, NULL, NULL);
	}
	//--------------------------------------------------------------------
	int UnicodeCountFromUtf8(const char* pString)
	{
		return ::MultiByteToWideChar(CP_UTF8, 0, pString, -1, NULL, 0);
	}
	//--------------------------------------------------------------------
	int Utf8CountFromUnicode(const wchar_t* pString)
	{
		return ::WideCharToMultiByte(CP_UTF8, 0, pString, -1, NULL, 0, NULL, NULL);
	}
	//--------------------------------------------------------------------
	wchar_t* AnsiToUnicode(const char* pSrcString) 
	{
		int nWCharCount = UnicodeCountFromAnsi(pSrcString);
		if (nWCharCount == 0)
		{
			//���ִ���
			return NULL;
		}

		wchar_t* pResult = NULL;
		pResult = new wchar_t[nWCharCount];
		if (pResult)
		{
			if (::MultiByteToWideChar(CP_ACP, 0, pSrcString, -1, pResult, nWCharCount) == 0)
			{
				delete[] pResult;
				pResult = NULL;
			}
		}

		return pResult;
	}
	//--------------------------------------------------------------------
	char* UnicodeToAnsi(const wchar_t* pSrcString)
	{
		int nByteCount = AnsiCountFromUnicode(pSrcString);
		if (nByteCount == 0)
		{
			//���ִ���
			return NULL;
		}

		char* pResult = NULL;
		pResult = new char[nByteCount];
		if (pResult)
		{
			if (::WideCharToMultiByte(CP_ACP, 0, pSrcString, -1, pResult, nByteCount, NULL, NULL) == 0)
			{
				delete[] pResult;
				pResult = NULL;
			}
		}

		return pResult;
	}
	//--------------------------------------------------------------------
	wchar_t* Utf8ToUnicode(const char* pSrcString)
	{
		int nWCharCount = UnicodeCountFromUtf8(pSrcString);
		if (nWCharCount == 0)
		{
			//���ִ���
			return NULL;
		}

		wchar_t* pResult = NULL;
		pResult = new wchar_t[nWCharCount];
		if (pResult)
		{
			if (::MultiByteToWideChar(CP_UTF8, 0, pSrcString, -1, pResult, nWCharCount) == 0)
			{
				delete[] pResult;
				pResult = NULL;
			}
		}

		return pResult;
	}
	//--------------------------------------------------------------------
	char* UnicodeToUtf8(const wchar_t* pSrcString)
	{
		int nByteCount = Utf8CountFromUnicode(pSrcString);
		if (nByteCount == 0)
		{
			//���ִ���
			return NULL;
		}

		char* pResult = NULL;
		pResult = new char[nByteCount];
		if (pResult)
		{
			if (::WideCharToMultiByte(CP_UTF8, 0, pSrcString, -1, pResult, nByteCount, NULL, NULL) == 0)
			{
				delete[] pResult;
				pResult = NULL;
			}
		}

		return pResult;
	}
	//--------------------------------------------------------------------
	char* AnsiToUtf8(const char* pSrcString)
	{
		char* pUtf8String = NULL;
		//���Ȱ�Ansi�ַ���ת����Unicode��ʽ��
		wchar_t* pUnicodeString = AnsiToUnicode(pSrcString);
		if (pUnicodeString)
		{
			//�ٰ�Unicode�ַ���ת����Utf8��ʽ��
			pUtf8String = UnicodeToUtf8(pUnicodeString);
			delete[] pUnicodeString;
		}
		return pUtf8String;
	}
	//--------------------------------------------------------------------
	char* Utf8ToAnsi(const char* pSrcString)
	{
		char* pAnsiString = NULL;
		//���Ȱ�Utf8�ַ���ת����Unicode��ʽ��
		wchar_t* pUnicodeString = Utf8ToUnicode(pSrcString);
		if (pUnicodeString)
		{
			//�ٰ�Unicode�ַ���ת����Ansi��ʽ��
			pAnsiString = UnicodeToAnsi(pUnicodeString);
			delete[] pUnicodeString;
		}
		return pAnsiString;
	}
}
//--------------------------------------------------------------------
