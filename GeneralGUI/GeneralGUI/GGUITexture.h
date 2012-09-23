//-----------------------------------------------------------------------------
// GGUI控件所使用的贴图
// (C) oil
// 2012-09-02
//-----------------------------------------------------------------------------
#ifndef _GGUITexture_h_
#define _GGUITexture_h_
//-----------------------------------------------------------------------------
#include "GGUITextureDefine.h"
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

	protected:
		static bool CreateIndexBuffer();
		static void ReleaseIndexBuffer();
		void SetTextureID(TextureID newTextureID);

	private:
		bool CreateVertexBuffer();
		void ReleaseVertexBuffer();

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
	};
	//-----------------------------------------------------------------------------
	inline TextureID GGUITexture::GetTextureID()
	{
		return m_nTextureID;
	}
} //namespace GGUI
//-----------------------------------------------------------------------------
#endif //_GGUITexture_h_
//-----------------------------------------------------------------------------
