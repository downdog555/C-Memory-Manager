#include "ActualWrapper.h"

ActualWrapper::ActualWrapper(char * actualPointer)
{
	m_actual = actualPointer;
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
