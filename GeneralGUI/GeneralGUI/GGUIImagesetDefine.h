//-----------------------------------------------------------------------------
// (C) oil
// 2012-10-19
//-----------------------------------------------------------------------------
#ifndef _GGUIImagesetDefine_h_
#define _GGUIImagesetDefine_h_
//-----------------------------------------------------------------------------
namespace GGUI
{
	typedef SoInt ImagesetID;
	static const ImagesetID Invalid_ImagesetID = -1;

	typedef SoInt ImageRectID;
	static const ImageRectID Invalid_ImageRectID = -1;

	//窗口的绘制参数。
	struct stRenderUnit
	{
		SoFloat fPositionX;
		SoFloat fPositionY;
		SoFloat fPositionZ;
		SoFloat fWidth;
		SoFloat fHeight;
		SoFloat fColorR;
		SoFloat fColorG;
		SoFloat fColorB;
		SoFloat fColorA;
		ImagesetID theImagesetID;
		ImageRectID theImageRectID;
	};

} //namespace GGUI
//-----------------------------------------------------------------------------
#endif //_GGUIImagesetDefine_h_
//-----------------------------------------------------------------------------
