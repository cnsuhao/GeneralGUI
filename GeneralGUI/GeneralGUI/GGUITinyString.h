//-----------------------------------------------------------------------------
// (C) oil
// 2012-10-19
//-----------------------------------------------------------------------------
#ifndef _GGUITinyString_h_
#define _GGUITinyString_h_
//-----------------------------------------------------------------------------
namespace GGUI
{
	static const SoInt MaxSize_TinyString = 16;
	//-----------------------------------------------------------------------------
	class GGUITinyString
	{
	public:
		GGUITinyString()
		{
			m_szBuffer[0] = 0;
		}
		//-----------------------------------------------------------------------------
		GGUITinyString(const char* pszString)
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
		const char* GetValue() const
		{
			return m_szBuffer;
		}
		//-----------------------------------------------------------------------------
		//注意，pszString字符串的size（包括结束符）不能大于MaxSize_ImagesetName；
		//如果大于的话，会被截断。
		void SetValue(const char* pszString);
		//
		friend bool operator < (const GGUITinyString& left, const GGUITinyString& right);

	protected:
		char m_szBuffer[MaxSize_TinyString];
	};
} //namespace GGUI
//-----------------------------------------------------------------------------
#endif //_GGUITinyString_h_
//-----------------------------------------------------------------------------
