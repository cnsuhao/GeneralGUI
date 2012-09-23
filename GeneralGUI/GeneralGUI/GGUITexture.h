//-----------------------------------------------------------------------------
// GGUI�ؼ���ʹ�õ���ͼ
// (C) oil
// 2012-09-02
//-----------------------------------------------------------------------------
#ifndef _GGUITexture_h_
#define _GGUITexture_h_
//-----------------------------------------------------------------------------
#include "GGUITextureDefine.h"
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

	protected:
		static bool CreateIndexBuffer();
		static void ReleaseIndexBuffer();
		void SetTextureID(TextureID newTextureID);

	private:
		bool CreateVertexBuffer();
		void ReleaseVertexBuffer();

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
	};
	//-----------------------------------------------------------------------------
	inline TextureID GGUITexture::GetTextureID()
	{
		return m_nTextureID;
	}
} //namespace GGUI
//-----------------------------------------------------------------------------
#endif //_GGUITexture_h_
//-----------------------------------------------------------------------------
