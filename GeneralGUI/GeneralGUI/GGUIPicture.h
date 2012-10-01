//-----------------------------------------------------------------------------
// GGUI Picture�ؼ�
// (C) oil
// 2012-10-01
//-----------------------------------------------------------------------------
#ifndef _GGUIPicture_h_
#define _GGUIPicture_h_
//-----------------------------------------------------------------------------
#include "GGUIWindow.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	class GGUIPicture : public GGUIWindow
	{
	public:
		enum ePictureShow
		{
			PictureShow_Auto, //����Ӧ��ά��ͼƬ�Ŀ�߱�����ҪôͼƬ��ȵ��ڴ��ڿ�ȣ�ҪôͼƬ�߶ȵ��ڴ��ڸ߶�
			PictureShow_Stretch, //���죬ʹͼƬ�������ڵ�������������
		};

	public:
		GGUIPicture();
		virtual ~GGUIPicture();

		void SetPictureShowType(ePictureShow theShowType);
		ePictureShow GetPictureShowType();

	protected:
		virtual void UpdateUITexture();

	protected:
		ePictureShow m_ePictureShow;

	};
}
//-----------------------------------------------------------------------------
#endif //_GGUIPicture_h_
//-----------------------------------------------------------------------------
