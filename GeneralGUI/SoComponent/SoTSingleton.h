//-----------------------------------------------------------------------------
// 单实例模板类
// (C) oil
// 2008-09-14
//-----------------------------------------------------------------------------
#ifndef _SoTSingleton_h_
#define _SoTSingleton_h_
//-----------------------------------------------------------------------------
namespace SoComponent
{
	template <class T>
	class SoTSingleton
	{
	public:
		static T* CreateInstance(void);
		static void ReleaseInstance(void);
		static T* Instance(void);
	private:
		static T* ms_pSingleton;
	};
	//-----------------------------------------------------------------------------
	template <class T>
	T*  SoTSingleton<T>::ms_pSingleton = 0;
	//-----------------------------------------------------------------------------
	template <class T>
	inline T* SoTSingleton<T>::CreateInstance(void)
	{
		if( 0!= ms_pSingleton)
			delete ms_pSingleton;

		ms_pSingleton = new T;
		return ms_pSingleton;
	}
	//-----------------------------------------------------------------------------
	template <class T>
	inline void SoTSingleton<T>::ReleaseInstance(void)
	{
		if( 0!= ms_pSingleton)
		{
			delete ms_pSingleton;
			ms_pSingleton = 0;
		}
	}
	//-----------------------------------------------------------------------------
	template <class T>
	inline T* SoTSingleton<T>::Instance(void)
	{
		return ms_pSingleton;
	}
	//-----------------------------------------------------------------------------
} //namespace SoComponent
//-----------------------------------------------------------------------------
#endif //_SoTSingleton_h_
//-----------------------------------------------------------------------------
