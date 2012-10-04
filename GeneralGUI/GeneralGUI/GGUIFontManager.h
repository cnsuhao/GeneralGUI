//-----------------------------------------------------------------------------
// GGUI的字体管理器
// (C) oil
// 2012-10-04
//-----------------------------------------------------------------------------
#ifndef _GGUIFontManager_h_
#define _GGUIFontManager_h_
//-----------------------------------------------------------------------------
namespace GGUI
{
	//-----------------------------------------------------------------------------
	#define GGUIMaxFontCount 30
	//-----------------------------------------------------------------------------
	class GGUIFreeTypeFont;
	//-----------------------------------------------------------------------------
	class GGUIFontManager : public SoTSingleton<GGUIFontManager>
	{
	public:
		GGUIFontManager();
		~GGUIFontManager();
		static GGUIFontManager* GetInstance();

		bool AddFont(SoInt nID, const char* pFontFileName, SoInt nFontFaceIndex, SoInt nFontSizeWidth, SoInt nFontSizeHeight, SoInt16 nEdge);
		void RemoveFont(SoInt nID);
		GGUIFreeTypeFont* GetFont(SoInt nID);

	private:
		GGUIFreeTypeFont* m_pFontList[GGUIMaxFontCount];
	};
	//-----------------------------------------------------------------------------
	inline GGUIFontManager* GGUIFontManager::GetInstance()
	{
		return GGUIFontManager::Instance();
	}
	//-----------------------------------------------------------------------------
	inline GGUIFreeTypeFont* GGUIFontManager::GetFont(SoInt nID)
	{
		if (nID >= 0 && nID < GGUIMaxFontCount)
		{
			return m_pFontList[nID];
		}
		else
		{
			return 0;
		}
	}
}
//-----------------------------------------------------------------------------
#endif //_GGUIFontManager_h_
//-----------------------------------------------------------------------------
