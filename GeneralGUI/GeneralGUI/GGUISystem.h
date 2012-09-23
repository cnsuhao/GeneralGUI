//-----------------------------------------------------------------------------
// GGUI系统类
// (C) oil
// 2012-09-08
//-----------------------------------------------------------------------------
#ifndef _GGUISystem_h_
#define _GGUISystem_h_
//-----------------------------------------------------------------------------
namespace GGUI
{
	class GGUISystem : public SoTSingleton<GGUISystem>
	{
	public:
		GGUISystem();
		~GGUISystem();
		static GGUISystem* GetInstance();

		//初始化GGUI系统，创建必要的组件和资源。
		bool InitUISystem(IDirect3DDevice9* pDevice);
		//释放GGUI系统。
		void ReleaseUISystem();

		//获取D3D设备指针。
		IDirect3DDevice9* GetD3DDevice();

	private:
		IDirect3DDevice9* m_pD3DDevice;
	};
	//-----------------------------------------------------------------------------
	inline GGUISystem* GGUISystem::GetInstance()
	{
		return GGUISystem::Instance();
	}
	//-----------------------------------------------------------------------------
	inline IDirect3DDevice9* GGUISystem::GetD3DDevice()
	{
		return m_pD3DDevice;
	}
	//-----------------------------------------------------------------------------
} //namespace GGUI
//-----------------------------------------------------------------------------
#endif //_GGUISystem_h_
//-----------------------------------------------------------------------------
