//-----------------------------------------------------------------------------
// (C) oil
// 2012-10-19
//-----------------------------------------------------------------------------
#include "GGUIStdAfx.h"
#include "GGUITinyString.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	//-----------------------------------------------------------------------------
	void GGUITinyString::SetValue(const char* pszString)
	{
		SoInt i = 0;
		for (; i<MaxSize_TinyString; ++i)
		{
			if (pszString[i] == 0)
				break;
			else
				m_szBuffer[i] = pszString[i];
		}
		m_szBuffer[i] = 0;
	}
	//-----------------------------------------------------------------------------
	bool operator < (const GGUITinyString& left, const GGUITinyString& right)
	{
		for (SoInt i=0; i<MaxSize_TinyString; ++i)
		{
			if (left.m_szBuffer[i] && right.m_szBuffer[i])
			{
				if (left.m_szBuffer[i] == right.m_szBuffer[i])
				{
					//继续比较；什么也不做。
				}
				else
				{
					return (left.m_szBuffer[i] < right.m_szBuffer[i]);
				}
			}
			else
			{
				//要么left.m_szBuffer[i]为0，要么right.m_szBuffer[i]为0
				if (left.m_szBuffer[i])
				{
					return false;
				}
				if (right.m_szBuffer[i])
				{
					return true;
				}
			}
		}
		return false;
	}
} //namespace GGUI
//-----------------------------------------------------------------------------
