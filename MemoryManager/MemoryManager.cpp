#include "MemoryManager.h"
MemoryManager::MemoryManager(int bytesForStack, int bytesForDBStack, int bytesForPool, int blockSizePool)
{
	int bytesToReserve = bytesForStack + bytesForDBStack + bytesForPool;
	m_memoryStart = (char*)std::malloc(bytesToReserve);
	//initialise each storage thing
	m_stack = Stack(m_memoryStart, bytesForStack);
	m_dbStack = DoubleStack(m_memoryStart + bytesForStack, bytesForDBStack);
	m_pool = Pool(m_memoryStart+bytesForStack+bytesForDBStack, bytesForPool,blockSizePool);
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
