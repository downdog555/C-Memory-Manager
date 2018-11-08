#include "MemoryManager.h"
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
bool MemoryManager::Deallocate(ActualWrapper * toRemove, int location, bool frontBack)
{

	if (location == 0)
	{
		return m_stack.deallocate(toRemove);
	}
	else if (location == 1)
	{
		if (frontBack)
		{
			return m_dbStack.deallocateFront(toRemove);
		}
		else
		{
			return m_dbStack.deallocateBack(toRemove);
		}
	}
	else
	{
		return m_pool.deallocate(toRemove);
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
