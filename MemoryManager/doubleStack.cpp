#include "doubleStack.h"
/// <summary>
/// main constructor
/// initialises the required counters
/// </summary>
/// <param name="startLocation">char pointer to the start of the block of reserved memeory</param>
/// <param name="numberOfBytes">the number of bytes allocated for the stack</param>
DoubleStack::DoubleStack(char * startLocation, unsigned const int numberOfBytes)
{
	m_start = startLocation;
	m_currentFront = startLocation;
	m_endLocation = startLocation + numberOfBytes;
	m_currentBack = m_endLocation;
	m_sizeOfStack = numberOfBytes;
}


DoubleStack::~DoubleStack()
{
}
/// <summary>
/// function to calculate the amount of memeory remaing in bytes
/// </summary>
/// <returns>the number of bytes remaining in the stack</returns>
int DoubleStack::memoryRemaining()
{
	int usedFront = m_currentFront - m_start;
	int usedBack = m_endLocation - m_currentBack;
	int remaining = m_sizeOfStack - usedFront - usedBack;
	return remaining;
}
