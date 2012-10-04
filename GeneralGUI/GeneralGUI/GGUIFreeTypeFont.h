//-----------------------------------------------------------------------------
// GGUI的FreeType字体
// (C) oil
// 2012-10-04
//-----------------------------------------------------------------------------
#ifndef _GGUIFreeTypeFont_h_
#define _GGUIFreeTypeFont_h_
//--------------------------------------------------------------------
#include <map>
#include <vector>
#include <ft2build.h>
#include FT_FREETYPE_H
//-----------------------------------------------------------------------------
namespace GGUI
{
	//--------------------------------------------------------------------
	//如果一个字符的CharGlyphID为N，则表示这个字符的像素数据处于贴图的第N个Rect。
	//如果第一张贴图的CharGlyphID包括了[0,M]，则第二张贴图的起始CharGlyphID为(M+1)。
	typedef SoInt CharGlyphID;
	static const CharGlyphID Invalid_CharGlyphID = -1;
	//--------------------------------------------------------------------
	//存储一个字符的图像纹理信息
	struct stCharGlyphData
	{
		CharGlyphID theCharGlyphID;
		//存储本字符的字符编码。
		wchar_t Character;
		//本字符在文本排版中的步进宽度。
		short AdvanceX;
		//本字符在文本排版中的步进高度。
		short AdvanceY;
		//字符的步进宽度和步进高度构成了外围Rect，像素数据Bitmap构成了内围Rect，
		//外围Rect和内围Rect之间的空隙就是左边距，右边距，上边距，下边距。
		//这里只需要记录左边距和上边距即可。
		short LeftMargin;
		short TopMargin;
		//本字符像素数据的宽度。
		short BitmapWidth;
		//本字符像素数据的高度。
		short BitmapHeight;

		stCharGlyphData()
			:theCharGlyphID(Invalid_CharGlyphID), Character(0), AdvanceX(0), AdvanceY(0)
			,LeftMargin(0), TopMargin(0), BitmapWidth(0), BitmapHeight(0)
		{
		}
	};
	//--------------------------------------------------------------------
	class GGUIFreeTypeFont
	{
	public:
		GGUIFreeTypeFont();
		~GGUIFreeTypeFont();

		//载入并打开字体文件，并没有把字体文件中的字符解析加载到内存中。
		//--pFontFileName 字体文件完整路径。必须是ASCII字符。
		//--nFontFaceIndex 使用字体的哪个字形，一般取默认值即可，默认值为0。
		//--nFontSizeWidth 字号宽度。
		//--nFontSizeHeight 字号高度。
		//--nEdge 值为0表示不描边；大于0，表示描几个像素的边缘。
		//返回是否执行成功。如果返回false，则本对象不能使用，外界应该删除掉。
		bool InitFont(const char* pFontFileName, SoInt nFontFaceIndex, SoInt nFontSizeWidth, SoInt nFontSizeHeight, SoInt16 nEdge);
		//当你把一个字符串绘制到指定的贴图上时，在调用DrawCharacter()之前，
		//你必须调用本函数设置必要的参数信息。
		//--pDestTexture 目标纹理贴图。目标纹理必须是D3DFMT_A8R8G8B8格式。
		//--bEdge 是否描边。
		//颜色，取值范围[0.0f, 1.0f]。
		void SetDrawParam(IDirect3DTexture9* pDestTexture, SoFloat fCharColorR, SoFloat fCharColorG, SoFloat fCharColorB,
			bool bEdge, SoFloat fEdgeColorR, SoFloat fEdgeColorG, SoFloat fEdgeColorB);
		//把一个字符串的字符图像绘制到指定贴图的指定位置上。
		//字符串中可以有空格字符和Tab字符，步进长度分别是m_nSpaceAdvance和m_nTabAdvance。
		//字符串中回车字符不会被解析，不支持回车字符的语义。
		//--pString 字符串指针。
		//--nValidCharCount 有几个有效字符。
		//--nStartX 从目标纹理上的哪个像素点开始绘制字符图像。
		//--nStartY 从目标纹理上的哪个像素点开始绘制字符图像。
		//--pAdvanceX [out]如果值不为NULL，则返回该字符串在水平方向上占据多少个像素。
		//--pAdvanceY [out]如果值不为NULL，则返回该字符串在垂直方向上占据多少个像素。
		bool DrawString(wchar_t* pString, SoInt nValidCharCount, SoInt nStartX, SoInt nStartY, SoInt* pAdvanceX, SoInt* pAdvanceY);
		//获取指定的字符在水平方向上和垂直方向上分别占据多少个像素。
		bool GetCharAdvance(wchar_t theChar, SoInt& nAdvanceX, SoInt& nAdvanceY);

	protected:
		void DrawCharacter(SoInt nAdvanceX, SoInt nAdvanceY, unsigned char* pSrcBits, SoInt nSrcPitch, unsigned char* pDestBits, SoInt nDestPitch);
		void DrawCharacter_Edge(SoInt nAdvanceX, SoInt nAdvanceY, unsigned char* pSrcBits, SoInt nSrcPitch, unsigned char* pDestBits, SoInt nDestPitch);
		bool OpenFontFile(const char* pFontFileName);
		void Clear();
		const stCharGlyphData* LoadSingleChar(wchar_t theChar);
		bool DrawGlyphToTexture(const stCharGlyphData& stData, unsigned char* pPixelBuffer);
		bool DrawGlyphWithEdgeToTexture(const stCharGlyphData& stData, unsigned char* pPixelBuffer);
		void FillPixelData(IDirect3DTexture9* pTexture, const RECT& dest_rect, unsigned char* pPixelBuffer, int nWidth, int nHeight, bool bEdge);
		void GetThreeIndexByGlobalIndex(SoInt nGlobalIndex, SoInt& nTextureIndex, SoInt& nSlotIndexX, SoInt& nSlotIndexY);
		//
		const stCharGlyphData* GetOrCreateCharGlyph(wchar_t theChar);
		//获取纹理贴图数组中的第nTextureIndex张贴图。
		//如果该贴图尚未创建，则创建。
		IDirect3DTexture9* GetOrCreateTexture(SoInt nTextureIndex);

	private:
		typedef std::map<wchar_t, stCharGlyphData> mapChar2GlyphData;
		typedef std::vector<IDirect3DTexture9*> vecTexture;

	private:
		//静态变量，存储纹理贴图的宽高。
		static SoInt ms_nTextureWidth;
		static SoInt ms_nTextureHeight;

	private:
		//FreeType中一种外观的句柄。
		FT_Face m_FontFace;
		//使用字体的哪个字形，一般取默认值即可，默认值为0。
		SoInt m_nFontFaceIndex;
		//本字体对象的字号。
		SoInt m_nFontSizeWidth;
		SoInt m_nFontSizeHeight;
		//根据纹理贴图的宽高和字号，计算一张纹理贴图能容纳多少个字。
		//水平方向上能容纳多少个字。
		SoInt m_nGlyphCountX;
		//垂直方向上能容纳多少个字。
		SoInt m_nGlyphCountY;
		//存储字符编码到字符图像数据的映射。
		mapChar2GlyphData m_mapChar2GlyphData;
		//存储纹理贴图。
		vecTexture m_vecTexture;
		//维护一个索引位置，这个索引指向纹理贴图中待填充的空白位置。
		SoInt m_nIndexForTextureEmptySlot;
		//空格字符没有像素数据，当遇到空格字符时它占据几个像素。
		SoInt16 m_nSpaceAdvance;
		//Tab字符没有像素数据，当遇到Tab字符时它占据几个像素。
		SoInt16 m_nTabAdvance;
		//值为0表示不描边；大于0表示描边。如果描边，记录描边占据几个像素。
		//该值频繁与SoInt16类型的数值做四则运算，所以它的类型定义为SoInt16。
		SoInt16 m_nEdge;
		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		//绘制一个字符串前，需要填充的绘制参数。
		IDirect3DTexture9* m_pTempDestTexture;
		//当调用DrawCharacter()绘制一个字符时，记录这个字符的颜色是多少。
		SoFloat m_fTempCharColorR;
		SoFloat m_fTempCharColorG;
		SoFloat m_fTempCharColorB;
		//当调用DrawCharacter()绘制一个字符的描边时，记录这个字符的描边颜色是多少。
		SoFloat m_fTempEdgeColorR;
		SoFloat m_fTempEdgeColorG;
		SoFloat m_fTempEdgeColorB;
		bool m_bTempEdge;
		//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	};
}
//-----------------------------------------------------------------------------
#endif //_GGUIFreeTypeFont_h_
//-----------------------------------------------------------------------------
