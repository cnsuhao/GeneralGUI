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
		friend class GGUIWindowManager;
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
		void SetImagesetID(ImagesetID theID);
		void SetImageRectID(ImageRectID theID);
		void SetVisible(bool bVisible);
		virtual void SetEnable(bool bEnable);

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
		ImagesetID GetImagesetID() const;
		ImageRectID GetImageRectID() const;
		DelegateID GetDelegateID() const;
		bool GetVisible() const;
		bool GetEnable() const;

		//�����������ͱ����ڵľ��������ж�����Ƿ����ڱ������ڲ���
		//������λ���жϣ������Ǵ����Ƿ�ɼ����Ƿ񱻽��õȵȡ�
		bool CheckMouseInWindowArea(SoFloat fMousePosX, SoFloat fMousePosY) const;

	protected:
		//�¼���Ӧ�������ں����ڲ���ִ���û�ע���Delegate������
		//���������Ҫ��д��Щ�����Ļ���Ӧ����ִ���Լ����߼����ٵ��û�����¼���Ӧ������
		virtual void OnMouseEnterWindowArea();
		virtual void OnMouseLeaveWindowArea();
		virtual void OnMouseLeftButtonClickDown();
		virtual void OnMouseLeftButtonClickUp();

	protected:
		void SetWindowID(WindowID theID);
		void SetDelegateID(DelegateID theID);
		//�ڻ���֮ǰ����Mesh������Ϣ�����յĸ��¡�
		void PostUpdateWindow();
		//UITexture�Ĳ���
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
		//�����ڵ����͡�
		eWindowType m_eMyWindowType;
		//�����ڵ�ID��
		WindowID m_nMyWindowID;
		//��������һ��UITexture���󣬼�¼����TextureID��
		TextureID m_nMyTextureID;
		//�����ڵ���ͼ��
		ImagesetID m_nMyImagesetID;
		ImageRectID m_nMyImageRectID;
		//�����ڵ�Delegate�¼���Ӧ������ID��
		DelegateID m_nMyDelegateID;
		//��¼�Ƿ���Ҫ����UITexture����
		bool m_bShouldUpdateUITexture;
		//��¼�����Ƿ�ɼ���
		bool m_bVisible;
		//��¼�����Ƿ���á�
		bool m_bEnable;
		//��¼���������Ƿ����ڱ����ڵľ��������ڡ�
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
