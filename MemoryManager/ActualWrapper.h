#pragma once
template<typename T>
class ActualWrapper
{
public:
	ActualWrapper(T * actualPointer);
	void UpdateActual(char * actualPointer);
	T * GetActual();
	~ActualWrapper();
private:
	T * m_actual;
};

template<typename T>
inline ActualWrapper<T>::ActualWrapper(T * actualPointer)
{
	m_actual = actualPointer;
}

template<typename T>
inline void ActualWrapper<T>::UpdateActual(char * actualPointer)
{
	m_actual = (T*)actualPointer;
}

template<typename T>
inline T * ActualWrapper<T>::GetActual()
{
	return m_actual;
}

template<typename T>
inline ActualWrapper<T>::~ActualWrapper()
{
}
