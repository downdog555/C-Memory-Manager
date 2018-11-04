#pragma once

class ActualWrapper
{
public:
	template<typename T>
	ActualWrapper(T * actualPointer);
	template<typename T>
	void UpdateActual(T * actualPointer);
	template<typename T>
	T * GetActual();
	~ActualWrapper();
private:
	template<typename T>
	T * m_actual;
};

template<typename T>
inline ActualWrapper::ActualWrapper(T * actualPointer)
{
	m_actual = actualPointer;
}

template<typename T>
inline void ActualWrapper::UpdateActual(T * actualPointer)
{
	m_actual = actualPointer;
}

template<typename T>
inline T * ActualWrapper::GetActual()
{
	return m_actual;
}


 ActualWrapper::~ActualWrapper()
{
}
