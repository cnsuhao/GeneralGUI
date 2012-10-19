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
	public:
		ImagesetID GetImagesetID() const;

		//设置本Imageset的名字。
		//注意，pszName字符串的size（包括结束符）不能大于MaxSize_ImagesetName；
		//如果大于的话，会被截断。
		void SetImagesetName(const char* pszName);
		//获取本Imageset的名字。
		const char* GetImagesetName() const;

		//
		void AddImageRect(const char* pszImageRectName);
		void RemoveImageRect(ImageRectID theRectID);
		const GGUIRect* GetImageRect(ImageRectID theRectID);
		ImageRectID GetImageRectIDByName(const char* pszImageRectName);


	protected:
		GGUIImageset();
		~GGUIImageset();
		void SetImagesetID(ImagesetID theID);
		//设置新的IDirect3DTexture9纹理。
		//传入NULL表示删除现有的纹理。
		void SetDXTexture(IDirect3DTexture9* pTexture);

	private:
		typedef std::map<GGUITinyString, ImageRectID> mapRectName2RectID;

	private:
		ImagesetID m_MyImagesetID;
		GGUITinyString m_MyImagesetName;
		IDirect3DTexture9* m_pDXTexture;
		//存储从ImageRectName到ImageRectID的映射。
		mapRectName2RectID m_mapRectName2RectID;
		//
		GGUIRect** m_pImageRectID2Rect;
		//记录数组中最多存储多少个元素。
		SoInt m_nCapacity;
		//记录数组中索引号最大的有效元素的下一个索引号。
		//如果数组中最后一个有效元素的下标为M，则该值为(M+1）。
		SoInt m_nIndexEnd;
	};
	//-----------------------------------------------------------------------------
	inline ImagesetID GGUIImageset::GetImagesetID() const
	{
		return m_MyImagesetID;
	}
	//-----------------------------------------------------------------------------
	const char* GGUIImageset::GetImagesetName() const
	{
		return m_MyImagesetName.GetValue();
	}
	//-----------------------------------------------------------------------------
	inline void GGUIImageset::SetImagesetID(ImagesetID theID)
	{
		m_MyImagesetID = theID;
	}
} //namespace GGUI
//-----------------------------------------------------------------------------
#endif //_GGUIImageset_h_
//-----------------------------------------------------------------------------
