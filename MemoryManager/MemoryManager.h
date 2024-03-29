#pragma once

#include "stack.h"
#include "pool.h"
#include "doubleStack.h"
#include "SmartPointer.h"
#include "Exceptions.h"


class MemoryManager
{
public:
	/// <summary>
	/// blanck get instance to return a copy
	/// </summary>
	/// <returns></returns>
	static MemoryManager* getInstance();
	/// <summary>
	/// supposed to be used for first intilisation
	/// </summary>
	/// <param name="bytesForStack">bytes required for stack</param>
	/// <param name="bytesForDBStack">bytes requried for double stack</param>
	/// <param name="bytesForPool">bytes rquired for the pool</param>
	/// <param name="blockSizePool">sized of each block in pool</param>
	/// <returns>memeory manager isntance</returns>
	static MemoryManager* getInstance(int bytesForStack, int bytesForDBStack, int bytesForPool, int blockSizePool);
	template<typename T, typename... Args>
	/// <summary>
	/// allocate fucntion with args for constructor
	/// </summary>
	/// <param name="type">the type of object required</param>
	/// <param name="storageLocation">the stroage location</param>
	/// <param name="frontBack">front back bool for db stack  deafults to false</param>
	/// <param name="...arg">args for constructor</param>
	/// <returns>smart pointer of correct type</returns>
	SmartPointer<T> Allocate(T type,int storageLocation = 2, bool frontBack = false, Args... arg);
	template<typename T>
	/// <summary>
	/// allocate fucntion with args for constructor
	/// </summary>
	/// <param name="type">the type of object required</param>
	/// <param name="storageLocation">the stroage location</param>
	/// <param name="frontBack">front back bool for db stack  deafults to false</param>
	/// <returns>smart pointer of correct type</returns>
	SmartPointer<T> Allocate(T type,int storageLocation = 2, bool frontBack = false);
	/// <summary>
	/// function call defrag on pool
	/// </summary>
	void Defrag();

	/// <summary>
	/// function to deallocte
	/// </summary>
	/// <param name="toRemove">actual wrapper to remove</param>
	/// <param name="location">location it is stored</param>
	/// <param name="frontBack">front back bool for dbstack</param>
	/// <returns>bool for success</returns>
	void Deallocate(ActualWrapper* toRemove, int location, bool frontBack = false);
	/// <summary>
	/// destructor
	/// </summary>
	~MemoryManager();
	/// <summary>
	/// gets hte number of blocks left in pool
	/// </summary>
	/// <returns></returns>
	int GetPoolBlocksLeft();
	/// <summary>
	/// gets hte number of bytes left in stack
	/// </summary>
	/// <returns></returns>
	int GetStackBytesLeft();
	/// <summary>
	/// gets hte number of bytes left in db stack
	/// </summary>
	/// <returns></returns>
	int GetDBStackBytesLeft();
	/// <summary>
	/// gets graphical representation of pool state
	/// </summary>
	/// <returns></returns>
	std::vector<std::string> DisplayPoolAlloc();
private:
	/// <summary>
	/// instace of the memeory manager
	/// </summary>
	static MemoryManager* instance;

	MemoryManager(const MemoryManager&);
	MemoryManager& operator=(const MemoryManager&);

	/// <summary>
	/// Constructor private for singleton
	/// </summary>
	/// <param name="bytesForStack">number of bytes for stack</param>
	/// <param name="bytesForDBStack">number for double stack</param>
	/// <param name="bytesForPool">number for pool</param>
	/// <param name="blockSizePool">size of each block in pool</param>
	MemoryManager(int bytesForStack, int bytesForDBStack, int bytesForPool, int blockSizePool);

	/// <summary>
	/// stack ref
	/// </summary>
	Stack m_stack;
	/// <summary>
	/// db stack ref
	/// </summary>
	DoubleStack m_dbStack;
	/// <summary>
	/// pool ref
	/// </summary>
	Pool m_pool;
	/// <summary>
	/// start of memeory char*
	/// </summary>
	char* m_memoryStart;
};


template<typename T, typename... Args>
/// <summary>
/// allocate fucntion with args for constructor
/// </summary>
/// <param name="type">the type of object required</param>
/// <param name="storageLocation">the stroage location</param>
/// <param name="frontBack">front back bool for db stack  deafults to false</param>
/// <param name="...arg">args for constructor</param>
/// <returns>smart pointer of correct type</returns>
inline SmartPointer<T> MemoryManager::Allocate(T type,int storageLocation, bool frontBack, Args... arg)
{
	SmartPointer<T> s;
	//std::cout << "Manage allocate " << std::endl;
	if (storageLocation == 0)
	{
		s =  m_stack.allocate(type, arg...);
	}
	else if (storageLocation == 1)
	{
		if (frontBack)
		{
			s=  m_dbStack.allocateFront(type, arg...);
		}
		else
		{
			s =  m_dbStack.allocateBack(type, arg...);
		}
	}
	else
	{
		//	std::cout << "Manage allocate POOl" << std::endl;
		s = m_pool.allocate(type, arg...);
	}


	if(s == NULL)
	{
		DeallocationException
		throw AllocationException();
	}
	return s;

}
template<typename T>
/// <summary>
/// allocate fucntion with args for constructor
/// </summary>
/// <param name="type">the type of object required</param>
/// <param name="storageLocation">the stroage location</param>
/// <param name="frontBack">front back bool for db stack  deafults to false</param>
/// <returns>smart pointer of correct type</returns>
inline SmartPointer<T> MemoryManager::Allocate(T type,int storageLocation, bool frontBack)
{
	SmartPointer<T> s;
	//std::cout << "Manage allocate " << std::endl;
	if (storageLocation == 0)
	{
		s =  m_stack.allocate(type);
	}
	else if (storageLocation == 1)
	{
		if (frontBack)
		{
			s = m_dbStack.allocateFront(type);
		}
		else
		{
			s = m_dbStack.allocateBack(type);
		}
	}
	else
	{
	//	std::cout << "Manage allocate POOl" << std::endl;
		s = m_pool.allocate(type);
	}
	if (s == NULL) 
	{
		throw AllocationException();
	}
	return s;
}
