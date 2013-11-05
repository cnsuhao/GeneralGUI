//-----------------------------------------------------------------------------
// (C) oil
// 2012-10-19
//-----------------------------------------------------------------------------
#ifndef _GGUIImageset_h_
#define _GGUIImageset_h_
//-----------------------------------------------------------------------------
namespace GGUI
{
	//-----------------------------------------------------------------------------
	class GGUIImageset
	{
		friend class GGUIImagesetManager;
	public:
		ImagesetID GetImagesetID() const;
		//获取本Imageset的名字。
		const GGUITinyString& GetImagesetName() const;
		DXTextureID GetDXTextureID() const;

		//新增一个ImageRect。
		//--strRectName ImageRect的名字。
		//--fLeft,fRight,fTop,fBottom 纹理坐标。
		//--pRectID 如果为有效值，不管函数返回true还是false，都会把得到的ImageRectID赋值给它。
		//如果已经存在名字为strRectName的ImageRect，则返回false。
		bool AddImageRect(const GGUITinyString& strRectName, SoFloat fLeft, SoFloat fRight, SoFloat fTop, SoFloat fBottom, ImageRectID* pRectID);
		void RemoveImageRect(ImageRectID theRectID);
		const GGUIRect* GetImageRect(ImageRectID theRectID) const;
		ImageRectID GetImageRectIDByName(const GGUITinyString& strRectName) const;
		const GGUITinyString* GetImageRectNameByID(ImageRectID theRectID) const;
		//ImageRect中存储的是纹理UV坐标。这个函数用于获取ImageRect的像素坐标。
		bool GetImageRectPixel(ImageRectID theRectID, GGUIRect& theRect) const;

	protected:
		GGUIImageset();
		~GGUIImageset();
		void SetImagesetID(ImagesetID theID);
		//设置本Imageset的名字。
		//注意，pszName字符串的size（包括结束符）不能大于MaxSize_ImagesetName；
		//如果大于的话，会被截断。
		void SetImagesetName(const tchar* pszName);
		//设置新的DXTextureID。
		//传入无效值表示删除现有的纹理。
		void SetDXTextureID(DXTextureID theTextureID);

	private:
		typedef std::map<GGUITinyString, ImageRectID> mapRectName2RectID;

	private:
		//存储GGUIRect*的数组。
		GGUIArray<GGUIRect*> m_arrayRect;
		//
		ImagesetID m_MyImagesetID;
		DXTextureID m_MyDXTextureID;
		GGUITinyString m_MyImagesetName;
		//记录DX贴图资源的宽高。
		SoInt m_nDXTextureWidth;
		SoInt m_nDXTextureHeight;
		//存储从ImageRectName到ImageRectID的映射。
		mapRectName2RectID m_mapRectName2RectID;

	};
	//-----------------------------------------------------------------------------
	inline ImagesetID GGUIImageset::GetImagesetID() const
	{
		return m_MyImagesetID;
	}
	//-----------------------------------------------------------------------------
	inline const GGUITinyString& GGUIImageset::GetImagesetName() const
	{
		return m_MyImagesetName;
	}
	//-----------------------------------------------------------------------------
	inline DXTextureID GGUIImageset::GetDXTextureID() const
	{
		return m_MyDXTextureID;
	}
	//-----------------------------------------------------------------------------
	inline const GGUIRect* GGUIImageset::GetImageRect(ImageRectID theRectID) const
	{
		return m_arrayRect.GetElement(theRectID);
	}
	//-----------------------------------------------------------------------------
	inline ImageRectID GGUIImageset::GetImageRectIDByName(const GGUITinyString& strRectName) const
	{
		mapRectName2RectID::const_iterator it = m_mapRectName2RectID.find(strRectName);
		if (it == m_mapRectName2RectID.end())
		{
			return Invalid_ImageRectID;
		}
		else
		{
			return (it->second);
		}
	}
	//-----------------------------------------------------------------------------
	inline void GGUIImageset::SetImagesetID(ImagesetID theID)
	{
		m_MyImagesetID = theID;
	}
	//-----------------------------------------------------------------------------
	inline void GGUIImageset::SetImagesetName(const tchar* pszName)
	{
		m_MyImagesetName.SetValue(pszName);
	}
} //namespace GGUI
//-----------------------------------------------------------------------------
#endif //_GGUIImageset_h_
//-----------------------------------------------------------------------------
