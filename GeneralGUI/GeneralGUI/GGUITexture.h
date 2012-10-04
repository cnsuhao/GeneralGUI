//-----------------------------------------------------------------------------
// GGUI�ؼ���ʹ�õ���ͼ
// (C) oil
// 2012-09-02
//-----------------------------------------------------------------------------
#ifndef _GGUITexture_h_
#define _GGUITexture_h_
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

		//������ͼ�ļ��������ڲ�����ɾ�����е�IDirect3DTexture9�����ٴ����µġ�
		bool LoadTexture(const tchar* pFileName);
		//�����Ѿ����غõ���ͼ�ļ��������ڲ�����ɾ�����е�IDirect3DTexture9����
		void SetTexture(IDirect3DTexture9* pNewTexture);
		//���¶��㻺������
		void UpdateVertexBuffer(SoFloat fX, SoFloat fY, SoFloat fZ, SoFloat fWidth, SoFloat fHeight, SoUInt32 uiColor);
		//���Ƶ���ǰ�ĺ�̨��������
		void RenderTexture();

		//
		TextureID GetTextureID();
		IDirect3DTexture9* GetDXTexture();
		//��ȡͼƬԴ�ļ��Ŀ�ߡ�
		SoInt GetSourceWidth();
		SoInt GetSourceHeight();

	protected:
		static bool CreateIndexBuffer();
		static void ReleaseIndexBuffer();
		void SetTextureID(TextureID newTextureID);

	private:
		bool CreateVertexBuffer();
		void ReleaseVertexBuffer();
		//���õ��µ�IDirect3DTexture9����󣬻�ȡ��Texture��һЩ������
		void RefreshTextureParam();

	private:
		//�������ݸ�ʽ��
		struct SVertexType
		{
			SoFloat fX, fY, fZ, fRHW;
			SoUInt32 uiColor;
			SoFloat fCoordX, fCoordY;
		};

	private:
		//�̶������ʽ��
		static SoUInt32 ms_TextureFVF;
		//Texture��ʹ�õ��������塣���������������ǲ���仯�ģ�����ʹ��D3DPOOL_MANAGED��
		//���й��ڴ�صĺô����豸��ʧ�󲻱����´�����
		static IDirect3DIndexBuffer9* ms_pTextureIB;

	private:
		//���豸��ʧʱ�����ݴ���Textureʱ�Ƿ�ʹ����D3DPOOL_MANAGED������������Ҫ
		//���¼��ػ�����Ҫ���¼��ء�
		IDirect3DTexture9* m_pTexture;
		//���㻺�������ݻ�Ƶ���仯������һ������ʹ��D3DPOOL_MANAGED������ʹ��D3DPOOL_DEFAULT��
		//���豸��ʧʱ�ͷ���Դ���豸���ú����´�����
		IDirect3DVertexBuffer9* m_pVertex;
		//ÿ��Texture������һ��ID��Invalid_TextureIDΪID����Чֵ��
		TextureID m_nTextureID;
		//Texture�Ŀ�ߡ�
		SoInt m_nWidth;
		SoInt m_nHeight;
		//��¼Textureʹ�õ��ڴ����͡�
		D3DPOOL m_eThePool;

	};
	//-----------------------------------------------------------------------------
	inline TextureID GGUITexture::GetTextureID()
	{
		return m_nTextureID;
	}
	//-----------------------------------------------------------------------------
	inline IDirect3DTexture9* GGUITexture::GetDXTexture()
	{
		return m_pTexture;
	}
	//-----------------------------------------------------------------------------
	inline SoInt GGUITexture::GetSourceWidth()
	{
		return m_nWidth;
	}
	//-----------------------------------------------------------------------------
	inline SoInt GGUITexture::GetSourceHeight()
	{
		return m_nHeight;
	}
} //namespace GGUI
//-----------------------------------------------------------------------------
#endif //_GGUITexture_h_
//-----------------------------------------------------------------------------
