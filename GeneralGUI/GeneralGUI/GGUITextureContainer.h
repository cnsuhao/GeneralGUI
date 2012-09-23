//-----------------------------------------------------------------------------
// GGUI��ͼ��������
// (C) oil
// 2012-09-16
//-----------------------------------------------------------------------------
#ifndef _GGUITextureContainer_h_
#define _GGUITextureContainer_h_
//-----------------------------------------------------------------------------
#include "GGUITextureDefine.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	class GGUITexture;
	//-----------------------------------------------------------------------------
	class GGUITextureContainer : public SoTSingleton<GGUITextureContainer>
	{
	public:
		GGUITextureContainer();
		~GGUITextureContainer();
		static GGUITextureContainer* GetInstance();

		bool InitTextureContainer();
		void ReleaseTextureContainer();

		GGUITexture* CreateUITexture();
		void ReleaseUITexture(TextureID theTextureID);
		GGUITexture* GetUITexture(TextureID theTextureID);
		bool IsOperationByTextureContainer();

	private:
		//һ��TextureID��Ӧ��һ��GGUITexture����
		//��new����������洢ID�������ӳ�䡣TextureIDҲ������������ţ��±꣩��
		GGUITexture** m_pTextureID2Object;
		//��¼���������洢���ٸ�Ԫ�ء�
		SoInt m_nCapacity;
		//��¼������������������ЧԪ�ص���һ�������š�
		//������������һ����ЧԪ�ص��±�ΪM�����ֵΪ(M+1����
		SoInt m_nIndexEnd;
		//��GGUITexture�Ĵ�����ɾ������ֵTextureID�Ȳ���������ͨ������GGUITextureContainer
		//�ĺ����������������������������򱨴�
		//m_bOperationByTextureContainer��ȡֵֻ��SoTrue��SoFalse���֡�
		bool m_bOperationByTextureContainer;
	};
	//-----------------------------------------------------------------------------
	inline GGUITextureContainer* GGUITextureContainer::GetInstance()
	{
		return GGUITextureContainer::Instance();
	}
	//-----------------------------------------------------------------------------
	inline GGUITexture* GGUITextureContainer::GetUITexture(TextureID theTextureID)
	{
		if (theTextureID >= 0 && theTextureID < m_nIndexEnd)
		{
			return m_pTextureID2Object[theTextureID];
		}
		else
		{
			return NULL;
		}
	}
	//-----------------------------------------------------------------------------
	inline bool GGUITextureContainer::IsOperationByTextureContainer()
	{
		return (m_bOperationByTextureContainer == SoTrue);
	}
}
//-----------------------------------------------------------------------------
#endif //_GGUITextureContainer_h_
//-----------------------------------------------------------------------------
