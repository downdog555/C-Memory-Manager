#include "pool.h"
/// <summary>
/// Main constructor
/// initilises the required data sets
/// such as raw pool
/// </summary>
/// <param name="start">char pointer to the section of memeory reserved by the main memeory manager class</param>
/// <param name="numberOfBytes">the size of the pool required in bytes</param>
/// <param name="sizeOfBlocks">the size of each block in the pool</param>
pool::pool(char * start, int numberOfBytes, int sizeOfBlocks)
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

pool::~pool()
{
}
/// <summary>
/// gets the amount of memeory in bytes
/// </summary>
/// <returns>the number of bytes remaining</returns>
int pool::memoryRemaining()
{
	return (m_blocksRemaining * m_blockSize);
}
/// <summary>
/// gets the number of blocks remaining
/// </summary>
/// <returns>number of blocks remaining</returns>
int pool::blocksRemaining()
{
	return m_blocksRemaining;
}
