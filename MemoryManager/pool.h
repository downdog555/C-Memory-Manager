#pragma once
#include <vector>
#include <iostream>
template<typename T>
/// <summary>
/// struct representing an entry for the pool so we can reallocate
/// </summary>
struct poolMapEntry 
{
	T ** userPointer;
	T* actualPointer;
	int numberOfBlocks;

};

class pool
{
public:
	pool(char* start, int numberOfBytes, int sizeOfBlocks);
	~pool();
	template<typename T>
	T* allocate(T objectRequired);
	template<typename T>
	bool deallocate(T *location);
	int memoryRemaining();
	int blocksRemaining();
private:
	char* m_start;
	char* m_end;
	int m_blocksRemaining;
	int m_blockSize;
	int	m_numberOfBlocks;
	bool m_defragmenting;
	//bool in pair is false for in use, true for free
	std::vector<std::pair<char*, bool>> m_rawPool;
	template<typename T>
	std::vector<poolMapEntry<T>> m_locationMap;
	void defragment();
};

template<typename T>
inline T * pool::allocate(T objectRequired)
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
		//we create the struct
		poolMapEntry<T> temp;
		T *obj = new(start) T();
		temp.actualPointer = obj;
		temp.numberOfBlocks = numOfBlocksReq;
		temp.userPointer = T ** p = &obj;
		m_locationMap.pushBack(temp);
		return temp.userPointer;

		

	}

	return NULL;
}
