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
		friend class GGUIWindowManager;
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
		void SetImagesetID(ImagesetID theID);
		void SetImageRectID(ImageRectID theID);
		void SetVisible(bool bVisible);
		virtual void SetEnable(bool bEnable);

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
		ImagesetID GetImagesetID() const;
		ImageRectID GetImageRectID() const;
		DelegateID GetDelegateID() const;
		bool GetVisible() const;
		bool GetEnable() const;

		//根据鼠标坐标和本窗口的矩形区域，判断鼠标是否落在本窗口内部。
		//单纯的位置判断，不考虑窗口是否可见，是否被禁用等等。
		bool CheckMouseInWindowArea(SoFloat fMousePosX, SoFloat fMousePosY) const;

	protected:
		//事件响应函数。在函数内部会执行用户注册的Delegate函数。
		//派生类如果要重写这些函数的话，应该先执行自己的逻辑，再调用基类的事件响应函数。
		virtual void OnMouseEnterWindowArea();
		virtual void OnMouseLeaveWindowArea();
		virtual void OnMouseLeftButtonClickDown();
		virtual void OnMouseLeftButtonClickUp();

	protected:
		void SetWindowID(WindowID theID);
		void SetDelegateID(DelegateID theID);
		//在绘制之前，对Mesh顶点信息做最终的更新。
		void PostUpdateWindow();
		//UITexture的操作
		void CreateUITexture();
		void ReleaseUITexture();
		virtual void UpdateUITexture();

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
		//本窗口的类型。
		eWindowType m_eMyWindowType;
		//本窗口的ID。
		WindowID m_nMyWindowID;
		//本窗口有一个UITexture对象，记录它的TextureID。
		TextureID m_nMyTextureID;
		//本窗口的贴图。
		ImagesetID m_nMyImagesetID;
		ImageRectID m_nMyImageRectID;
		//本窗口的Delegate事件响应函数的ID。
		DelegateID m_nMyDelegateID;
		//记录是否需要更新UITexture对象。
		bool m_bShouldUpdateUITexture;
		//记录窗口是否可见。
		bool m_bVisible;
		//记录窗口是否可用。
		bool m_bEnable;
		//记录鼠标的坐标是否落在本窗口的矩形区域内。
		bool m_bMouseInWindowArea;

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
