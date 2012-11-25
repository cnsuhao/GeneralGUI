//-----------------------------------------------------------------------------
// (C) oil
// 2012-11-25
//-----------------------------------------------------------------------------
#ifndef _GGUIArray_h_
#define _GGUIArray_h_
//-----------------------------------------------------------------------------
namespace GGUI
{
	//-----------------------------------------------------------------------------
	template <class Temp>
	class GGUIArray
	{
	public:
		//--invalidValue 数组元素的无效值是多少。当执行“移除一个元素”操作时，
		//               本类只是把这个元素置为无效值，并且这个元素再也不会被置为有效值，
		//               在数组中造成一个空洞；这个操作没有释放内存也没有改变数组容量。
		//--nInitCapacity 数组的初始容量是多大。
		GGUIArray(const Temp& invalidValue, SoInt nInitCapacity);
		~GGUIArray();

		//增加一个有效元素。
		void AddElement(const Temp& theElement);
		//移除一个元素，把这个元素置为无效值。
		void RemoveElement(SoInt nIndex);
		//获取一个元素。
		Temp& GetElement(SoInt nIndex);
		//获取写入指针的索引号。
		SoInt GetWriteIndex();

	private:
		//记录数组元素的无效值。
		Temp m_theInvalidValue;
		//数组。
		Temp* m_Array;
		//记录数组的容量。
		SoInt m_nCapacity;
		//记录执行“增加一个元素”操作时的写入指针，新增加的元素赋值给这个索引号的元素。
		SoInt m_nWriteIndex;
	};
	//-----------------------------------------------------------------------------
	template <class Temp>
	inline GGUIArray<Temp>::GGUIArray(const Temp& invalidValue, SoInt nInitCapacity)
	:m_theInvalidValue(invalidValue)
	,m_Array(0)
	,m_nCapacity(nInitCapacity)
	,m_nWriteIndex(0)
	{
		m_Array = new Temp[m_nCapacity];
		for (SoInt i=0; i<m_nCapacity; ++i)
		{
			m_Array[i] = m_theInvalidValue;
		}
	}
	//-----------------------------------------------------------------------------
	template <class Temp>
	inline GGUIArray<Temp>::~GGUIArray()
	{
		if (m_Array)
		{
			delete [] m_Array;
			m_Array = 0;
		}
	}
	//-----------------------------------------------------------------------------
	template <class Temp>
	inline void GGUIArray<Temp>::AddElement(const Temp& theElement)
	{
		if (m_nWriteIndex >= m_nCapacity)
		{
			//数组容量不够了，则把容量扩大到原来的2倍。
			SoUInt sizeOfOldArray = sizeof(Temp) * m_nCapacity;
			m_nCapacity *= 2;
			SoUInt sizeOfNewArray = sizeof(Temp) * m_nCapacity;
			Temp* pNewArray = new Temp[m_nCapacity];
			for (SoInt i=0; i<m_nCapacity; ++i)
			{
				pNewArray[i] = m_theInvalidValue;
			}
			memcpy_s(pNewArray, sizeOfNewArray, m_Array, sizeOfOldArray);
			delete [] m_Array;
			m_Array = pNewArray;
		}
		m_Array[m_nWriteIndex] = theElement;
		++m_nWriteIndex;
	}
	//-----------------------------------------------------------------------------
	template <class Temp>
	inline void GGUIArray<Temp>::RemoveElement(SoInt nIndex)
	{
		if (nIndex>=0 && nIndex<m_nWriteIndex)
		{
			m_Array[nIndex] = m_theInvalidValue;
		}
	}
	//-----------------------------------------------------------------------------
	template <class Temp>
	inline Temp& GGUIArray<Temp>::GetElement(SoInt nIndex)
	{
		if (nIndex>=0 && nIndex<m_nWriteIndex)
		{
			return m_Array[nIndex];
		}
		else
		{
			return m_theInvalidValue;
		}
	}
	//-----------------------------------------------------------------------------
	template <class Temp>
	inline SoInt GGUIArray<Temp>::GetWriteIndex()
	{
		return m_nWriteIndex;
	}
} //namespace GGUI
//-----------------------------------------------------------------------------
#endif //_GGUIArray_h_
//-----------------------------------------------------------------------------
