#include "ActualWrapper.h"

ActualWrapper::ActualWrapper()
{
}

ActualWrapper::ActualWrapper(char * actualPointer)
{

	m_actual = actualPointer;
}

ActualWrapper * ActualWrapper::GetWrapper()
{
	return this;
}

void ActualWrapper::UpdateActual(char * actualPointer)
{
	m_actual = actualPointer;
}

char * ActualWrapper::GetActual()
{
	return m_actual;
}

char * ActualWrapper::GetActualComp()
{
	return m_actual;
}

ActualWrapper::~ActualWrapper()
{
}
