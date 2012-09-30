//-----------------------------------------------------------------------------
// GGUI窗口基类
// (C) oil
// 2012-09-16
//-----------------------------------------------------------------------------
#ifndef _GGUIWindow_h_
#define _GGUIWindow_h_
//-----------------------------------------------------------------------------
namespace GGUI
{
	class GGUIWindow
	{
		friend class GGUIWindowContainer;
		friend class GGUIInputProcess;
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
		void SetVisible(bool bVisible);

		//获取属性函数
		SoFloat GetPositionX() const;
		SoFloat GetPositionY() const;
		SoFloat GetPositionZ() const;
		SoFloat GetWidth() const;
		SoFloat GetHeight() const;
		void GetColor(SoFloat& fR, SoFloat& fG, SoFloat& fB) const;
		SoFloat GetAlpha() const;
		WindowID GetWindowID() const;
		TextureID GetTextureID() const;
		bool GetVisible() const;

		//根据鼠标坐标和本窗口的矩形区域，判断鼠标是否落在本窗口内部。
		bool CheckMouseInWindowArea(SoFloat fMousePosX, SoFloat fMousePosY) const;

	protected:
		void SetWindowID(WindowID theID);
		void OnMouseEnterWindowArea();
		void OnMouseLeaveWindowArea();

		//UITexture的操作
		void CreateUITexture();
		void ReleaseUITexture();
		void UpdateUITexture();

	protected:
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
		bool m_bShouldUpdateUITexture;
		//记录窗口是否可见。
		bool m_bVisible;

	};
	//-----------------------------------------------------------------------------
	inline bool GGUIWindow::CheckMouseInWindowArea(SoFloat fMousePosX, SoFloat fMousePosY) const
	{
		if (fMousePosX > m_fPositionX && fMousePosX < m_fPositionX + m_fWidth)
		{
			if (fMousePosY > m_fPositionY && fMousePosY < m_fPositionY + m_fHeight)
			{
				return true;
			}
		}
		return false;
	}
}
//-----------------------------------------------------------------------------
#endif //_GGUIWindow_h_
//-----------------------------------------------------------------------------
