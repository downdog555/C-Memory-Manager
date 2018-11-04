#pragma once
template<typename T>
class ActualWrapper
{
public:

	ActualWrapper(T * actualPointer);

	void UpdateActual(T * actualPointer);

	T * GetActual();

	char* GetActualComp();

	~ActualWrapper();
private:
	T * m_actual;
};

template<typename T>
inline  ActualWrapper<T>::ActualWrapper(T * actualPointer)
{
	m_actual = actualPointer;
}

template<typename T>
inline void   ActualWrapper<T>::UpdateActual(T * actualPointer)
{
	m_actual = actualPointer;
}

template<typename T>
inline T *  ActualWrapper<T>::GetActual()
{
	return m_actual;
}

template<typename T>
inline char *  ActualWrapper<T>::GetActualComp()
{
	T* meow = m_actual;
	return (char*)m_actual;
}

template<typename T>
ActualWrapper<T>::~ActualWrapper()
{
}
