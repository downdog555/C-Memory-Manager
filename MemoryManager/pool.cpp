#include "pool.h"
/// <summary>
/// default constructor
/// </summary>
Pool::Pool()
{
}
/// <summary>
/// correct constructor tto use
/// </summary>
/// <param name="start">char* to the start location of the pool</param>
/// <param name="numberOfBytes">number of bytes in the pool</param>
/// <param name="sizeOfBlocks">size of each block in the pool</param>
/// <param name="m">pointer to hte memeory manager</param>
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
	//initilise blocks 
	for (int i = 0; i < m_numberOfBlocks; i++) 
	{
		std::pair<char*, bool> temp; 
		temp.first = m_start + (i*m_blockSize);
		temp.second = true;
		m_rawPool.push_back(temp);
	}
}
/// <summary>
/// destructor
/// </summary>
Pool::~Pool()
{
}
/// <summary>
/// deallocates an object
/// </summary>
/// <param name="toRemove">actual wrapper pointer</param>
/// <returns>boolean of success</returns>
bool Pool::deallocate(ActualWrapper * toRemove)
{

	//loop through each pair in the location map
	for (std::list<std::pair<ActualWrapper, int>>::iterator it = m_locationMap.begin(); it!= m_locationMap.end(); ++it) 
	{
		//if we find the correct actual
		if (it->first.GetActual() == toRemove->GetActual()) 
		{
			
			//we can now remove it and unlock each one 
			//we get the size of block
			int sizeOfBlock = it->second;
			//we need to find which block it starts at
			for (int blockIndex = 0; blockIndex < m_rawPool.size(); blockIndex++)
			{
				//means we have found the start block
				if (m_rawPool[blockIndex].first == toRemove->GetActual())
				{
					//unlock until end of num of block
					for (int j = blockIndex; j < blockIndex + sizeOfBlock; j++)
					{
						//unlock each block
						m_rawPool[j].second = true;

					}
					break;
				}
			}

			//add on the freed blocks
			m_blocksRemaining += sizeOfBlock;
			//now delete the actual from the list
			m_locationMap.erase(it);
			return true;
		}
	}
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
/// <summary>
/// dispalys the pools status
/// </summary>
/// <returns>vector of strings representing the current state of the pool</returns>
std::vector<std::string> Pool::DisplayPool()
{
	std::vector<std::string> temp;

	//we need to know row size and column
	int rowSize = 5;
	std::string s ="";
	int columnCounter = 0;
	for (int i =0; i < m_rawPool.size(); i++) 
	{
		//o for open x for closed
		if (m_rawPool[i].second) 
		{
			s = s + "o";
		}
		else 
		{
			s = s + "x";
		}
		columnCounter++;
		if (columnCounter == rowSize)
		{
			columnCounter = 0;
			temp.push_back(s);
			s = "";
		}


	}

	return temp;
}
/// <summary>
/// defragments the pool
/// </summary>
void Pool::defragment()
{
	
		//we need to start with each smart pointer,
		//we get each actual,
		//then we see if there is a free block before it.
		//if there is we will try to move it up
		//we propagate the update by the smart pointers we have access to, use the update actual function...
		//we will use memmove
		//we go through the raw pool
		for (int i = 0; i < m_rawPool.size(); i++)
		{
			//we go through the raw pool block by block, find the corrosponding smart pointer
			//get the size of T and what not and re-assign....
			for (std::list<std::pair<ActualWrapper, int>>::iterator it = m_locationMap.begin(); it != m_locationMap.end(); ++it) 
			{
				if (m_rawPool[i].first == it->first.GetActual())
				{
					//we need to see if we can move up any blocks
					//if 0 we cannot
					if (i != 0)
					{
						//we need to see if there are any free blocks before
						int numOfFreeBlocks = 0;
						for (int reverseCounter = i - 1; reverseCounter > 0; reverseCounter--)
						{
							if (m_rawPool[reverseCounter].second == true)
							{
								numOfFreeBlocks++;
							}
							else
							{
								break;
							}
						}

						int bytesToMoveBy = numOfFreeBlocks * m_blockSize;
						if (bytesToMoveBy > 0)
						{
							char* newPos = it->first.GetActual() - bytesToMoveBy;
							char* old = it->first.GetActual();
							int sizeOfObjectInBlocks = it->second;
							//use mememove to move data
							memmove(newPos, old, it->second*m_blockSize);
							//we then need to update actual
							it->first.UpdateActual(newPos);
							//we then need to set the blocks false/true
							//we can go from new position and set as locked until end of blocks, then set as free till end of old pointer
							for (int blockFreeingCounter = i - numOfFreeBlocks; blockFreeingCounter < i + sizeOfObjectInBlocks; blockFreeingCounter++)
							{
								//if it is not set to false then set to false

								//we set htem to closed
								if (blockFreeingCounter <= sizeOfObjectInBlocks)
								{
									if (m_rawPool[blockFreeingCounter].second == true)
									{
										m_rawPool[blockFreeingCounter].second = false;
									}

								}
								else
								{
									//the rest we  set to open
									if (m_rawPool[blockFreeingCounter].second == false)
									{
										m_rawPool[blockFreeingCounter].second = true;
									}
								}


							}

						}
						else
						{
							continue;
						}

					}
				}
			}
			
		}



	
}
/// <summary>
/// function to check memeory
/// </summary>
void Pool::CheckMemory()
{
	if (m_blocksRemaining/ m_numberOfBlocks < m_numberOfBlocks / 4)
	{
		std::cout << "Pool memeory is less than 25% left" << std::endl;
	}
}
