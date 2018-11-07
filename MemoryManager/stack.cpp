#include "stack.h"
Stack::Stack()
{
}
/// <summary>
/// Constructor that initilises the stack.
/// </summary>
/// <param name="numberOfBytes"></param>
/// <param name="startLocation"></param>
Stack::Stack(char * startLocation, unsigned const int numberOfBytes, MemoryManager * m)
{
	m_start = startLocation;
	m_current = startLocation;
	m_endLocation = startLocation+numberOfBytes;
	m_sizeOfStack = numberOfBytes;
	m_manager = m;
}

Stack::~Stack()
{
}

bool Stack::deallocate(ActualWrapper * toRemove)
{
	//we need to find how many bytes the object is
	int size = 0;;
	int index = 0;
	char* toFind = toRemove->GetActual();
	for (std::list<std::pair<ActualWrapper,int>>::iterator it = m_actuals.begin(); it != m_actuals.end(); it++) 
	{
		size = it->second;

		if (toFind > m_current)
		{
			return false;
		}
		if (m_current - size == toFind)
		{
			//we need to remove the acutal from the list now 
			//we can destruct
			m_actuals.erase(it);
			//do we need to call the constructor
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

int Stack::memoryRemaining()
{

	int used = m_current - m_start;
	int remaining = m_sizeOfStack - used;
	return remaining;
}
