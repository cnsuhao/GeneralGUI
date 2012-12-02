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
		//打开磁盘上指定的log文件。
		//如果文件存在，则在文件尾部继续写入log信息；
		//如果文件不存在，则新建这个文件。
		bool OpenDiskFile(const tchar* pszDiskFileName);
		//关闭磁盘文件。
		void CloseDiskFile();

	protected:
		FILE* m_fp;
		bool m_bFlushImmediately;
	};
} //namespace GGUI
//-----------------------------------------------------------------------------
#endif //_GGUILog_h_
//-----------------------------------------------------------------------------
