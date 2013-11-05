//-----------------------------------------------------------------------------
// (C) oil
// 2012-10-19
//-----------------------------------------------------------------------------
#ifndef _GGUITinyString_h_
#define _GGUITinyString_h_
//-----------------------------------------------------------------------------
namespace GGUI
{
	//GGUITinyString对象中最多有多少个字符（包括结束符）。
	static const SoInt MaxCharCount_TinyString = 16;
	//-----------------------------------------------------------------------------
	class GGUITinyString
	{
	public:
		GGUITinyString()
		{
			m_szBuffer[0] = 0;
		}
		//-----------------------------------------------------------------------------
		GGUITinyString(const tchar* pszString)
		{
			SetValue(pszString);
		}
		//-----------------------------------------------------------------------------
		GGUITinyString(const GGUITinyString& other)
		{
			SetValue(other.GetValue());
		}
		//-----------------------------------------------------------------------------
		~GGUITinyString()
		{
		}
		//-----------------------------------------------------------------------------
		const tchar* GetValue() const
		{
			return m_szBuffer;
		}
		//-----------------------------------------------------------------------------
		//注意，pszString字符串的size（包括结束符）不能大于MaxSize_ImagesetName；
		//如果大于的话，会被截断。
		//如果pszString值为NULL，则m_szBuffer被置为空字符串""。
		void SetValue(const tchar* pszString);
		//-----------------------------------------------------------------------------
		void operator = (const GGUITinyString& other)
		{
			SetValue(other.GetValue());
		}
		//-----------------------------------------------------------------------------
		friend bool operator < (const GGUITinyString& left, const GGUITinyString& right);

	protected:
		tchar m_szBuffer[MaxCharCount_TinyString];
	};
} //namespace GGUI
//-----------------------------------------------------------------------------
#endif //_GGUITinyString_h_
//-----------------------------------------------------------------------------
