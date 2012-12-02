//-----------------------------------------------------------------------------
// (C) oil
// 2012-12-02
//-----------------------------------------------------------------------------
#ifndef _GGUILog_h_
#define _GGUILog_h_
//-----------------------------------------------------------------------------
namespace GGUI
{
	class GGUILog
	{
	public:
		GGUILog();
		virtual ~GGUILog();

		virtual bool InitLog(const tchar* pszDiskFileName, bool bFlushImmediately);
		//
		void OutputDebug(const tchar* pFormat, ...);
		void OutputWaring(const tchar* pFormat, ...);
		void OutputError(const tchar* pFormat, ...);

	protected:
		void AddLogHead(tchar* pType);
		//�򿪴�����ָ����log�ļ���
		//����ļ����ڣ������ļ�β������д��log��Ϣ��
		//����ļ������ڣ����½�����ļ���
		bool OpenDiskFile(const tchar* pszDiskFileName);
		//�رմ����ļ���
		void CloseDiskFile();

	protected:
		FILE* m_fp;
		bool m_bFlushImmediately;
	};
} //namespace GGUI
//-----------------------------------------------------------------------------
#endif //_GGUILog_h_
//-----------------------------------------------------------------------------
