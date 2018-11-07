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
	//m_locationMap.reserve(m_numberOfBlocks);
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
bool Pool::deallocate(ActualWrapper * toRemove)
{


	for (std::list<std::pair<ActualWrapper, int>>::iterator it = m_locationMap.begin(); it!= m_locationMap.end(); ++it) 
	{
		if (it->first.GetActual() == toRemove->GetActual()) 
		{
			//we can now remove it and unlock each one 
			int sizeOfBlock = it->second;
			//we need to find which block it starts at
			for (int blockIndex = 0; blockIndex < m_rawPool.size(); blockIndex++)
			{
				if (m_rawPool[blockIndex].first == toRemove->GetActual())
				{
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
std::vector<std::string> Pool::DisplayPool()
{
	std::vector<std::string> temp;

	//we need to know row size and column
	int rowSize = 5;
	std::string s ="";
	int columnCounter = 0;
	for (int i =0; i < m_rawPool.size(); i++) 
	{
		
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
