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
	class GGUIDXTextureManager
	{
	public:
		GGUIDXTextureManager();
		~GGUIDXTextureManager();
		static GGUIDXTextureManager* GetInstance();
		bool InitDXTextureManager();

		//从磁盘上加载贴图文件。
		//--pFileName 磁盘上的文件名。
		//如果加载成功，返回新IDirect3DTexture9的DXTextureID；
		//如果加载失败，返回Invalid_DXTextureID。
		DXTextureID LoadTextureFromDisk(const tchar* pszFileName);
		//删除一个贴图。
		void ReleaseDXTexture(DXTextureID theTextureID);
		//获取DXTexture指针。
		IDirect3DTexture9* GetDXTexture(DXTextureID theTextureID);

	private:
		static GGUIDXTextureManager* ms_pInstance;
	private:
		GGUIArray<IDirect3DTexture9*> m_arrayDXTexture;

	};
	//-----------------------------------------------------------------------------
	inline GGUIDXTextureManager* GGUIDXTextureManager::GetInstance()
	{
		return ms_pInstance;
	}
	//-----------------------------------------------------------------------------
	inline IDirect3DTexture9* GGUIDXTextureManager::GetDXTexture(DXTextureID theTextureID)
	{
		return m_arrayDXTexture.GetElement(theTextureID);
	}
} //namespace GGUI
//-----------------------------------------------------------------------------
#endif //_GGUIDXTextureManager_h_
//-----------------------------------------------------------------------------
