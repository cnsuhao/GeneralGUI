//-----------------------------------------------------------------------------
// (C) oil
// 2012-10-20
//-----------------------------------------------------------------------------
#ifndef _GGUIImagesetManager_h_
#define _GGUIImagesetManager_h_
//-----------------------------------------------------------------------------
namespace GGUI
{
	class GGUIImageset;
	//-----------------------------------------------------------------------------
	class GGUIImagesetManager : public SoTSingleton<GGUIImagesetManager>
	{
	public:
		GGUIImagesetManager();
		~GGUIImagesetManager();
		static GGUIImagesetManager* GetInstance();

		bool InitImagesetManager();
		void ReleaseImagesetManager();

		//�Ӵ����ϼ���ָ����Imageset�ļ���
		//--pszImagesetFile �����ļ�·����
		//--pImagesetID ���Ϊ��Чֵ�����ܷ���ֵΪtrue����false������ѵõ���ImagesetID��ֵ������
		//���ָ����Imageset�ļ��Ѿ����ڣ��Ѿ����أ����򷵻�false��
		bool CreateImagesetByFile(const tchar* pszImagesetFile, ImagesetID* pImagesetID);
		//��ʱ������
		bool CreateImagesetByTextureFile(const tchar* pszTextureFile, const GGUITinyString& strImagesetName, ImagesetID* pImagesetID, ImageRectID* pImageRectID);
		//����һ��GGUIImageset������ImageRect�ĸ���Ϊ0.
		//--strImagesetName ���֡�
		//--pImagesetID ���Ϊ��Чֵ�����ܷ���ֵΪtrue����false������ѵõ���ImagesetID��ֵ������
		//�������ΪstrImagesetName��Imageset�ļ��Ѿ����ڣ��򷵻�false��
		bool CreateImageset(const GGUITinyString& strImagesetName, ImagesetID* pImagesetID);
		//ɾ��һ��GGUIImageset����
		void ReleaseImageset(ImagesetID theImagesetID);
		//��ȡһ��GGUIImageset����
		GGUIImageset* GetImageset(ImagesetID theImagesetID);
		ImagesetID GetImagesetIDByName(const GGUITinyString& strImagesetName);

	private:
		typedef std::map<GGUITinyString, ImagesetID> mapImagesetName2ImagesetID;

	private:
		//GGUIImagesetָ�����顣
		GGUIImageset** m_arrayImageset;
		//��¼���������洢���ٸ�Ԫ�ء�
		SoInt m_nCapacity;
		//��¼������������������ЧԪ�ص���һ�������š�
		//������������һ����ЧԪ�ص��±�ΪM�����ֵΪ(M+1����
		SoInt m_nIndexEnd;
		//ά����ImagesetName��ImagesetID��ӳ�䡣
		mapImagesetName2ImagesetID m_mapImagesetName2ID;

	};
	//-----------------------------------------------------------------------------
	inline GGUIImagesetManager* GGUIImagesetManager::GetInstance()
	{
		return GGUIImagesetManager::Instance();
	}
	//-----------------------------------------------------------------------------
	inline GGUIImageset* GGUIImagesetManager::GetImageset(ImagesetID theImagesetID)
	{
		if (theImagesetID >= 0 && theImagesetID < m_nIndexEnd)
		{
			return m_arrayImageset[theImagesetID];
		}
		else
		{
			return NULL;
		}
	}
	//-----------------------------------------------------------------------------
	inline ImagesetID GGUIImagesetManager::GetImagesetIDByName(const GGUITinyString& strImagesetName)
	{
		mapImagesetName2ImagesetID::iterator it = m_mapImagesetName2ID.find(strImagesetName);
		if (it == m_mapImagesetName2ID.end())
		{
			return Invalid_ImagesetID;
		}
		else
		{
			return (it->second);
		}
	}
} //namespace GGUI
//-----------------------------------------------------------------------------
#endif //_GGUIImagesetManager_h_
//-----------------------------------------------------------------------------
