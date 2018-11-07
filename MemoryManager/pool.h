#pragma once
#include <vector>
#include <iostream>
#include <tuple>
#include <string>
#include <list>
#include "SmartPointer.h"

class Pool
{
public:
	Pool();
	Pool(char* start, int numberOfBytes, int sizeOfBlocks, MemoryManager* m);
	~Pool();
	template<typename T, typename... Args>
	SmartPointer<T> allocate(T objectRequired, Args... args);
	template<typename T>
	SmartPointer<T> allocate(T objectRequired);
	
	bool deallocate(ActualWrapper* toRemove);
	int memoryRemaining();
	int blocksRemaining();
	std::vector<std::string> DisplayPool();
	void defragment();
private:
	char* m_start;
	char* m_end;
	MemoryManager * m_manager;
	int m_blocksRemaining;
	int m_blockSize;
	int	m_numberOfBlocks;
	bool m_defragmenting;

	//bool in pair is false for in use, true for free
	std::vector<std::pair<char*, bool>> m_rawPool;
	//char pointer is start, int is number of required blocks second int is block index
	//we will store just a char pointer to the actual
	//std::vector<std::pair<ActualWrapper, int>> m_locationMap;
	std::list<std::pair<ActualWrapper, int>> m_locationMap;

	
};

template<typename T, typename... Args>
inline SmartPointer<T> Pool::allocate(T objectRequired, Args... args)
{

	std::cout << "pool allocate " << std::endl;
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
				if (blockCount == numOfBlocksReq)
				{
					//we are done
					done = true;
					break;
				}
				if (m_rawPool[block].second == false)
				{
					startloc = NULL;
					startBlock = NULL;
					blockCount = 0;
					continue;
				}

				if (m_rawPool[block].second == true)
				{
					blockCount += 1;
					continue;
				}



			}

			if (done == false)
			{
				//we need to defragment
				//defragment();
			}



		}
		//when we have the location and number of blocks we can then assign
		//we first reserve the blocks then create hte object
		for (int blocksToReserve = startBlock; blocksToReserve < startBlock + numOfBlocksReq; blocksToReserve++)
		{
			m_rawPool[blocksToReserve].second = false;
		}
		m_blocksRemaining -= numOfBlocksReq;
		char* start = m_rawPool[startBlock].first;


		T *obj = new(start) T(args...);
		//SmartPointer(ActualWrapper<T>* actual, MemoryManager* m, int l = POOL, int index = 0, bool frontBack = false);
		ActualWrapper actual(start);
		//SmartPointer<T> temp(&actual, m_manager, 2, startBlock, false);
		std::pair<ActualWrapper, int> tempPair(actual, numOfBlocksReq);

		//m_locationMap.push_back(std::pair<ActualWrapper, int>( ActualWrapper(start), numOfBlocksReq));

		m_locationMap.emplace_back(ActualWrapper(start), numOfBlocksReq);
		//return SmartPointer<T>(&m_locationMap[index].first, m_manager, 2, startBlock, false);
		return SmartPointer<T>(&m_locationMap.back().first, m_manager, 2, startBlock, false);
	}
	return NULL;
}
template<typename T>
inline SmartPointer<T> Pool::allocate(T objectRequired)
{

	std::cout << "pool allocate " << std::endl;
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
				if (blockCount == numOfBlocksReq)
				{
					//we are done
					done = true;
					break;
				}
				if (m_rawPool[block].second == false)
				{
					startloc = NULL;
					startBlock = NULL;
					blockCount = 0;
					continue;
				}
				
				if (m_rawPool[block].second == true)
				{
					blockCount += 1;
					continue;
				}

				

			}

			if (done == false)
			{
				//we need to defragment
				//defragment();
			}



		}
		//when we have the location and number of blocks we can then assign
		//we first reserve the blocks then create hte object
		for (int blocksToReserve = startBlock; blocksToReserve < startBlock+numOfBlocksReq; blocksToReserve++)
		{
			m_rawPool[blocksToReserve].second = false;
		}
		m_blocksRemaining -= numOfBlocksReq;
		char* start = m_rawPool[startBlock].first;


		T *obj = new(start) T();
		//SmartPointer(ActualWrapper<T>* actual, MemoryManager* m, int l = POOL, int index = 0, bool frontBack = false);
		ActualWrapper actual(start);
		//SmartPointer<T> temp(&actual, m_manager, 2, startBlock, false);
		std::pair<ActualWrapper, int> tempPair(actual, numOfBlocksReq);
	
		//m_locationMap.push_back(std::pair<ActualWrapper, int>( ActualWrapper(start), numOfBlocksReq));
		
		m_locationMap.emplace_back(ActualWrapper(start), numOfBlocksReq);
		//return SmartPointer<T>(&m_locationMap[index].first, m_manager, 2, startBlock, false);
		return SmartPointer<T>(&m_locationMap.back().first, m_manager, 2, startBlock, false);



	}

	return NULL;
}




