#include "stack.h"
/// <summary>
/// default constructor
/// </summary>
Stack::Stack()
{
}
/// <summary>
/// the correct constructor
/// </summary>
/// <param name="startLocation">char pointer to the start of the stack in memeory</param>
/// <param name="numberOfBytes">the number of bytes being used for the stack</param>
/// <param name="m">a pointer to the memeory manager creating this stack</param>
Stack::Stack(char * startLocation, unsigned const int numberOfBytes, MemoryManager * m)
{
	m_start = startLocation;
	m_current = startLocation;
	m_endLocation = startLocation+numberOfBytes;
	m_sizeOfStack = numberOfBytes;
	m_manager = m;
}
/// <summary>
/// destructor
/// </summary>
Stack::~Stack()
{
}
/// <summary>
/// function to deallocate an object
/// </summary>
/// <param name="toRemove">a pointer to the actual wrapper</param>
/// <returns>boolean providing success or faliure</returns>
bool Stack::deallocate(ActualWrapper * toRemove)
{
	//size of the object in bytes to remove
	int size = 0;
	//get a char* so it is easier to comapre and not gotten on each itteration
	char* toFind = toRemove->GetActual();
	//iterates through the list of acutals
	for (std::list<std::pair<ActualWrapper,int>>::iterator it = m_actuals.begin(); it != m_actuals.end(); it++) 
	{
		
		
		//if the pointer is after the current front then we cannot dealloc and it is error
		if (toFind > m_current)
		{
			//return faliure
			return false;
		}
		//get the size to compare where the object ends
		size = it->second;
		if (m_current - size == toFind)
		{
			//we have found it at front of stack
			//we need to remove the acutal from the list now 
			//we can destruct
			//remove from the list
			m_actuals.erase(it);
			//decrement the char* by the size
			m_current -= size;
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
/// function to get the remaing memeory in the stack
/// </summary>
/// <returns>int containg the amount of memeory left</returns>
int Stack::memoryRemaining()
{

	int used = m_current - m_start;
	int remaining = m_sizeOfStack - used;
	return remaining;
}
