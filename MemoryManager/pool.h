#pragma once
#include <vector>
#include <iostream>
#include <tuple>
#include <string>
#include <list>
#include "SmartPointer.h"

/// <summary>
/// class representing a pool
/// </summary>
class Pool
{
public:
	/// <summary>
	/// default constructor
	/// </summary>
	Pool();
	/// <summary>
	/// correct constructor tto use
	/// </summary>
	/// <param name="start">char* to the start location of the pool</param>
	/// <param name="numberOfBytes">number of bytes in the pool</param>
	/// <param name="sizeOfBlocks">size of each block in the pool</param>
	/// <param name="m">pointer to hte memeory manager</param>
	Pool(char* start, int numberOfBytes, int sizeOfBlocks, MemoryManager* m);
	/// <summary>
	/// destructor
	/// </summary>
	~Pool();

	template<typename T, typename... Args>
	/// <summary>
	/// Allocates an  object using args for the constructor
	/// </summary>
	/// <param name="objectRequired">blank object required</param>
	/// <param name="...args">args for the constructor</param>
	/// <returns>smart pointer of correct type</returns>
	SmartPointer<T> allocate(T objectRequired, Args... args);
	template<typename T>
	/// <summary>
	/// allocates an object
	/// </summary>
	/// <param name="objectRequired">the required object blan kcopy</param>
	/// <returns>smardt pointer of correct type</returns>
	SmartPointer<T> allocate(T objectRequired);
	/// <summary>
	/// deallocates an object
	/// </summary>
	/// <param name="toRemove">actual wrapper pointer</param>
	/// <returns>boolean of success</returns>
	bool deallocate(ActualWrapper* toRemove);
	/// <summary>
	/// gets the amount of memeory remaing
	/// </summary>
	/// <returns>amount of memeory as int remaing</returns>
	int memoryRemaining();
	/// <summary>
	/// gets the number of blocks reaming 
	/// </summary>
	/// <returns>numbner of free blocks</returns>
	int blocksRemaining();
	/// <summary>
	/// dispalys the pools status
	/// </summary>
	/// <returns>vector of strings representing the current state of the pool</returns>
	std::vector<std::string> DisplayPool();
	/// <summary>
	/// defragments the pool
	/// </summary>
	void defragment();
private:
	/// <summary>
	/// start of the pool
	/// </summary>
	char* m_start;
	/// <summary>
	/// end of the pool
	/// </summary>
	char* m_end;
	/// <summary>
	/// pointer to the memeory manager
	/// </summary>
	MemoryManager * m_manager;
	/// <summary>
	/// number of blocks remaining
	/// </summary>
	int m_blocksRemaining;
	/// <summary>
	/// size of eacj block
	/// </summary>
	int m_blockSize;
	/// <summary>
	/// number of total blocks
	/// </summary>
	int	m_numberOfBlocks;
	/// <summary>
	/// defragging currently active
	/// </summary>
	bool m_defragmenting;
	/// <summary>
	/// function to allert user if memeory is low
	/// </summary>
	void CheckMemory();
	//bool in pair is false for in use, true for free
	/// <summary>
	/// vector of a pair of char* and bool, for each block, bool is true if block is free
	/// </summary>
	std::vector<std::pair<char*, bool>> m_rawPool;
	//char pointer is start, int is number of required blocks second int is block index
	//we will store just a char pointer to the actual
	//std::vector<std::pair<ActualWrapper, int>> m_locationMap;
	/// <summary>
	/// list of pairs of actual wrappers and ints representing number of blocks object takes up
	/// </summary>
	std::list<std::pair<ActualWrapper, int>> m_locationMap;

	
};

template<typename T, typename... Args>
/// <summary>
/// Allocates an  object using args for the constructor
/// </summary>
/// <param name="objectRequired">blank object required</param>
/// <param name="...args">args for the constructor</param>
/// <returns>smart pointer of correct type</returns>
inline SmartPointer<T> Pool::allocate(T objectRequired, Args... args)
{


	//	std::cout << "pool allocate " << std::endl;
	//we need the number of blocks the boject will take up
	int numOfBlocksReq;
	//since we have size of T we knwo how many blocks are required
	//if size mod the block size returns greater than 0 we need to divide then add extra block
	if (sizeof(T) % m_blockSize > 0)
	{
		numOfBlocksReq = sizeof(T) / m_blockSize + 1;
	}
	else
	{
		//if not just divide
		numOfBlocksReq = sizeof(T) / m_blockSize;
	}
	//check we have enough blocks
	if (blocksRemaining() < numOfBlocksReq)
	{
		return NULL;
	}
	else
	{
		//we then need to find the free blocks that are congruent
		bool done = false;
		char* startloc;
		int blockCount;
		int startBlock;
		//while we are not done searching
		while (!done)
		{
			//start loation is null
			startloc = NULL;
			//block count is set to zero
			blockCount = 0;
			//we have to find that number of contiguous blocks
			//if we cant then we need to defragment....

			for (int block = 0; block < m_rawPool.size(); block++)
			{
				//if current block is free and startloc is null, the ne have found the first posisble block
				if (m_rawPool[block].second == true && startloc == NULL)
				{
					//set start lock
					startloc = m_rawPool[block].first;
					//set start block index
					startBlock = block;
					//increase counter
					blockCount += 1;
					//go next itteration
					continue;
				}
				//if we have the required number of blocks we are dopne
				if (blockCount == numOfBlocksReq)
				{
					//we are done
					done = true;
					break;
				}
				//if it is false we need to start again
				if (m_rawPool[block].second == false)
				{
					startloc = NULL;
					startBlock = NULL;
					blockCount = 0;
					continue;
				}
				//if block is free increase block count
				if (m_rawPool[block].second == true)
				{
					blockCount += 1;
					continue;
				}



			}
			//after goinf through all blocks if we are not done we need to defrag

			if (done == false)
			{
				//we need to defragment
				defragment();
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

		//create object from that start point with args
		T *obj = new(start) T(args...);

		//add to list		
		m_locationMap.emplace_back(ActualWrapper(start), numOfBlocksReq);
		//return the smart pointer
		CheckMemory();
		return SmartPointer<T>(&m_locationMap.back().first, m_manager, 2, startBlock, false);



	}

	return NULL;
}
template<typename T>
/// <summary>
/// allocates an object
/// </summary>
/// <param name="objectRequired">the required object blan kcopy</param>
/// <returns>smardt pointer of correct type</returns>
inline SmartPointer<T> Pool::allocate(T objectRequired)
{

//	std::cout << "pool allocate " << std::endl;
	//we need the number of blocks the boject will take up
	int numOfBlocksReq;
	//since we have size of T we knwo how many blocks are required
	//if size mod the block size returns greater than 0 we need to divide then add extra block
	if (sizeof(T) % m_blockSize > 0)
	{
		numOfBlocksReq = sizeof(T) / m_blockSize + 1;
	}
	else
	{
		//if not just divide
		numOfBlocksReq = sizeof(T) / m_blockSize;
	}
	//check we have enough blocks
	if (blocksRemaining() < numOfBlocksReq)
	{
		return NULL;
	}
	else
	{
		//we then need to find the free blocks that are congruent
		bool done = false;
		char* startloc;
		int blockCount;
		int startBlock;
		//while we are not done searching
		while (!done)
		{
			//start loation is null
			startloc = NULL;
			//block count is set to zero
			blockCount = 0;
			//we have to find that number of contiguous blocks
			//if we cant then we need to defragment....

			for (int block = 0; block < m_rawPool.size(); block++)
			{
				//if current block is free and startloc is null, the ne have found the first posisble block
				if (m_rawPool[block].second == true && startloc == NULL)
				{
					//set start lock
					startloc = m_rawPool[block].first;
					//set start block index
					startBlock = block;
					//increase counter
					blockCount += 1;
					//go next itteration
					continue;
				}
				//if we have the required number of blocks we are dopne
				if (blockCount == numOfBlocksReq)
				{
					//we are done
					done = true;
					break;
				}
				//if it is false we need to start again
				if (m_rawPool[block].second == false)
				{
					startloc = NULL;
					startBlock = NULL;
					blockCount = 0;
					continue;
				}
				//if block is free increase block count
				if (m_rawPool[block].second == true)
				{
					blockCount += 1;
					continue;
				}

				

			}
			//after goinf through all blocks if we are not done we need to defrag

			if (done == false)
			{
				//we need to defragment
				defragment();
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

		//create object from that start point
		T *obj = new(start) T();
		
	//add to list		
		m_locationMap.emplace_back(ActualWrapper(start), numOfBlocksReq);
//return the smart pointer
		CheckMemory();
		return SmartPointer<T>(&m_locationMap.back().first, m_manager, 2, startBlock, false);



	}

	return NULL;
}




