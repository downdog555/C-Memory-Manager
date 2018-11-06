#include "pool.h"
Pool::Pool()
{
}
/// <summary>
/// Main constructor
/// initilises the required data sets
/// such as raw pool
/// </summary>
/// <param name="start">char pointer to the section of memeory reserved by the main memeory manager class</param>
/// <param name="numberOfBytes">the size of the pool required in bytes</param>
/// <param name="sizeOfBlocks">the size of each block in the pool</param>
Pool::Pool(char * start, int numberOfBytes, int sizeOfBlocks, MemoryManager* m)
{

	m_start = start;
	m_end = start + numberOfBytes;
	m_blockSize = sizeOfBlocks;
	m_manager = m;
	//we also need to initalise the block pool
	m_numberOfBlocks = numberOfBytes / sizeOfBlocks;
	m_blocksRemaining = m_numberOfBlocks;
	m_rawPool.reserve(m_numberOfBlocks);
	for (int i = 0; i < m_numberOfBlocks; i++) 
	{
		std::pair<char*, bool> temp;
		temp.first = m_start + (i*m_blockSize);
		temp.second = true;
		m_rawPool.push_back(temp);
	}
}

Pool::~Pool()
{
}
bool Pool::deallocate(char * toRemove)
{
	return false;
}
/// <summary>
/// gets the amount of memeory in bytes
/// </summary>
/// <returns>the number of bytes remaining</returns>
int Pool::memoryRemaining()
{
	return (m_blocksRemaining * m_blockSize);
}
/// <summary>
/// gets the number of blocks remaining
/// </summary>
/// <returns>number of blocks remaining</returns>
int Pool::blocksRemaining()
{
	return m_blocksRemaining;
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
				if (m_rawPool[i].first == m_locationMap[j].GetActual())
				{
					//we need to loop through the list of smart pointers created for this
				}
			}
		}



	
}
