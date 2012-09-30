//-----------------------------------------------------------------------------
// GGUI���ڻ���
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

		//���º���
		void UpdateWindow(SoFloat fFrameTime);
		//���ƺ���
		void RenderWindow();

		//�������Ժ���
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

		//��ȡ���Ժ���
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

		//�����������ͱ����ڵľ��������ж�����Ƿ����ڱ������ڲ���
		bool CheckMouseInWindowArea(SoFloat fMousePosX, SoFloat fMousePosY) const;

	protected:
		void SetWindowID(WindowID theID);
		void OnMouseEnterWindowArea();
		void OnMouseLeaveWindowArea();

		//UITexture�Ĳ���
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
		//�����ڵ�ID��
		WindowID m_nMyWindowID;
		//��������һ��UITexture���󣬼�¼����TextureID��
		TextureID m_nMyTextureID;
		//��¼�Ƿ���Ҫ����UITexture����
		bool m_bShouldUpdateUITexture;
		//��¼�����Ƿ�ɼ���
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
