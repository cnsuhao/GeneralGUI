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
		//--pDXTextureID 如果为有效值，则把新的DXTextureID赋值给它。
		bool LoadTextureFromDisk(const tchar* pszFileName, DXTextureID* pDXTextureID);
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
