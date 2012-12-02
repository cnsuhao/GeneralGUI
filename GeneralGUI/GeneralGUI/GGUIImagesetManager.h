//-----------------------------------------------------------------------------
// (C) oil
// 2012-10-20
//-----------------------------------------------------------------------------
#ifndef _GGUIImagesetManager_h_
#define _GGUIImagesetManager_h_
//-----------------------------------------------------------------------------
namespace GGUI
{
	class GGUIImageset;
	//-----------------------------------------------------------------------------
	class GGUIImagesetManager
	{
	public:
		GGUIImagesetManager();
		~GGUIImagesetManager();
		static GGUIImagesetManager* GetInstance();

		bool InitImagesetManager();
		void ReleaseImagesetManager();

		//从磁盘上加载指定的Imageset文件。
		//--pszImagesetFile 磁盘文件路径。
		//--pImagesetID 如果为有效值，不管返回值为true还是false，都会把得到的ImagesetID赋值给它。
		//如果指定的Imageset文件已经存在（已经加载），则返回false。
		bool CreateImagesetByFile(const tchar* pszImagesetFile, ImagesetID* pImagesetID);
		//临时函数。
		bool CreateImagesetByTextureFile(const tchar* pszTextureFile, const GGUITinyString& strImagesetName, ImagesetID* pImagesetID, ImageRectID* pImageRectID);
		//创建一个GGUIImageset对象。其ImageRect的个数为0.
		//--strImagesetName 名字。
		//--pImagesetID 如果为有效值，不管返回值为true还是false，都会把得到的ImagesetID赋值给它。
		//如果名字为strImagesetName的Imageset文件已经存在，则返回false。
		bool CreateImageset(const GGUITinyString& strImagesetName, ImagesetID* pImagesetID);
		//删除一个GGUIImageset对象。
		void ReleaseImageset(ImagesetID theImagesetID);
		//获取一个GGUIImageset对象。
		GGUIImageset* GetImageset(ImagesetID theImagesetID);
		ImagesetID GetImagesetIDByName(const GGUITinyString& strImagesetName);

	private:
		typedef std::map<GGUITinyString, ImagesetID> mapImagesetName2ImagesetID;

	private:
		static GGUIImagesetManager* ms_pInstance;
	private:
		//GGUIImageset指针数组。
		GGUIArray<GGUIImageset*> m_arrayImageset;
		//维护从ImagesetName到ImagesetID的映射。
		mapImagesetName2ImagesetID m_mapImagesetName2ID;

	};
	//-----------------------------------------------------------------------------
	inline GGUIImagesetManager* GGUIImagesetManager::GetInstance()
	{
		return ms_pInstance;
	}
	//-----------------------------------------------------------------------------
	inline GGUIImageset* GGUIImagesetManager::GetImageset(ImagesetID theImagesetID)
	{
		return m_arrayImageset.GetElement(theImagesetID);
	}
	//-----------------------------------------------------------------------------
	inline ImagesetID GGUIImagesetManager::GetImagesetIDByName(const GGUITinyString& strImagesetName)
	{
		mapImagesetName2ImagesetID::iterator it = m_mapImagesetName2ID.find(strImagesetName);
		if (it == m_mapImagesetName2ID.end())
		{
			return Invalid_ImagesetID;
		}
		else
		{
			return (it->second);
		}
	}
} //namespace GGUI
//-----------------------------------------------------------------------------
#endif //_GGUIImagesetManager_h_
//-----------------------------------------------------------------------------
