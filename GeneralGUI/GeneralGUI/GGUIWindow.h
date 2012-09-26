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

		//��ȡ���Ժ���
		SoFloat GetPositionX();
		SoFloat GetPositionY();
		SoFloat GetPositionZ();
		SoFloat GetWidth();
		SoFloat GetHeight();
		void GetColor(SoFloat& fR, SoFloat& fG, SoFloat& fB);
		SoFloat GetAlpha();
		WindowID GetWindowID();
		TextureID GetTextureID();

		//����������꣬�ж�����Ƿ����ڱ������ڲ���
		bool IsContainMouse(SoFloat fMousePosX, SoFloat fMousePosY);

	protected:
		void SetWindowID(WindowID theID);

		//UITexture�Ĳ���
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
		//�����ڵ�ID��
		WindowID m_nMyWindowID;
		//��������һ��UITexture���󣬼�¼����TextureID��
		TextureID m_nMyTextureID;
		//��¼�Ƿ���Ҫ����UITexture����
		//ֻ��SoTrue��SoFalse����״̬��
		SoBool m_bShouldUpdateUITexture;
	};
	//-----------------------------------------------------------------------------
	inline bool GGUIWindow::IsContainMouse(SoFloat fMousePosX, SoFloat fMousePosY)
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
