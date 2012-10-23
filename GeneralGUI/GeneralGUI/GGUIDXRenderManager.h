//-----------------------------------------------------------------------------
// (C) oil
// 2012-10-21
//-----------------------------------------------------------------------------
#ifndef _GGUIDXRenderManager_h_
#define _GGUIDXRenderManager_h_
//-----------------------------------------------------------------------------
namespace GGUI
{
	class GGUIWindow;
	class GGUIImageset;
	//-----------------------------------------------------------------------------
	class GGUIDXRenderManager : public SoTSingleton<GGUIDXRenderManager>
	{
	public:
		GGUIDXRenderManager();
		~GGUIDXRenderManager();
		static GGUIDXRenderManager* GetInstance();
		bool InitDXRenderManager();
		void ReleaseDXRenderManager();

		//保存原来的DX设备渲染状态。事后要还原为原来状态。
		void PreRender();
		void AddRnederUnit(const GGUIWindow* pUIWindow);
		void DoRender();
		void PostRender();

	private:
		//顶点数据格式。
		struct stVertexContent
		{
			SoFloat fX, fY, fZ, fRHW;
			SoUInt32 uiColor;
			SoFloat fCoordX, fCoordY;
		};

	private:
		//顶点缓冲区数据会频繁变化，所以一定不能使用D3DPOOL_MANAGED，必须使用D3DPOOL_DEFAULT，
		//当设备丢失时释放资源，设备重置后重新创建。
		IDirect3DVertexBuffer9* m_pDXVertexBuffer;
		//记录DX顶点数组的最大容量。
		SoInt m_nDXVertexCapacity;
		//
		IDirect3DIndexBuffer9* m_pDXIndexBuffer;
		SoInt m_nDXIndexCapacity;
		//
		stVertexContent* m_arrayVertexContent;
		//记录数组中最多存储多少个元素。
		SoInt m_nVertexContentCapacity;
		//记录数组中索引号最大的有效元素的下一个索引号。
		//如果数组中最后一个有效元素的下标为M，则该值为(M+1）。
		SoInt m_nVertexContentIndexEnd;
		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		//保存原来的DX设备渲染状态。绘制过后要还原为原来状态。
		DWORD m_dwOldAlphaBlendEnable;
		DWORD m_dwOldSrcBlend;
		DWORD m_dwOldDestBlend;
		DWORD m_dwOldAlphaArg1;
		DWORD m_dwOldAlphaArg2;
		DWORD m_dwOldAlphaOp;
		//记录本次绘制的纹理贴图。
		ImagesetID m_theTargetImagesetID;
		GGUIImageset* m_pTargetImageset;
		//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	};
	//-----------------------------------------------------------------------------
	GGUIDXRenderManager* GGUIDXRenderManager::GetInstance()
	{
		return GGUIDXRenderManager::Instance();
	}
} //namespace GGUI
//-----------------------------------------------------------------------------
#endif //_GGUIDXRenderManager_h_
//-----------------------------------------------------------------------------
