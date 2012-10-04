//-----------------------------------------------------------------------------
// GGUI的FreeType字体
// (C) oil
// 2012-10-04
//-----------------------------------------------------------------------------
#include "GGUIStdAfx.h"
#include "GGUIFreeTypeFont.h"
#include "GGUISystem.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	//--------------------------------------------------------------------
	//FreeType库构造和析构的引用计数。
	static int s_nFTRefCount = 0;
	//A handle to the FreeType library
	static FT_Library ft_lib;
	//字号的最小值。
	const int MinFontSize = 5;
	//--------------------------------------------------------------------
	#undef __FTERRORS_H__
	#define FT_ERRORDEF( e, v, s ) s,
	#define FT_ERROR_START_LIST static const char* ft_errors[] = {
	#define FT_ERROR_END_LIST 0};
	#include FT_ERRORS_H
	//--------------------------------------------------------------------
	SoInt GGUIFreeTypeFont::ms_nTextureWidth = 512;
	SoInt GGUIFreeTypeFont::ms_nTextureHeight = 512;
	//--------------------------------------------------------------------
	GGUIFreeTypeFont::GGUIFreeTypeFont()
	:m_FontFace(0)
	,m_nFontFaceIndex(0)
	,m_nFontSizeWidth(0)
	,m_nFontSizeHeight(0)
	,m_nGlyphCountX(0)
	,m_nGlyphCountY(0)
	,m_nIndexForTextureEmptySlot(0)
	,m_nSpaceAdvance(1)
	,m_nTabAdvance(1)
	,m_nEdge(1)
	,m_pTempDestTexture(0)
	,m_fTempCharColorR(0.0f)
	,m_fTempCharColorG(0.0f)
	,m_fTempCharColorB(0.0f)
	,m_fTempEdgeColorR(0.0f)
	,m_fTempEdgeColorG(0.0f)
	,m_fTempEdgeColorB(0.0f)
	,m_bTempEdge(false)
	{
		m_vecTexture.reserve(4);
		if (!s_nFTRefCount++)
		{
			FT_Init_FreeType(&ft_lib);
		}
	}
	//--------------------------------------------------------------------
	GGUIFreeTypeFont::~GGUIFreeTypeFont()
	{
		Clear();
		if (!--s_nFTRefCount)
		{
			FT_Done_FreeType(ft_lib);
		}
	}
	//--------------------------------------------------------------------
	bool GGUIFreeTypeFont::InitFont(const char* pFontFileName, SoInt nFontFaceIndex, SoInt nFontSizeWidth, SoInt nFontSizeHeight, SoInt16 nEdge)
	{
		//检查参数
		if (!pFontFileName)
		{
			return false;
		}

		m_nFontFaceIndex = nFontFaceIndex;
		m_nFontSizeWidth = nFontSizeWidth<MinFontSize ? MinFontSize : nFontSizeWidth;
		m_nFontSizeHeight = nFontSizeHeight<MinFontSize ? MinFontSize : nFontSizeHeight;
		m_nGlyphCountX = ms_nTextureWidth / m_nFontSizeWidth;
		m_nGlyphCountY = ms_nTextureHeight / m_nFontSizeHeight;
		m_nEdge = nEdge>0 ? nEdge : 0;
		m_nSpaceAdvance = nFontSizeWidth / 2;
		m_nTabAdvance = nFontSizeWidth * 2;

		//打开字体文件。
		if (!OpenFontFile(pFontFileName))
		{
			return false;
		}

		//预先加载常用的所有的ASCII字符。
		//因为这些字符使用的最频繁，保证它们处于同一张纹理内。
		for (wchar_t i=0; i<128; ++i)
		{
			LoadSingleChar(i);
		}

		LoadSingleChar(L'珊');

		//=======================================

			char szBMPName[256] = {0};
			StringCbPrintfA(szBMPName, sizeof(szBMPName), "D:\\FreeTypeAll.png");
			D3DXSaveTextureToFileA(szBMPName, D3DXIFF_PNG, m_vecTexture[0], NULL);

		return true;
	}
	//--------------------------------------------------------------------
	void GGUIFreeTypeFont::SetDrawParam(IDirect3DTexture9* pDestTexture, SoFloat fCharColorR, SoFloat fCharColorG, SoFloat fCharColorB,
		bool bEdge, SoFloat fEdgeColorR, SoFloat fEdgeColorG, SoFloat fEdgeColorB)
	{
		m_pTempDestTexture = pDestTexture;
		m_fTempCharColorR = fCharColorR;
		m_fTempCharColorG = fCharColorG;
		m_fTempCharColorB = fCharColorB;
		m_bTempEdge = bEdge;
		m_fTempEdgeColorR = fEdgeColorR;
		m_fTempEdgeColorG = fEdgeColorG;
		m_fTempEdgeColorB = fEdgeColorB;
	}
	//--------------------------------------------------------------------
	bool GGUIFreeTypeFont::DrawString(wchar_t* pString, SoInt nValidCharCount, SoInt nStartX, SoInt nStartY, SoInt* pAdvanceX, SoInt* pAdvanceY)
	{
		if (!m_pTempDestTexture)
		{
			return false;
		}
		if (!pString)
		{
			return false;
		}
		//把字符串遍历一次，确保每个字符都从字体文件中解析到了字体贴图中；
		//同时，计算整个字符串将要占据的宽高。
		SoInt nStringAdvanceX = 0;
		SoInt nStringAdvanceY = m_nFontSizeHeight;
		wchar_t charSpace = 32;
		wchar_t charTab = 23;
		for (SoInt i=0; i<nValidCharCount; ++i)
		{
			if (pString[i] == charSpace)
			{
				nStringAdvanceX += m_nSpaceAdvance;
			}
			else if (pString[i] == charTab)
			{
				nStringAdvanceX += m_nTabAdvance;
			}
			else
			{
				const stCharGlyphData* pData = GetOrCreateCharGlyph(pString[i]);
				if (pData && pData->theCharGlyphID != Invalid_CharGlyphID)
				{
					nStringAdvanceX += pData->AdvanceX;
				}
			}
		}
		if (pAdvanceX)
		{
			*pAdvanceX = nStringAdvanceX;
		}
		if (pAdvanceY)
		{
			*pAdvanceY = nStringAdvanceY;
		}
		//Lock目标纹理贴图。
		UINT uiLevel = 0;
		D3DLOCKED_RECT locked_DestRect;
		RECT dest_rect;
		dest_rect.left = nStartX;
		dest_rect.right = nStartX + nStringAdvanceX;
		dest_rect.top = nStartY;
		dest_rect.bottom = nStartY + nStringAdvanceY;
		if (m_pTempDestTexture->LockRect(uiLevel, &locked_DestRect, &dest_rect, D3DLOCK_DISCARD) != D3D_OK)
		{
			return false;
		}
		//开始向目标纹理中填充像素。
		SoInt nCurrentAdvanceX = 0;
		//SoInt nCurrentStartY = 0;
		SoInt nCurrentSrcTextureIndex = -1; //记录当前正在使用哪个字体贴图。
		D3DLOCKED_RECT locked_SrcRect;
		for (SoInt i=0; i<nValidCharCount; ++i)
		{
			if (pString[i] == charSpace)
			{
				nCurrentAdvanceX += m_nSpaceAdvance;
			}
			else if (pString[i] == charTab)
			{
				nCurrentAdvanceX += m_nTabAdvance;
			}
			else
			{
				const stCharGlyphData* pData = GetOrCreateCharGlyph(pString[i]);
				if (pData && pData->theCharGlyphID != Invalid_CharGlyphID)
				{
					SoInt nTextureIndex = -1;
					SoInt nSlotIndexX = 0;
					SoInt nSlotIndexY = 0;
					GetThreeIndexByGlobalIndex(pData->theCharGlyphID, nTextureIndex, nSlotIndexX, nSlotIndexY);
					if (nTextureIndex != nCurrentSrcTextureIndex)
					{
						//关闭旧的，打开新的。
						if (nCurrentSrcTextureIndex != -1)
						{
							m_vecTexture[nCurrentSrcTextureIndex]->UnlockRect(uiLevel);
						}
						nCurrentSrcTextureIndex = nTextureIndex;
						//把源字体贴图整个lock住。
						if (m_vecTexture[nTextureIndex]->LockRect(uiLevel, &locked_SrcRect, NULL, D3DLOCK_READONLY) != D3D_OK)
						{
							//Error
							nCurrentSrcTextureIndex = -1;
							break;
						}
					}
					unsigned char* pDestBits = (unsigned char*)locked_DestRect.pBits + nCurrentAdvanceX * 4;
					unsigned char* pSrcBits = ((unsigned char*)locked_SrcRect.pBits) + ((nSlotIndexY * m_nFontSizeHeight) * locked_SrcRect.Pitch + nSlotIndexX * m_nFontSizeWidth);
					if (m_bTempEdge)
					{
						DrawCharacter_Edge(pData->AdvanceX, pData->AdvanceY, pSrcBits+m_nFontSizeWidth, locked_SrcRect.Pitch, pDestBits, locked_DestRect.Pitch);
					}
					DrawCharacter(pData->AdvanceX, pData->AdvanceY, pSrcBits, locked_SrcRect.Pitch, pDestBits, locked_DestRect.Pitch);
					nCurrentAdvanceX += pData->AdvanceX;
				}
			}
		}
		if (nCurrentSrcTextureIndex != -1)
		{
			m_vecTexture[nCurrentSrcTextureIndex]->UnlockRect(uiLevel);
		}
		m_pTempDestTexture->UnlockRect(uiLevel);
		return true;
	}
	//--------------------------------------------------------------------
	void GGUIFreeTypeFont::DrawCharacter(SoInt nAdvanceX, SoInt nAdvanceY,
		unsigned char* pSrcBits, SoInt nSrcPitch, unsigned char* pDestBits, SoInt nDestPitch)
	{
		for (SoInt y = 0; y < nAdvanceY; ++y)
		{
			for (SoInt x = 0; x < nAdvanceX; ++x)
			{
				unsigned char* src_pixel = pSrcBits + nSrcPitch * y + x;
				if (src_pixel[0] > 0)
				{
					//本像素不是透明的，src_pixel[3]就是透明度。
					unsigned char* dest_pixel = pDestBits + nDestPitch * y + x * 4;
					if (src_pixel[0] == 0xFF)
					{
						dest_pixel[0] = (unsigned char)(255.0f * m_fTempCharColorB);
						dest_pixel[1] = (unsigned char)(255.0f * m_fTempCharColorG);
						dest_pixel[2] = (unsigned char)(255.0f * m_fTempCharColorR);
					}
					else
					{
						//float fAlpha = ((float)(src_pixel[3])) / 255.0f;
						//dest_pixel[0] = (unsigned char)(dest_pixel[0]*(1.0f-fAlpha) + 255.0f*fColorB*fAlpha);
						//上面注释的两句是原始算法，下面是精简后的代码。
						float fSrcPixel3 = (float)src_pixel[0];
						float fInverseAlpha = 1.0f - fSrcPixel3 / 255.0f;
						dest_pixel[0] = (unsigned char)(dest_pixel[0]*fInverseAlpha + m_fTempCharColorB*fSrcPixel3);
						dest_pixel[1] = (unsigned char)(dest_pixel[1]*fInverseAlpha + m_fTempCharColorG*fSrcPixel3);
						dest_pixel[2] = (unsigned char)(dest_pixel[2]*fInverseAlpha + m_fTempCharColorR*fSrcPixel3);
					}
				}
			}
		}
	}
	//--------------------------------------------------------------------
	void GGUIFreeTypeFont::DrawCharacter_Edge(SoInt nAdvanceX, SoInt nAdvanceY, 
		unsigned char* pSrcBits, SoInt nSrcPitch, unsigned char* pDestBits, SoInt nDestPitch)
	{
		for (SoInt y = 0; y < nAdvanceY; ++y)
		{
			for (SoInt x = 0; x < nAdvanceX; ++x)
			{
				unsigned char* src_pixel = pSrcBits + nSrcPitch * y + x;
				if (src_pixel[0] > 0)
				{
					//本像素不是透明的，src_pixel[3]就是透明度。
					unsigned char* dest_pixel = pDestBits + nDestPitch * y + x * 4;
					if (src_pixel[0] == 0xFF)
					{
						dest_pixel[0] = (unsigned char)(255.0f * m_fTempEdgeColorB);
						dest_pixel[1] = (unsigned char)(255.0f * m_fTempEdgeColorG);
						dest_pixel[2] = (unsigned char)(255.0f * m_fTempEdgeColorR);
					}
					else
					{
						//float fAlpha = ((float)(src_pixel[3])) / 255.0f;
						//dest_pixel[0] = (unsigned char)(dest_pixel[0]*(1.0f-fAlpha) + 255.0f*fColorB*fAlpha);
						//上面注释的两句是原始算法，下面是精简后的代码。
						float fSrcPixel3 = (float)src_pixel[0];
						float fInverseAlpha = 1.0f - fSrcPixel3 / 255.0f;
						dest_pixel[0] = (unsigned char)(dest_pixel[0]*fInverseAlpha + m_fTempEdgeColorB*fSrcPixel3);
						dest_pixel[1] = (unsigned char)(dest_pixel[1]*fInverseAlpha + m_fTempEdgeColorG*fSrcPixel3);
						dest_pixel[2] = (unsigned char)(dest_pixel[2]*fInverseAlpha + m_fTempEdgeColorR*fSrcPixel3);
					}
				}
			}
		}
	}
	//--------------------------------------------------------------------
	bool GGUIFreeTypeFont::GetCharAdvance(wchar_t theChar, SoInt& nAdvanceX, SoInt& nAdvanceY)
	{
		const stCharGlyphData* pGlyphData = GetOrCreateCharGlyph(theChar);
		if (pGlyphData && pGlyphData->theCharGlyphID != Invalid_CharGlyphID)
		{
			nAdvanceX = pGlyphData->AdvanceX;
			nAdvanceY = pGlyphData->AdvanceY;
			return true;
		}
		else
		{
			return false;
		}
	}
	//--------------------------------------------------------------------
	bool GGUIFreeTypeFont::OpenFontFile(const char* pFontFileName)
	{
		//FT模块的返回值。为0表示成功。
		FT_Error nFTResult = 0;

		//加载一个字体。
		nFTResult = FT_New_Face(ft_lib, pFontFileName, m_nFontFaceIndex, &m_FontFace);
		if (nFTResult)
		{
			::MessageBoxA(0,"加载字库文件失败",0,0);
			return false;
		}

		//FontFace加载完毕后，默认是Unicode charmap。
		//这里再主动设置一下，使用Unicode charmap。
		nFTResult = FT_Select_Charmap(m_FontFace, FT_ENCODING_UNICODE);
		if (nFTResult)
		{
			::MessageBoxA(0,"选择Unicode编码失败",0,0);
			return false;
		}

		//设置字符宽高，像素单位。
		nFTResult = FT_Set_Pixel_Sizes(m_FontFace, m_nFontSizeWidth, m_nFontSizeHeight);
		if (nFTResult)
		{
			::MessageBoxA(0,"设置大小失败",0,0);
			return false;
		}

		return true;
	}
	//--------------------------------------------------------------------
	void GGUIFreeTypeFont::Clear()
	{
		if (m_FontFace)
		{
			FT_Done_Face(m_FontFace);
			m_FontFace = 0;
		}
		m_nFontFaceIndex = 0;
		m_nFontSizeWidth = 0;
		m_nFontSizeHeight = 0;
		m_nGlyphCountX = 0;
		m_nGlyphCountY = 0;
		m_nIndexForTextureEmptySlot = 0;
		m_mapChar2GlyphData.clear();
		for (vecTexture::iterator it = m_vecTexture.begin();
			it != m_vecTexture.end();
			++it)
		{
			(*it)->Release();
		}
		m_vecTexture.clear();
	}
	//--------------------------------------------------------------------
	const stCharGlyphData* GGUIFreeTypeFont::LoadSingleChar(wchar_t theChar)
	{
		//一开始就为theChar分配内存，表示这个字符尝试过加载。
		stCharGlyphData& stData = m_mapChar2GlyphData[theChar];

		//启用抗锯齿。不使用抗锯齿的话，太难看了。
		bool bAntiAliased = true;
		FT_Int32 nLoadFlags = FT_LOAD_RENDER | FT_LOAD_FORCE_AUTOHINT | (bAntiAliased ? FT_LOAD_TARGET_NORMAL : FT_LOAD_TARGET_MONO);
		FT_Error nResult = FT_Load_Char(m_FontFace, theChar, nLoadFlags);
		if (nResult)
		{
			//字体文件中没有这个字！
			//用一个错误字符表示，比如星号。
			//未完待续。
			::MessageBoxA(0,"GGUIFreeTypeFont::LoadSingleChar : 字体文件中没有这个字",0,0);
			return &stData;
		}

		//
		const FT_GlyphSlot& theGlyph = m_FontFace->glyph;
		//
		stData.Character = theChar;
		//本类只生成横向排版字形，不处理竖向排版。在非等宽字体下，X方向上的步进是各不相同的。
		stData.AdvanceX = (int)(theGlyph->advance.x >> 6);
		//本类只生成横向排版字形，所以Y方向上的步进是固定的；如果是竖向排版，则X方向上的步进是固定的。
		stData.AdvanceY = m_nFontSizeHeight;
		stData.LeftMargin = theGlyph->bitmap_left;
		stData.TopMargin = m_nFontSizeHeight - theGlyph->bitmap_top;
		stData.BitmapWidth = theGlyph->bitmap.width;
		stData.BitmapHeight = theGlyph->bitmap.rows;

		//
		const FT_Bitmap& bitmap = theGlyph->bitmap;
		//一个byte表示一个像素，存储bitmap灰度图。
		unsigned char* pPixelBuffer = 0;
		bool bShouldDeletePixelBuffer = false;
		switch (bitmap.pixel_mode)
		{
		case FT_PIXEL_MODE_GRAY:
			{
				pPixelBuffer = (unsigned char*)bitmap.buffer;
				bShouldDeletePixelBuffer = false;
			}
			break;
		case FT_PIXEL_MODE_MONO:
			{
				int width = bitmap.width;
				int height = bitmap.rows;
				pPixelBuffer = new unsigned char[width*height];
				bShouldDeletePixelBuffer = true;
				int nIndex = 0;
				for (int y = 0; y < height; ++y)
				{
					for (int x = 0; x < width; ++x)
					{
						if (bitmap.buffer[y*width + x/8] & (0x80 >> (x & 7)))
						{
							pPixelBuffer[nIndex] = 0xFF;
						}
						else
						{
							pPixelBuffer[nIndex] = 0x00;
						}
						++nIndex;
					}
				}
			}
			break;
		default:
			::MessageBoxA(0,"GGUIFreeTypeFont::LoadSingleChar : 不支持的 bitmap.pixel_mode",0,0);
			break;
		}

		if (!pPixelBuffer)
		{
			//出错了。
			return &stData;
		}

		stData.theCharGlyphID = m_nIndexForTextureEmptySlot;
		++m_nIndexForTextureEmptySlot;
		//
		DrawGlyphToTexture(stData, pPixelBuffer);
		//
		if (m_nEdge > 0)
		{
			++m_nIndexForTextureEmptySlot;
			DrawGlyphWithEdgeToTexture(stData, pPixelBuffer);
		}
		//
		if (bShouldDeletePixelBuffer)
		{
			delete [] pPixelBuffer;
		}
		//
		return &stData;
	}
	//--------------------------------------------------------------------
	bool GGUIFreeTypeFont::DrawGlyphToTexture(const stCharGlyphData& stData, unsigned char* pPixelBuffer)
	{
		//获取纹理贴图中待填充的Rect位置。
		//待填充的Rect位于哪个贴图内。
		SoInt nTextureIndex = 0;
		SoInt nSlotIndexX = 0;
		SoInt nSlotIndexY = 0;
		GetThreeIndexByGlobalIndex(stData.theCharGlyphID, nTextureIndex, nSlotIndexX, nSlotIndexY);
		//如果贴图尚未创建，则创建。
		IDirect3DTexture9* pTexture = GetOrCreateTexture(nTextureIndex);
		if (!pTexture)
		{
			return false;
		}

		//Lock顶层贴图。
		RECT dest_rect;
		dest_rect.left = nSlotIndexX * m_nFontSizeWidth + stData.LeftMargin;
		dest_rect.right = dest_rect.left + stData.BitmapWidth;
		dest_rect.top = nSlotIndexY * m_nFontSizeHeight + stData.TopMargin;
		dest_rect.bottom = dest_rect.top + stData.BitmapHeight;
		FillPixelData(pTexture, dest_rect, pPixelBuffer, stData.BitmapWidth, stData.BitmapHeight, false);
		return true;
	}
	//--------------------------------------------------------------------
	bool GGUIFreeTypeFont::DrawGlyphWithEdgeToTexture(const stCharGlyphData& stData, unsigned char* pPixelBuffer)
	{
		//获取纹理贴图中待填充的Rect位置。
		//待填充的Rect位于哪个贴图内。
		SoInt nTextureIndex = 0;
		SoInt nSlotIndexX = 0;
		SoInt nSlotIndexY = 0;
		GetThreeIndexByGlobalIndex(stData.theCharGlyphID+1, nTextureIndex, nSlotIndexX, nSlotIndexY);
		//如果贴图尚未创建，则创建。
		IDirect3DTexture9* pTexture = GetOrCreateTexture(nTextureIndex);
		if (!pTexture)
		{
			return false;
		}

		RECT dest_rect;
		short LeftMargin = 0;
		short TopMargin = 0;
		//向左偏移
		LeftMargin = stData.LeftMargin - m_nEdge;
		TopMargin = stData.TopMargin;
		if (LeftMargin < 0)
		{
			LeftMargin = 0;
		}
		dest_rect.left = nSlotIndexX * m_nFontSizeWidth + LeftMargin;
		dest_rect.right = dest_rect.left + stData.BitmapWidth;
		dest_rect.top = nSlotIndexY * m_nFontSizeHeight + TopMargin;
		dest_rect.bottom = dest_rect.top + stData.BitmapHeight;
		FillPixelData(pTexture, dest_rect, pPixelBuffer, stData.BitmapWidth, stData.BitmapHeight, true);
		//向左上偏移
		LeftMargin = stData.LeftMargin - m_nEdge;
		TopMargin = stData.TopMargin - m_nEdge;
		if (LeftMargin < 0)
		{
			LeftMargin = 0;
		}
		if (TopMargin < 0)
		{
			TopMargin = 0;
		}
		dest_rect.left = nSlotIndexX * m_nFontSizeWidth + LeftMargin;
		dest_rect.right = dest_rect.left + stData.BitmapWidth;
		dest_rect.top = nSlotIndexY * m_nFontSizeHeight + TopMargin;
		dest_rect.bottom = dest_rect.top + stData.BitmapHeight;
		FillPixelData(pTexture, dest_rect, pPixelBuffer, stData.BitmapWidth, stData.BitmapHeight, true);
		//向上偏移
		LeftMargin = stData.LeftMargin;
		TopMargin = stData.TopMargin - m_nEdge;
		if (TopMargin < 0)
		{
			TopMargin = 0;
		}
		dest_rect.left = nSlotIndexX * m_nFontSizeWidth + LeftMargin;
		dest_rect.right = dest_rect.left + stData.BitmapWidth;
		dest_rect.top = nSlotIndexY * m_nFontSizeHeight + TopMargin;
		dest_rect.bottom = dest_rect.top + stData.BitmapHeight;
		FillPixelData(pTexture, dest_rect, pPixelBuffer, stData.BitmapWidth, stData.BitmapHeight, true);
		//向右上偏移
		LeftMargin = stData.LeftMargin + m_nEdge;
		TopMargin = stData.TopMargin - m_nEdge;
		//if (LeftMargin + stData.BitmapWidth > m_nFontSizeWidth)
		//{
		//	LeftMargin = m_nFontSizeWidth - stData.BitmapWidth;
		//}
		if (TopMargin < 0)
		{
			TopMargin = 0;
		}
		dest_rect.left = nSlotIndexX * m_nFontSizeWidth + LeftMargin;
		dest_rect.right = dest_rect.left + stData.BitmapWidth;
		dest_rect.top = nSlotIndexY * m_nFontSizeHeight + TopMargin;
		dest_rect.bottom = dest_rect.top + stData.BitmapHeight;
		FillPixelData(pTexture, dest_rect, pPixelBuffer, stData.BitmapWidth, stData.BitmapHeight, true);
		//向右偏移
		LeftMargin = stData.LeftMargin + m_nEdge;
		TopMargin = stData.TopMargin;
		//if (LeftMargin + stData.BitmapWidth > m_nFontSizeWidth)
		//{
		//	LeftMargin = m_nFontSizeWidth - stData.BitmapWidth;
		//}
		dest_rect.left = nSlotIndexX * m_nFontSizeWidth + LeftMargin;
		dest_rect.right = dest_rect.left + stData.BitmapWidth;
		dest_rect.top = nSlotIndexY * m_nFontSizeHeight + TopMargin;
		dest_rect.bottom = dest_rect.top + stData.BitmapHeight;
		FillPixelData(pTexture, dest_rect, pPixelBuffer, stData.BitmapWidth, stData.BitmapHeight, true);
		//向右下偏移
		LeftMargin = stData.LeftMargin + m_nEdge;
		TopMargin = stData.TopMargin + m_nEdge;
		//if (LeftMargin + stData.BitmapWidth > m_nFontSizeWidth)
		//{
		//	LeftMargin = m_nFontSizeWidth - stData.BitmapWidth;
		//}
		//if (TopMargin + stData.BitmapHeight > m_nFontSizeHeight)
		//{
		//	TopMargin = m_nFontSizeHeight - stData.BitmapHeight;
		//}
		dest_rect.left = nSlotIndexX * m_nFontSizeWidth + LeftMargin;
		dest_rect.right = dest_rect.left + stData.BitmapWidth;
		dest_rect.top = nSlotIndexY * m_nFontSizeHeight + TopMargin;
		dest_rect.bottom = dest_rect.top + stData.BitmapHeight;
		FillPixelData(pTexture, dest_rect, pPixelBuffer, stData.BitmapWidth, stData.BitmapHeight, true);
		//向下偏移
		LeftMargin = stData.LeftMargin;
		TopMargin = stData.TopMargin + m_nEdge;
		//if (TopMargin + stData.BitmapHeight > m_nFontSizeHeight)
		//{
		//	TopMargin = m_nFontSizeHeight - stData.BitmapHeight;
		//}
		dest_rect.left = nSlotIndexX * m_nFontSizeWidth + LeftMargin;
		dest_rect.right = dest_rect.left + stData.BitmapWidth;
		dest_rect.top = nSlotIndexY * m_nFontSizeHeight + TopMargin;
		dest_rect.bottom = dest_rect.top + stData.BitmapHeight;
		FillPixelData(pTexture, dest_rect, pPixelBuffer, stData.BitmapWidth, stData.BitmapHeight, true);
		//向左下偏移
		LeftMargin = stData.LeftMargin - m_nEdge;
		TopMargin = stData.TopMargin + m_nEdge;
		if (LeftMargin < 0)
		{
			LeftMargin = 0;
		}
		//if (TopMargin + stData.BitmapHeight > m_nFontSizeHeight)
		//{
		//	TopMargin = m_nFontSizeHeight - stData.BitmapHeight;
		//}
		dest_rect.left = nSlotIndexX * m_nFontSizeWidth + LeftMargin;
		dest_rect.right = dest_rect.left + stData.BitmapWidth;
		dest_rect.top = nSlotIndexY * m_nFontSizeHeight + TopMargin;
		dest_rect.bottom = dest_rect.top + stData.BitmapHeight;
		FillPixelData(pTexture, dest_rect, pPixelBuffer, stData.BitmapWidth, stData.BitmapHeight, true);
		return true;
	}
	//--------------------------------------------------------------------
	void GGUIFreeTypeFont::FillPixelData(IDirect3DTexture9* pTexture, const RECT& dest_rect, 
		unsigned char* pPixelBuffer, int nWidth, int nHeight, bool bEdge)
	{
		if (!pTexture || !pPixelBuffer)
		{
			return;
		}

		//Lock顶层贴图。
		UINT uiLevel = 0;
		D3DLOCKED_RECT locked_rect;
		if (pTexture->LockRect(uiLevel, &locked_rect, &dest_rect, D3DLOCK_DISCARD) != D3D_OK)
		{
			return;
		}

		int nIndex = 0;
		for (int y = 0; y < nHeight; ++y)
		{
			unsigned char* pDestBuffer = ((unsigned char*)locked_rect.pBits) + locked_rect.Pitch * y;
			for (int x = 0; x < nWidth; ++x)
			{
				if (bEdge)
				{
					if (pDestBuffer[x] == 0 && pPixelBuffer[nIndex] > 0)
						pDestBuffer[x] = 0x50;
				}
				else
				{
					pDestBuffer[x] = pPixelBuffer[nIndex];
				}
				++nIndex;
			}
		}
		pTexture->UnlockRect(uiLevel);
	}
	//--------------------------------------------------------------------
	void GGUIFreeTypeFont::GetThreeIndexByGlobalIndex(SoInt nGlobalIndex, SoInt& nTextureIndex, SoInt& nSlotIndexX, SoInt& nSlotIndexY)
	{
		if (nGlobalIndex >= 0)
		{
			SoInt nCountPerTexture = m_nGlyphCountX * m_nGlyphCountY;
			nTextureIndex = nGlobalIndex / nCountPerTexture;
			SoInt nYuShu = nGlobalIndex - nTextureIndex * nCountPerTexture;
			nSlotIndexY = nYuShu / m_nGlyphCountX;
			nSlotIndexX = nYuShu - nSlotIndexY * m_nGlyphCountX;
		}
	}
	//--------------------------------------------------------------------
	const stCharGlyphData* GGUIFreeTypeFont::GetOrCreateCharGlyph(wchar_t theChar)
	{
		mapChar2GlyphData::iterator it = m_mapChar2GlyphData.find(theChar);
		if (it == m_mapChar2GlyphData.end())
		{
			return LoadSingleChar(theChar);
		}
		else
		{
			return (&(it->second));
		}
	}
	//--------------------------------------------------------------------
	IDirect3DTexture9* GGUIFreeTypeFont::GetOrCreateTexture(SoInt nTextureIndex)
	{
		IDirect3DTexture9* pTexture = 0;
		if ((SoInt)m_vecTexture.size() > nTextureIndex)
		{
			pTexture = m_vecTexture[nTextureIndex];
		}
		else
		{
			//产生几层Mipmap纹理层级，值为0表示产生完整的纹理层级链表。
			UINT uiLevels = 1;
			//取默认值。
			DWORD dwUsage = 0;
			//图片像素格式，创建灰度图，只需要存储像素点的Alpha值即可。
			D3DFORMAT eFormat = D3DFMT_A8;
			//使用系统内存，因为这个Texture不会被送入显卡中进行绘制，而且需要频繁的Lock操作和
			//内存拷贝操作，所以放到系统内存最合适了。当设备丢失时不必重新创建。
			D3DPOOL ePool = D3DPOOL_SYSTEMMEM;
			//
			if (GGUISystem::GetInstance()->GetD3DDevice()->CreateTexture(ms_nTextureWidth, ms_nTextureHeight, 
				uiLevels, dwUsage, eFormat, ePool, &pTexture, NULL) == D3D_OK)
			{
				m_vecTexture.push_back(pTexture);
			}
			else
			{
				::MessageBoxA(0,"GGUIFreeTypeFont::GetOrCreateTexture : 创建贴图失败",0,0);
			}
		}
		return pTexture;
	}
}
//-----------------------------------------------------------------------------
