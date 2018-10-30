#include "doubleStack.h"



doubleStack::doubleStack()
{
}

doubleStack::doubleStack(char * startLocation, unsigned const int numberOfBytes)
{
	m_start = startLocation;
	m_currentFront = startLocation;
	m_endLocation = startLocation + numberOfBytes;
	m_currentBack = m_endLocation;
	m_sizeOfStack = numberOfBytes;
}


doubleStack::~doubleStack()
{
}

int doubleStack::memoryRemaining()
{
	int usedFront = m_currentFront - m_start;
	int usedBack = m_endLocation - m_currentBack;
	int remaining = m_sizeOfStack - usedFront - usedBack;
	return remaining;
}
