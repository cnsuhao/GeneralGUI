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
		//--invalidValue ����Ԫ�ص���Чֵ�Ƕ��١���ִ�С��Ƴ�һ��Ԫ�ء�����ʱ��
		//               ����ֻ�ǰ����Ԫ����Ϊ��Чֵ���������Ԫ����Ҳ���ᱻ��Ϊ��Чֵ��
		//               �����������һ���ն����������û���ͷ��ڴ�Ҳû�иı�����������
		//--nInitCapacity ����ĳ�ʼ�����Ƕ��
		GGUIArray(const Temp& invalidValue, SoInt nInitCapacity);
		~GGUIArray();

		//����һ����ЧԪ�ء�
		void AddElement(const Temp& theElement);
		//�Ƴ�һ��Ԫ�أ������Ԫ����Ϊ��Чֵ��
		void RemoveElement(SoInt nIndex);
		//��ȡһ��Ԫ�ء�
		Temp& GetElement(SoInt nIndex);
		//��ȡд��ָ��������š�
		SoInt GetWriteIndex();

	private:
		//��¼����Ԫ�ص���Чֵ��
		Temp m_theInvalidValue;
		//���顣
		Temp* m_Array;
		//��¼�����������
		SoInt m_nCapacity;
		//��¼ִ�С�����һ��Ԫ�ء�����ʱ��д��ָ�룬�����ӵ�Ԫ�ظ�ֵ����������ŵ�Ԫ�ء�
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
			//�������������ˣ������������ԭ����2����
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
