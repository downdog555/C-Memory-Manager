#include "doubleStack.h"
/// <summary>
/// default constructor
/// </summary>
DoubleStack::DoubleStack()
{
}
/// <summary>
/// Actual Constructor
/// </summary>
/// <param name="startLocation">start location of this stack</param>
/// <param name="numberOfBytes">size of this stack</param>
/// <param name="m">pointer to the memory manager</param>
DoubleStack::DoubleStack(char * startLocation, unsigned const int numberOfBytes, MemoryManager* m)
{
	m_start = startLocation;
	m_currentFront = startLocation;
	m_endLocation = startLocation + numberOfBytes;
	m_currentBack = m_endLocation;
	m_sizeOfStack = numberOfBytes;
	m_manager = m;
}

/// <summary>
/// destructor
/// </summary>
DoubleStack::~DoubleStack()
{
}
/// <summary>
/// deallocates from the front of the stack
/// </summary>
/// <param name="toRemove">pointer to the wrapper to be removed</param>
/// <returns>boolean of success or not</returns>
bool DoubleStack::deallocateFront(ActualWrapper * toRemove)
{
	//we need to find how many bytes the object is
	int size = 0;;
	int index = 0;
	char* toFind = toRemove->GetActual();
	for (std::list<std::pair<ActualWrapper, int>>::iterator it = m_actuals.begin(); it != m_actuals.end(); it++)
	{
		size = it->second;

		if (toFind > m_currentFront)
		{
			return false;
		}
		if (m_currentFront - size == toFind)
		{
			//we need to remove the acutal from the list now 
			//we can destruct
			m_actuals.erase(it);
			//do we need to call the constructor
			m_currentFront -= size;
			return true;
		}
		else
		{
			//we cannot deallocate but we could mark for deallocation.
			return false;
		}
	}

	return false;
}
/// <summary>
/// deallocates from the back
/// </summary>
/// <param name="toRemove">pointer to the wrapper to be removed</param>
/// <returns>boolean of success</returns>
bool DoubleStack::deallocateBack(ActualWrapper * toRemove)
{

	//we need to find how many bytes the object is
	int size = 0;;
	int index = 0;
	char* toFind = toRemove->GetActual();
	for (std::list<std::pair<ActualWrapper, int>>::iterator it = m_actuals.begin(); it != m_actuals.end(); it++)
	{
		size = it->second;

		if (toFind < m_currentBack)
		{
			return false;
		}
		if (m_currentBack == toFind)
		{
			//we need to remove the acutal from the list now 
			//we can destruct
			m_actuals.erase(it);
			//do we need to call the constructor
			m_currentBack += size;
			return true;
		}
		else
		{
			//we cannot deallocate but we could mark for deallocation.
			return false;
		}
	}

	return false;





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

void DoubleStack::CheckMemeory()
{
	if (memoryRemaining() / m_sizeOfStack < m_sizeOfStack / 4) 
	{
		std::cout << "Double Stack Memory is at less than 25%" << std::endl;
	}
}
