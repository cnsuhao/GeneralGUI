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
		//用户创建GGUILog对象（或GGUILog派生类的对象），把对象指针通过
		//SetInstance()传递给本类。
		static void SetInstance(GGUILog* pLog);
		static GGUILog* GetInstance();

		//初始化函数。
		//--pszDiskFileName 把log信息输出到指定的磁盘文件，磁盘文件不存在则创建，
		//                  如果存在则在末尾写入log；值为NULL，表示不输出到磁盘文件。
		//--bOutputDebugString 是否把log信息输出到VS的debug窗口。
		//--bFlushImmediately 是否每次输出log后立即执行flush操作。
		virtual bool InitLog(const tchar* pszDiskFileName, bool bOutputDebugString, bool bFlushImmediately);
		//
		virtual void OutputDebug(const tchar* pFormat, ...);
		virtual void OutputWaring(const tchar* pFormat, ...);
		virtual void OutputError(const tchar* pFormat, ...);

	protected:
		virtual void AddLogHead(tchar* pType);
		virtual void AddLogBody(const tchar* pFormat, const va_list& kVaList);
		//打开磁盘上指定的log文件。
		//如果文件存在，则在文件尾部继续写入log信息；
		//如果文件不存在，则新建这个文件。
		virtual bool OpenDiskFile(const tchar* pszDiskFileName);
		//关闭磁盘文件。
		virtual void CloseDiskFile();

	protected:
		static GGUILog* ms_pInstance;
	protected:
		FILE* m_fp;
		bool m_bOutputDebugString;
		bool m_bFlushImmediately;
	};
	//-----------------------------------------------------------------------------
	#define LOG_DEBUG if(GGUILog::GetInstance()) GGUILog::GetInstance()->OutputDebug
	#define LOG_WARING if(GGUILog::GetInstance()) GGUILog::GetInstance()->OutputWaring
	#define LOG_ERROR if(GGUILog::GetInstance()) GGUILog::GetInstance()->OutputError
	//-----------------------------------------------------------------------------
} //namespace GGUI
//-----------------------------------------------------------------------------
#endif //_GGUILog_h_
//-----------------------------------------------------------------------------
