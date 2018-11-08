#include "ActualWrapper.h"
/// <summary>
/// default constructor
/// </summary>
ActualWrapper::ActualWrapper()
{
}
/// <summary>
/// Correct Constructor
/// </summary>
/// <param name="actualPointer">the pointer of the object</param>
ActualWrapper::ActualWrapper(char * actualPointer)
{

	m_actual = actualPointer;
}
/// <summary>
/// returns a pointer to this wrapper
/// </summary>
/// <returns>a pointer to this wrapper</returns>
ActualWrapper * ActualWrapper::GetWrapper()
{
	return this;
}
/// <summary>
/// updates the actual pointer
/// </summary>
/// <param name="actualPointer">new pointer</param>
void ActualWrapper::UpdateActual(char * actualPointer)
{
	m_actual = actualPointer;
}
/// <summary>
/// gets the actual char*
/// </summary>
/// <returns>the actual char*</returns>
char * ActualWrapper::GetActual()
{
	return m_actual;
}
/// <summary>
/// Depricated
/// </summary>
/// <returns></returns>
char * ActualWrapper::GetActualComp()
{
	return m_actual;
}
/// <summary>
/// destructor
/// </summary>
ActualWrapper::~ActualWrapper()
{
}
