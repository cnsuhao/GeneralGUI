//-----------------------------------------------------------------------------
// (C) oil
// 2012-10-19
//-----------------------------------------------------------------------------
#ifndef _GGUIRect_h_
#define _GGUIRect_h_
//-----------------------------------------------------------------------------
namespace GGUI
{
	//-----------------------------------------------------------------------------
	class GGUIRect
	{
	public:
		GGUIRect()
		:m_fLeft(0.0f), m_fRight(0.0f), m_fTop(0.0f), m_fBottom(0.0f)
		{

		}
		GGUIRect(SoFloat fLeft, SoFloat fRight, SoFloat fTop, SoFloat fBottom)
		:m_fLeft(fLeft), m_fRight(fRight), m_fTop(fTop), m_fBottom(fBottom)
		{

		}

	public:
		SoFloat m_fLeft;
		SoFloat m_fRight;
		SoFloat m_fTop;
		SoFloat m_fBottom;
	};
} //namespace GGUI
//-----------------------------------------------------------------------------
#endif //_GGUIRect_h_
//-----------------------------------------------------------------------------
