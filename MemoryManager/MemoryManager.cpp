#include "MemoryManager.h"
MemoryManager::MemoryManager(int bytesForStack, int bytesForDBStack, int bytesForPool, int blockSizePool)
{
	int bytesToReserve = bytesForStack + bytesForDBStack + bytesForPool;
	m_memoryStart = (char*)std::malloc(bytesToReserve);
	//initialise each storage thing
	m_stack = Stack(m_memoryStart, bytesForStack, this);
	m_dbStack = DoubleStack(m_memoryStart + bytesForStack, bytesForDBStack, this);
	m_pool = Pool(m_memoryStart+bytesForStack+bytesForDBStack, bytesForPool,blockSizePool, this);
}

void MemoryManager::Defrag()
{
	m_pool.defragment();
}

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



MemoryManager::~MemoryManager()
{
}

int MemoryManager::GetPoolBlocksLeft()
{
	
	return m_pool.blocksRemaining();
}

int MemoryManager::GetStackBytesLeft()
{
	return m_stack.memoryRemaining();
}

int MemoryManager::GetDBStackBytesLeft()
{
	return m_dbStack.memoryRemaining();
}

std::vector<std::string> MemoryManager::DisplayPoolAlloc()
{
	return m_pool.DisplayPool();
}
