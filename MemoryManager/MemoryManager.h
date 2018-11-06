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

	template<typename T>
	bool Deallocate(SmartPointer<T> * s);

	~MemoryManager();
	int GetPoolBlocksLeft();
	int GetStackBytesLeft();
	int GetDBStackBytesLeft();

private:
	Stack m_stack;
	DoubleStack m_dbStack;
	Pool m_pool;
	char* m_memoryStart;
};



template<typename T, typename... Args>
inline SmartPointer<T> MemoryManager::Allocate(T type,int storageLocation, bool frontBack, Args... arg)
{
	
	if (storageLocation == 0)
	{

	}
	else if (storageLocation == 1)
	{
		if (frontBack)
		{
			//TODO
			//return m_dbStack.allocateFront(type, arg);
		}
		else
		{
			//return m_dbStack.allocateBack(type, arg);
		}
	}
	else
	{
		return m_pool.allocate(type, arg);
	}

}
template<typename T>
inline SmartPointer<T> MemoryManager::Allocate(T type,int storageLocation, bool frontBack)
{
	std::cout << "Manage allocate " << std::endl;
	if (storageLocation == 0)
	{

	}
	else if (storageLocation == 1)
	{
		if (frontBack)
		{
			//return m_dbStack.allocateFront(type);
		}
		else
		{
			//return m_dbStack.allocateBack(type);
		}
	}
	else
	{
		std::cout << "Manage allocate POOl" << std::endl;
		return m_pool.allocate(type);
	}
	return NULL;
}
template<typename T>
inline bool MemoryManager::Deallocate(SmartPointer<T> * s)
{
	int locationType = s->GetLocation();
	if (locationType == 0)
	{
		m_stack.deallocate(s);
	}
	else if (locationType == 1)
	{
		if (s->m_frontBack)
		{
			return m_dbStack.deallocateFront(s);
		}
		else
		{
			return m_dbStack.deallocateBack(s);
		}
	}
	else
	{

		return m_pool.deallocate(s, s->GetActual());
	}
}