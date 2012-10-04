//-----------------------------------------------------------------------------
// GGUI控件所使用的贴图
// (C) oil
// 2012-09-02
//-----------------------------------------------------------------------------
#ifndef _GGUITexture_h_
#define _GGUITexture_h_
//-----------------------------------------------------------------------------
namespace GGUI
{
	//-----------------------------------------------------------------------------
	class GGUITexture
	{
		friend class GGUITextureContainer;
	public:
		GGUITexture();
		~GGUITexture();

		//加载贴图文件。函数内部会先删除现有的IDirect3DTexture9对象，再创建新的。
		bool LoadTexture(const tchar* pFileName);
		//设置已经加载好的贴图文件。函数内部会先删除现有的IDirect3DTexture9对象。
		void SetTexture(IDirect3DTexture9* pNewTexture);
		//更新顶点缓冲区。
		void UpdateVertexBuffer(SoFloat fX, SoFloat fY, SoFloat fZ, SoFloat fWidth, SoFloat fHeight, SoUInt32 uiColor);
		//绘制到当前的后台缓冲区。
		void RenderTexture();

		//
		TextureID GetTextureID();
		IDirect3DTexture9* GetDXTexture();
		//获取图片源文件的宽高。
		SoInt GetSourceWidth();
		SoInt GetSourceHeight();

	protected:
		static bool CreateIndexBuffer();
		static void ReleaseIndexBuffer();
		void SetTextureID(TextureID newTextureID);

	private:
		bool CreateVertexBuffer();
		void ReleaseVertexBuffer();
		//当得到新的IDirect3DTexture9对象后，获取新Texture的一些参数。
		void RefreshTextureParam();

	private:
		//顶点数据格式。
		struct SVertexType
		{
			SoFloat fX, fY, fZ, fRHW;
			SoUInt32 uiColor;
			SoFloat fCoordX, fCoordY;
		};

	private:
		//固定顶点格式。
		static SoUInt32 ms_TextureFVF;
		//Texture所使用的索引缓冲。索引缓冲区数据是不会变化的，所以使用D3DPOOL_MANAGED，
		//用托管内存池的好处是设备丢失后不必重新创建。
		static IDirect3DIndexBuffer9* ms_pTextureIB;

	private:
		//当设备丢失时，根据创建Texture时是否使用了D3DPOOL_MANAGED，来决定不需要
		//重新加载还是需要重新加载。
		IDirect3DTexture9* m_pTexture;
		//顶点缓冲区数据会频繁变化，所以一定不能使用D3DPOOL_MANAGED，必须使用D3DPOOL_DEFAULT，
		//当设备丢失时释放资源，设备重置后重新创建。
		IDirect3DVertexBuffer9* m_pVertex;
		//每个Texture对象都有一个ID；Invalid_TextureID为ID的无效值。
		TextureID m_nTextureID;
		//Texture的宽高。
		SoInt m_nWidth;
		SoInt m_nHeight;
		//记录Texture使用的内存类型。
		D3DPOOL m_eThePool;

	};
	//-----------------------------------------------------------------------------
	inline TextureID GGUITexture::GetTextureID()
	{
		return m_nTextureID;
	}
	//-----------------------------------------------------------------------------
	inline IDirect3DTexture9* GGUITexture::GetDXTexture()
	{
		return m_pTexture;
	}
	//-----------------------------------------------------------------------------
	inline SoInt GGUITexture::GetSourceWidth()
	{
		return m_nWidth;
	}
	//-----------------------------------------------------------------------------
	inline SoInt GGUITexture::GetSourceHeight()
	{
		return m_nHeight;
	}
} //namespace GGUI
//-----------------------------------------------------------------------------
#endif //_GGUITexture_h_
//-----------------------------------------------------------------------------
