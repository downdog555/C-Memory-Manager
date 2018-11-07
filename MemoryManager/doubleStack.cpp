#include "doubleStack.h"
DoubleStack::DoubleStack()
{
}
/// <summary>
/// main constructor
/// initialises the required counters
/// </summary>
/// <param name="startLocation">char pointer to the start of the block of reserved memeory</param>
/// <param name="numberOfBytes">the number of bytes allocated for the stack</param>
DoubleStack::DoubleStack(char * startLocation, unsigned const int numberOfBytes, MemoryManager* m)
{
	m_start = startLocation;
	m_currentFront = startLocation;
	m_endLocation = startLocation + numberOfBytes;
	m_currentBack = m_endLocation;
	m_sizeOfStack = numberOfBytes;
	m_manager = m;
}


DoubleStack::~DoubleStack()
{
}
bool DoubleStack::deallocateFront(ActualWrapper * toRemove)
{

	//we need to find how many bytes the object is
	int size = 0;;
	int index = 0;
	char* toFind = toRemove->GetActual();
	for (int i = 0; i < actuals.size(); i++)
	{
		if (toFind == actuals[i].first.GetActual())
		{
			index = i;
			size = actuals[i].second;
			break;
		}
	}


	if (toFind > m_currentFront)
	{
		return false;
	}
	if (m_currentFront - size == toFind)
	{
		//we need to remove the acutal from the list now 
		//we can destruct
		actuals.erase(actuals.begin() + index);
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
bool DoubleStack::deallocateBack(ActualWrapper * toRemove)
{

	//we need to find how many bytes the object is
	int size = 0;;
	int index = 0;
	char* toFind = toRemove->GetActual();
	for (int i = 0; i < actuals.size(); i++)
	{
		if (toFind == actuals[i].first.GetActual())
		{
			index = i;
			size = actuals[i].second;
			break;
		}
	}


	if (toFind < m_currentBack)
	{
		return false;
	}
	if (m_currentBack == toFind)
	{
		//we need to remove the acutal from the list now 
		//we can destruct
		actuals.erase(actuals.begin() + index);
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
