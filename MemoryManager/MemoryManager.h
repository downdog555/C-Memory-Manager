#pragma once

#include "stack.h"
#include "pool.h"
#include "doubleStack.h"
#include "SmartPointer.h"


class MemoryManager
{
public:
	MemoryManager(int bytesForStack, int bytesForDBStack, int bytesForPool, int blockSizePool);

	/// <summary>
	/// Returns a smart pointer of the requested type...
	/// </summary>
	/// <param name="type">is the required type</param>
	/// <param name="storageLocation">defaults to using the pool, stack is 0 and 1 is double stack</param>
	/// <param name="frontBack"> if storage requested is double stack true for front false for back</param>
	/// <returns>a smart pointer</returns>
	template<typename T, typename... Args>
	SmartPointer<T> Allocate(T type,int storageLocation = 2, bool frontBack = false, Args... arg);
	template<typename T>
	SmartPointer<T> Allocate(T type,int storageLocation = 2, bool frontBack = false);

	void Defrag();

	bool Deallocate(ActualWrapper* toRemove, int location, bool frontBack = false);

	~MemoryManager();
	int GetPoolBlocksLeft();
	int GetStackBytesLeft();
	int GetDBStackBytesLeft();
	std::vector<std::string> DisplayPoolAlloc();
private:
	Stack m_stack;
	DoubleStack m_dbStack;
	Pool m_pool;
	char* m_memoryStart;
};



template<typename T, typename... Args>
inline SmartPointer<T> MemoryManager::Allocate(T type,int storageLocation, bool frontBack, Args... arg)
{
	
	//std::cout << "Manage allocate " << std::endl;
	if (storageLocation == 0)
	{
		return m_stack.allocate(type, arg...);
	}
	else if (storageLocation == 1)
	{
		if (frontBack)
		{
			return m_dbStack.allocateFront(type, arg...);
		}
		else
		{
			return m_dbStack.allocateBack(type, arg...);
		}
	}
	else
	{
		//	std::cout << "Manage allocate POOl" << std::endl;
		return m_pool.allocate(type, arg...);
	}
	return NULL;

}
template<typename T>
inline SmartPointer<T> MemoryManager::Allocate(T type,int storageLocation, bool frontBack)
{
	//std::cout << "Manage allocate " << std::endl;
	if (storageLocation == 0)
	{
		return m_stack.allocate(type);
	}
	else if (storageLocation == 1)
	{
		if (frontBack)
		{
			return m_dbStack.allocateFront(type);
		}
		else
		{
			return m_dbStack.allocateBack(type);
		}
	}
	else
	{
	//	std::cout << "Manage allocate POOl" << std::endl;
		return m_pool.allocate(type);
	}
	return NULL;
}
