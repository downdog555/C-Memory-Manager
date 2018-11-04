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
Pool::Pool(char * start, int numberOfBytes, int sizeOfBlocks)
{
	m_start = start;
	m_end = start + numberOfBytes;
	m_blockSize = sizeOfBlocks;

	//we also need to initalise the block pool
	m_numberOfBlocks = numberOfBytes / sizeOfBlocks;
	m_rawPool.reserve(m_numberOfBlocks);
	for (int i = 0; i < m_numberOfBlocks; i++) 
	{
		std::pair<char*, bool> temp;
		temp.first = m_start + (i*m_blockSize);
		temp.second = true;
	}
}

Pool::~Pool()
{
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
/// <summary>
/// method to defrag called when we have enough blocks but not enough consecutively
/// </summary>
template<typename T>
void Pool::defragment()
{
	//we need to start with each smart pointer,
	//we get each actual,
	//then we see if there is a free block before it.
	//if there is we will try to move it up
	//we propagate the update by the smart pointers we have access to, use the update actual function...
	//we will use memmove
	//we go through the 
	for (int i = 0; i< m_rawPool.size(); i++)
	{
		//we go through the raw pool block by block, find the corrosponding smart pointer
		//get the size of T and what not and re-assign....
		SmartPointer s;
		for (int j = 0; j < m_locationMap.size(); j++) 
		{
			if (m_rawPool[i].first == (char*)m_locationMap[j].GetActual()) 
			{
				//we have found smart pointer
				s = m_locationMap[j];
			}
		}
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


			i += (numberOfBlocks -1);
			continue;
		}
		//we now need another loop to find out where we can star to assign from
		int newStartCounter = i-1;
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
		std::memmove((void*)m_rawPool[newStartCounter].first,(void*)m_rawPool[i].first, numOfBytes);
		//we then need to update the smart pointer with the new place
		s.UpdateActual((T*)m_rawPool[newStartCounter].first);
		//we then can set from this point till the end of file.
		//
		int endOfBothBlocks = i + numberOfBlocks;
		for (int blockReset = newStartCounter; newStartCounter < endOfBothBlocks; blockReset ++)
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


	
}
