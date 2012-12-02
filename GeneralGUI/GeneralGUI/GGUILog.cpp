//-----------------------------------------------------------------------------
// (C) oil
// 2012-12-02
//-----------------------------------------------------------------------------
#include "GGUIStdAfx.h"
#include "GGUILog.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	//-----------------------------------------------------------------------------
	GGUILog::GGUILog()
	:m_fp(NULL)
	,m_bFlushImmediately(false)
	{

	}
	//-----------------------------------------------------------------------------
	GGUILog::~GGUILog()
	{
		CloseDiskFile();
	}
	//-----------------------------------------------------------------------------
	bool GGUILog::InitLog(const tchar* pszDiskFileName, bool bFlushImmediately)
	{
		bool br = true;
		if (pszDiskFileName)
		{
			br = OpenDiskFile(pszDiskFileName);
		}
		m_bFlushImmediately = bFlushImmediately;
		return br;
	}
	//-----------------------------------------------------------------------------
	void GGUILog::OutputDebug(const tchar* pFormat, ...)
	{
		AddLogHead(TEXT("DEBUG"));
		//
		tchar szBuff[2048] = {0};
		va_list marker;
		va_start(marker, pFormat);
		StringCbVPrintf(szBuff, sizeof(szBuff), pFormat, marker);
		va_end(marker);
		if (m_fp)
		{
			size_t theBuffLength = 0;
			StringCbLength(szBuff, sizeof(szBuff), &theBuffLength);
			fwrite(szBuff, theBuffLength, 1, m_fp);
			if (m_bFlushImmediately)
			{
				fflush(m_fp);
			}
		}
#ifdef _DEBUG
		OutputDebugString(szBuff);
#endif
	}
	//-----------------------------------------------------------------------------
	void GGUILog::OutputWaring(const tchar* pFormat, ...)
	{
		AddLogHead(TEXT("WARING"));
		//
		tchar szBuff[2048] = {0};
		va_list marker;
		va_start(marker, pFormat);
		StringCbVPrintf(szBuff, sizeof(szBuff), pFormat, marker);
		va_end(marker);
		if (m_fp)
		{
			size_t theBuffLength = 0;
			StringCbLength(szBuff, sizeof(szBuff), &theBuffLength);
			szBuff[theBuffLength] = TEXT('\n');
			++theBuffLength;
			szBuff[theBuffLength] = 0;
			fwrite(szBuff, theBuffLength, 1, m_fp);
			if (m_bFlushImmediately)
			{
				fflush(m_fp);
			}
		}
#ifdef _DEBUG
		OutputDebugString(szBuff);
#endif
	}
	//-----------------------------------------------------------------------------
	void GGUILog::OutputError(const tchar* pFormat, ...)
	{
		AddLogHead(TEXT("ERROR"));
		//
		tchar szBuff[2048] = {0};
		va_list marker;
		va_start(marker, pFormat);
		StringCbVPrintf(szBuff, sizeof(szBuff), pFormat, marker);
		va_end(marker);
		if (m_fp)
		{
			size_t theBuffLength = 0;
			StringCbLength(szBuff, sizeof(szBuff), &theBuffLength);
			fwrite(szBuff, theBuffLength, 1, m_fp);
			if (m_bFlushImmediately)
			{
				fflush(m_fp);
			}
		}
#ifdef _DEBUG
		OutputDebugString(szBuff);
#endif
	}
	//-----------------------------------------------------------------------------
	void GGUILog::AddLogHead(tchar* pType)
	{
		tchar szBuff[128] = {0};
		SYSTEMTIME stTime;
		GetSystemTime(&stTime);
		StringCbPrintf(szBuff, sizeof(szBuff), 
			TEXT("%2u:%2u:%2u:%3u [%s] "),
			stTime.wHour, stTime.wMinute, stTime.wSecond, stTime.wMilliseconds, pType);
		if (m_fp)
		{
			size_t theBuffLength = 0;
			StringCbLength(szBuff, sizeof(szBuff), &theBuffLength);
			fwrite(szBuff, theBuffLength, 1, m_fp);
		}
#ifdef _DEBUG
		OutputDebugString(szBuff);
#endif
	}
	//-----------------------------------------------------------------------------
	bool GGUILog::OpenDiskFile(const tchar* pszDiskFileName)
	{
		if (_tfopen_s(&m_fp, pszDiskFileName, TEXT("at")) != 0)
		{
			//打开文件失败。
			m_fp = NULL;
			return false;
		}
		//
		tchar szBuff[1024] = {0};
		SYSTEMTIME stTime;
		GetSystemTime(&stTime);
		StringCbPrintf(szBuff, sizeof(szBuff), 
			TEXT("========%4u:%2u:%2u %2u%2u%2u begin========\n"),
			stTime.wYear, stTime.wMonth, stTime.wDay, stTime.wHour, stTime.wMinute, stTime.wSecond);
		size_t theBuffLength = 0;
		StringCbLength(szBuff, sizeof(szBuff), &theBuffLength);
		fwrite(szBuff, theBuffLength, 1, m_fp);
		return true;
	}
	//-----------------------------------------------------------------------------
	void GGUILog::CloseDiskFile()
	{
		if (m_fp)
		{
			tchar szBuff[1024] = {0};
			SYSTEMTIME stTime;
			GetSystemTime(&stTime);
			StringCbPrintf(szBuff, sizeof(szBuff), 
				TEXT("========%4u:%2u:%2u %2u%2u%2u end========\n"),
				stTime.wYear, stTime.wMonth, stTime.wDay, stTime.wHour, stTime.wMinute, stTime.wSecond);
			size_t theBuffLength = 0;
			StringCbLength(szBuff, sizeof(szBuff), &theBuffLength);
			fwrite(szBuff, theBuffLength, 1, m_fp);
			fflush(m_fp);
			fclose(m_fp);
			m_fp = NULL;
		}
	}
}
//-----------------------------------------------------------------------------
