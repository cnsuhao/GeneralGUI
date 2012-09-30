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
		bool InitUISystem(IDirect3DDevice9* pDevice, SoFloat fScreenWidth, SoFloat fScreenHeight);
		//释放GGUI系统。
		void ReleaseUISystem();
		//获取D3D设备指针。
		IDirect3DDevice9* GetD3DDevice();

		//更新。
		void UpdateGGUI(SoFloat fFrameTime);
		//绘制。
		void RenderGGUI();

		//注入一个键盘按键事件。
		//返回ture表示这个按键事件被本系统响应并处理了；
		//返回false表示本系统不关心并没有处理这个事件。
		bool InjectKeyEvent(eInputEvent theEvent, eKeyButton theKey);
		//注入一个鼠标事件。
		//返回ture表示这个事件被本系统响应并处理了；
		//返回false表示本系统不关心并没有处理这个事件。
		bool InjectMouseEvent(eInputEvent theEvent, eMouseButton theButton, SoFloat fParamA, SoFloat fParamB);

	private:


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
