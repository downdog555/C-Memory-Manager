#pragma once
#include "SmartPointer.h"
#include "stack.h"
#include "pool.h"
#include "doubleStack.h"

class MemoryManager
{
public:
	MemoryManager(int bytesForStack, int bytesForDBStack, int bytesForPool, int blockSizePool);
	template<typename T>
	/// <summary>
	/// Returns a smart pointer of the requested type...
	/// </summary>
	/// <param name="type">is the required type</param>
	/// <param name="storageLocation">defaults to using the pool, stack is 0 and 1 is double stack</param>
	/// <param name="frontBack"> if storage requested is double stack true for front false for back</param>
	/// <returns>a smart pointer</returns>
	SmartPointer Allocate(T type, int storageLocation = 2, bool frontBack = false);

	template<typename T>
	bool Deallocate(SmartPointer * s);

	~MemoryManager();


private:
	Stack m_stack;
	DoubleStack m_dbStack;
	Pool m_pool;
	char* m_memoryStart;
};

template<typename T>
inline SmartPointer MemoryManager::Allocate(T type, int storageLocation, bool frontBack)
{
	SmartPointer s;
	if (storageLocation == 0)
	{

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
		s = m_pool.allocate(type);
	}
	return s;
}

template<typename T>
inline bool MemoryManager::Deallocate(SmartPointer * s)
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