//-----------------------------------------------------------------------------
// GGUI窗口基类
// (C) oil
// 2012-09-16
//-----------------------------------------------------------------------------
#ifndef _GGUIWindow_h_
#define _GGUIWindow_h_
//-----------------------------------------------------------------------------
#include "GGUIWindowDefine.h"
#include "GGUITextureDefine.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	class GGUIWindow
	{
		friend class GGUIWindowContainer;
	public:
		GGUIWindow();
		virtual ~GGUIWindow();

		//更新函数
		void UpdateWindow(SoFloat fFrameTime);
		//绘制函数
		void RenderWindow();

		//设置属性函数
		void SetPositionX(SoFloat fPosX);
		void SetPositionY(SoFloat fPosY);
		void SetPositionZ(SoFloat fPosZ);
		void SetWidth(SoFloat fWidth);
		void SetHeight(SoFloat fHeight);
		void SetColor(SoFloat fR, SoFloat fG, SoFloat fB);
		void SetAlpha(SoFloat fAlpha);
		void SetImage(IDirect3DTexture9* pTexture);
		bool SetImageByFileName(const tchar* pFileName);

		//获取属性函数
		SoFloat GetPositionX();
		SoFloat GetPositionY();
		SoFloat GetPositionZ();
		SoFloat GetWidth();
		SoFloat GetHeight();
		void GetColor(SoFloat& fR, SoFloat& fG, SoFloat& fB);
		SoFloat GetAlpha();
		WindowID GetWindowID();
		TextureID GetTextureID();

	protected:
		void SetWindowID(WindowID theID);

		//UITexture的操作
		void CreateUITexture();
		void ReleaseUITexture();
		void UpdateUITexture();

	private:
		SoFloat m_fPositionX;
		SoFloat m_fPositionY;
		SoFloat m_fPositionZ;
		SoFloat m_fWidth;
		SoFloat m_fHeight;
		SoFloat m_fColorR;
		SoFloat m_fColorG;
		SoFloat m_fColorB;
		SoFloat m_fColorA;
		//本窗口的ID。
		WindowID m_nMyWindowID;
		//本窗口有一个UITexture对象，记录它的TextureID。
		TextureID m_nMyTextureID;
		//记录是否需要更新UITexture对象。
		//只有SoTrue和SoFalse两种状态。
		SoBool m_bShouldUpdateUITexture;
	};
}
//-----------------------------------------------------------------------------
#endif //_GGUIWindow_h_
//-----------------------------------------------------------------------------
