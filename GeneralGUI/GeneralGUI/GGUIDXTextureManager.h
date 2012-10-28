//-----------------------------------------------------------------------------
// (C) oil
// 2012-10-21
//-----------------------------------------------------------------------------
#ifndef _GGUIDXTextureManager_h_
#define _GGUIDXTextureManager_h_
//-----------------------------------------------------------------------------
namespace GGUI
{
	//-----------------------------------------------------------------------------
	class GGUIDXTextureManager : public SoTSingleton<GGUIDXTextureManager>
	{
	public:
		GGUIDXTextureManager();
		~GGUIDXTextureManager();
		static GGUIDXTextureManager* GetInstance();
		bool InitDXTextureManager();
		void ReleaseDXTextureManager();

		//从磁盘上加载贴图文件。
		//--pFileName 磁盘上的文件名。
		//--pDXTextureID 如果为有效值，则把新的DXTextureID赋值给它。
		bool LoadTextureFromDisk(const tchar* pszFileName, DXTextureID* pDXTextureID);
		//删除一个贴图。
		void ReleaseDXTexture(DXTextureID theTextureID);
		//获取DXTexture指针。
		IDirect3DTexture9* GetDXTexture(DXTextureID theTextureID);

	private:
		//
		IDirect3DTexture9** m_arrayDXTexture;
		//记录数组中最多存储多少个元素。
		SoInt m_nCapacity;
		//记录数组中索引号最大的有效元素的下一个索引号。
		//如果数组中最后一个有效元素的下标为M，则该值为(M+1）。
		SoInt m_nIndexEnd;
	};
	//-----------------------------------------------------------------------------
	inline GGUIDXTextureManager* GGUIDXTextureManager::GetInstance()
	{
		return GGUIDXTextureManager::Instance();
	}
	//-----------------------------------------------------------------------------
	inline IDirect3DTexture9* GGUIDXTextureManager::GetDXTexture(DXTextureID theTextureID)
	{
		if (theTextureID >= 0 && theTextureID < m_nCapacity)
		{
			return m_arrayDXTexture[theTextureID];
		}
		else
		{
			return NULL;
		}
	}
} //namespace GGUI
//-----------------------------------------------------------------------------
#endif //_GGUIDXTextureManager_h_
//-----------------------------------------------------------------------------
