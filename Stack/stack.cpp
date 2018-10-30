#include "stack.h"

stack::stack()
{
}
/// <summary>
/// Constructor that initilises the stack.
/// </summary>
/// <param name="numberOfBytes"></param>
/// <param name="startLocation"></param>
stack::stack(char * startLocation, unsigned const int numberOfBytes)
{
	m_start = startLocation;
	m_current = startLocation;
	m_endLocation = startLocation+numberOfBytes;
	m_sizeOfStack = numberOfBytes;
}

stack::~stack()
{
}

int stack::memoryRemaining()
{
	int used = &m_current - &m_start;
	int remaining = m_sizeOfStack - used;
	return remaining;
}
