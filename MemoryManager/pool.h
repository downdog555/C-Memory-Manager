#pragma once
#include <vector>
#include <iostream>
#include <tuple>
#include "SmartPointer.h"
#include "MemoryManager.h"

class Pool
{
public:
	Pool(char* start, int numberOfBytes, int sizeOfBlocks, MemoryManager* m);
	~Pool();
	template<typename T>
	SmartPointer<T> allocate(T objectRequired);
	template<typename T>
	bool deallocate(SmartPointer<T>* pointer);
	int memoryRemaining();
	int blocksRemaining();
private:
	char* m_start;
	char* m_end;
	int m_blocksRemaining;
	int m_blockSize;
	int	m_numberOfBlocks;
	MemoryManager* m_manager;
	bool m_defragmenting;
	//bool in pair is false for in use, true for free
	std::vector<std::pair<char*, bool>> m_rawPool;
	//char pointer is start, int is number of required blocks second int is block index
	template<typename T>
	std::vector<SmartPointer<T>> m_locationMap;
	void defragment();
};

template<typename T>
inline SmartPointer<T> Pool::allocate(T objectRequired)
{
	int numOfBlocksReq;
	//since we have size of T we knwo how many blocks are required
	if (sizeof(T) % m_blockSize > 0) 
	{
		numOfBlocksReq = sizeof(T) / m_blockSize + 1;
	}
	else 
	{
		numOfBlocksReq = sizeof(T) / m_blockSize;
	}
	if (blocksRemaining() < numOfBlocksReq) 
	{
		return NULL;
	}
	else 
	{
		bool done = false;
		char* startloc;
		int blockCount;
		int startBlock;
		while (!done) 
		{
			startloc = NULL;
			blockCount = 0;
			//we have to find that number of contiguous blocks
			//if we cant then we need to defragment....

			for (int block = 0; block < m_rawPool.size(); block++)
			{
				if (m_rawPool[block].second == true && startloc == NULL)
				{
					startloc = m_rawPool[block].first;
					startBlock = block;
					blockCount += 1;
					continue;
				}

				if (m_rawPool[block].second == false)
				{
					startloc = NULL;
					startBlock = NULL;
					blockCount = 0;
					continue;
				}

				if (m_rawPool[block].second == true;)
				{
					blockCount += 1;
					continue;
				}

				if (blockCount == numOfBlocksReq)
				{
					//we are done
					done = true;
					break;
				}

			}

			if (done == false)
			{
				//we need to defragment
				defragment();
			}



		}
		//when we have the location and number of blocks we can then assign
		//we first reserve the blocks then create hte object
		for (int blocksToReserve = startBlock; blocksToReserve < numOfBlocksReq; blocksToReserve++) 
		{
			m_rawPool[blocksToReserve].second = false;
		}
		m_blocksRemaining -= numOfBlocksReq;
		char* start = m_rawPool[startBlock].first;
		
		
		T *obj = new(start) T();
		SmartPointer<T> temp(obj, m_manager, 2, startBlock);
	
		m_locationMap.pushBack(temp);
		return temp;

		

	}

	return NULL;
}
template<typename T>
inline bool Pool::deallocate(SmartPointer<T>* pointer)
{
	//we have need to loop through pool map and find the matching char pointer...
	//remove from the list and then deallocate
	//using thesecond value as the number of blocks
	int numberOfBlocks;
	//since we have size of T we knwo how many blocks are required
	if (sizeof(T) % m_blockSize > 0)
	{
		numberOfBlocks = sizeof(T) / m_blockSize + 1;
	}
	else
	{
		numberOfBlocks = sizeof(T) / m_blockSize;
	}
	int startBlock = *pointer->GetIndex();
	int endValue = startBlock + numberOfBlocks;
	for (int blockDealloc = startBlock; blockDealloc < endValue; blockDealloc++)
	{
		m_rawPool[blockDealloc].second = true;
		m_blocksRemaining++;
	}
	

	for (std::vector<SmartPointer<T>>::iterator it = m_locationMap.begin(); it != m_locationMap.end(); ++it)
	{
		if (*it->GetActual() == *pointer->GetActual()) 
		{
			m_locationMap.erase(it);
			return true;
			
		}
	}
	return false;
}
