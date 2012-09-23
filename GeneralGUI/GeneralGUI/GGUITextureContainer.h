//-----------------------------------------------------------------------------
// GGUI贴图的容器类
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
		//一个TextureID对应着一个GGUITexture对象。
		//用new出来的数组存储ID到对象的映射。TextureID也即数组的索引号（下标）。
		GGUITexture** m_pTextureID2Object;
		//记录数组中最多存储多少个元素。
		SoInt m_nCapacity;
		//记录数组中索引号最大的有效元素的下一个索引号。
		//如果数组中最后一个有效元素的下标为M，则该值为(M+1）。
		SoInt m_nIndexEnd;
		//对GGUITexture的创建，删除，赋值TextureID等操作，必须通过调用GGUITextureContainer
		//的函数来操作；如果不按照这个规则，则报错。
		//m_bOperationByTextureContainer的取值只有SoTrue和SoFalse两种。
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
