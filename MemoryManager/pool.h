#pragma once
#include <vector>
#include <iostream>
#include <tuple>
#include "SmartPointer.h"
//#include "MemoryManager.h"

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
	template<typename T>
	bool deallocate(SmartPointer<T> * pointer);
	int memoryRemaining();
	int blocksRemaining();
private:
	char* m_start;
	char* m_end;
	MemoryManager * m_manager;
	int m_blocksRemaining;
	int m_blockSize;
	int	m_numberOfBlocks;
	bool m_defragmenting;
	template<typename T>
	bool defragGeneric(SmartPointer<T> pointer, int i);
	//bool in pair is false for in use, true for free
	std::vector<std::pair<char*, bool>> m_rawPool;
	//char pointer is start, int is number of required blocks second int is block index
	//we will store just a char pointer to the actual
	std::vector<char*> m_locationMap;


	void defragment();
};

template<typename T, typename... Args>
inline SmartPointer<T> Pool::allocate(T objectRequired, Args... args)
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
		
		
		T *obj = new(start) T(args);
		//SmartPointer(ActualWrapper<T>* actual, MemoryManager* m, int l = POOL, int index = 0, bool frontBack = false);
		ActualWrapper<T>* actual(obj);
		SmartPointer<T> temp(actual, m_manager, 2, startBlock);
	
		m_locationMap.pushBack((char*)obj);
		return temp;

		

	}

	return NULL;
}
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

				if (m_rawPool[block].second == true)
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
				//defragment();
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
		//SmartPointer(ActualWrapper<T>* actual, MemoryManager* m, int l = POOL, int index = 0, bool frontBack = false);
		ActualWrapper<T> actual(obj);
		SmartPointer<T> temp(&actual, m_manager, 2, startBlock);

		m_locationMap.push_back((char*)obj);
		return 	temp;



	}

	return NULL;
}
template<typename T>
inline bool Pool::deallocate(SmartPointer<T> * pointer)
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
	

	for (std::vector<SmartPointer>::iterator it = m_locationMap.begin(); it != m_locationMap.end(); ++it)
	{
		if (*it->GetActual() == *pointer->GetActual()) 
		{
			m_locationMap.erase(it);
			return true;
			
		}
	}
	return false;
}

template<typename T>
inline bool Pool::defragGeneric(SmartPointer<T> pointer, int i)
{
	//we now need to re alloc if we can...
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
	if (i == 0)
	{
		// since we cannot, the we need to advanced the counter by the number of blocks - 1


		i += (numberOfBlocks - 1);
		continue;
	}
	//we now need another loop to find out where we can star to assign from
	int newStartCounter = i - 1;
	while (newStartCounter > 0)
	{
		if (m_rawPool[newStartCounter].second == false)
		{
			break;
		}
		newStartCounter--;
	}

	//we now know the index block we can assign from, we also know the size of t and the number of blocks so we can use 
	int numOfBytes = numberOfBlocks * m_blockSize;
	std::memmove((void*)m_rawPool[newStartCounter].first, (void*)m_rawPool[i].first, numOfBytes);
	//we then need to update the smart pointer with the new place
	s.UpdateActual((T*)m_rawPool[newStartCounter].first);
	//we then can set from this point till the end of file.
	//
	int endOfBothBlocks = i + numberOfBlocks;
	for (int blockReset = newStartCounter; newStartCounter < endOfBothBlocks; blockReset++)
	{
		int secondCounter = 0;
		int endOfFirst = newStartCounter + numberOfBlocks;
		if (secondCounter < endOfFirst)
		{
			m_rawPool[blockReset].second = false;




			secondCounter++;
		}
		else
		{
			m_rawPool[blockReset].second = true;
		}

	}

}

void Pool::defragment()
{
	//we need to start with each smart pointer,
	//we get each actual,
	//then we see if there is a free block before it.
	//if there is we will try to move it up
	//we propagate the update by the smart pointers we have access to, use the update actual function...
	//we will use memmove
	//we go through the 
	for (int i = 0; i < m_rawPool.size(); i++)
	{
		//we go through the raw pool block by block, find the corrosponding smart pointer
		//get the size of T and what not and re-assign....

		for (int j = 0; j < m_locationMap.size(); j++)
		{
			if (m_rawPool[i].first == m_locationMap[j])
			{
				//we need to loop through the list of smart pointers created for this
			}
		}
	}



}
