#include "MemoryManager.h"

/// <summary>
/// set instance to null on first creation
/// </summary>
MemoryManager* MemoryManager::instance = 0;
/// <summary>
/// Constructor
/// </summary>
/// <param name="bytesForStack">number of bytes for stack</param>
/// <param name="bytesForDBStack">number for double stack</param>
/// <param name="bytesForPool">number for pool</param>
/// <param name="blockSizePool">size of each block in pool</param>
MemoryManager::MemoryManager(int bytesForStack, int bytesForDBStack, int bytesForPool, int blockSizePool)
{
	int bytesToReserve = bytesForStack + bytesForDBStack + bytesForPool;
	m_memoryStart = (char*)std::malloc(bytesToReserve);
	//initialise each storage thing
	m_stack = Stack(m_memoryStart, bytesForStack, this);
	m_dbStack = DoubleStack(m_memoryStart + bytesForStack, bytesForDBStack, this);
	m_pool = Pool(m_memoryStart+bytesForStack+bytesForDBStack, bytesForPool,blockSizePool, this);
}
/// <summary>
/// blanck get instance to return a copy
/// </summary>
/// <returns></returns>
MemoryManager * MemoryManager::getInstance()
{
	return instance;
}
/// <summary>
/// supposed to be used for first intilisation
/// </summary>
/// <param name="bytesForStack">bytes required for stack</param>
/// <param name="bytesForDBStack">bytes requried for double stack</param>
/// <param name="bytesForPool">bytes rquired for the pool</param>
/// <param name="blockSizePool">sized of each block in pool</param>
/// <returns>memeory manager isntance</returns>
MemoryManager * MemoryManager::getInstance(int bytesForStack, int bytesForDBStack, int bytesForPool, int blockSizePool)
{
	if (instance == 0) 
	{
		instance = new MemoryManager(bytesForStack, bytesForDBStack, bytesForPool, blockSizePool);
	}
	return instance;
}
/// <summary>
/// function call defrag on pool
/// </summary>
void MemoryManager::Defrag()
{
	m_pool.defragment();
}
/// <summary>
/// function to deallocte
/// </summary>
/// <param name="toRemove">actual wrapper to remove</param>
/// <param name="location">location it is stored</param>
/// <param name="frontBack">front back bool for dbstack</param>
/// <returns>bool for success</returns>
void MemoryManager::Deallocate(ActualWrapper * toRemove, int location, bool frontBack)
{
	bool value;
	if (location == 0)
	{
		value = m_stack.deallocate(toRemove);
	}
	else if (location == 1)
	{
		if (frontBack)
		{
			value= m_dbStack.deallocateFront(toRemove);
		}
		else
		{
			value = m_dbStack.deallocateBack(toRemove);
		}
	}
	else
	{
		value = m_pool.deallocate(toRemove);
	}

	if (!value)
	{
		throw DeallocationException();
	}
}


/// <summary>
/// destructor
/// </summary>
MemoryManager::~MemoryManager()
{
	free((void*)m_memoryStart);
}
/// <summary>
/// gets hte number of blocks left in pool
/// </summary>
/// <returns></returns>
int MemoryManager::GetPoolBlocksLeft()
{
	
	return m_pool.blocksRemaining();
}
/// <summary>
/// gets hte number of bytes left in stack
/// </summary>
/// <returns></returns>
int MemoryManager::GetStackBytesLeft()
{
	return m_stack.memoryRemaining();
}
/// <summary>
/// gets hte number of bytes left in db stack
/// </summary>
/// <returns></returns>
int MemoryManager::GetDBStackBytesLeft()
{
	return m_dbStack.memoryRemaining();
}
/// <summary>
/// gets graphical representation of pool state
/// </summary>
/// <returns></returns>
std::vector<std::string> MemoryManager::DisplayPoolAlloc()
{
	return m_pool.DisplayPool();
}
