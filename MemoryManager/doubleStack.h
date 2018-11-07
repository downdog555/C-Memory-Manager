#pragma once
#include <vector>
#include "ActualWrapper.h"
#include <iostream>
#include <list>
#include "SmartPointer.h"
/// <summary>
/// class representing a double ended stack
/// </summary>
class DoubleStack
{

public:
	DoubleStack();
	DoubleStack(char * startLocation, unsigned const int numberOfBytes, MemoryManager* m);
	~DoubleStack();
	template<typename T, typename... Args>
	SmartPointer<T> allocateFront(T objectRequired, Args... args);
	template<typename T>
	SmartPointer<T> allocateFront(T objectRequired);
	
	bool deallocateFront(ActualWrapper * toRemove);
	bool deallocateBack(ActualWrapper * toRemove);

	template<typename T, typename... Args>
	SmartPointer<T> allocateBack(T objectRequired, Args... args);
	template<typename T>
	SmartPointer<T> allocateBack(T objectRequired);
	int memoryRemaining();
private:
	char* m_start;
	char* m_currentFront;
	char* m_currentBack;
	char* m_endLocation;
	int m_sizeOfStack;
	MemoryManager * m_manager;
	std::list<std::pair<ActualWrapper, int>> m_actuals;
};
template<typename T, typename... Args>
/// <summary>
/// Method To Allocate memory for a given class to the front 
/// we need to also keep track of each allocation
/// </summary>
/// <param name="objectRequired">The Object To Allocate</param>
/// <returns>A pointer to the object</returns>
inline	SmartPointer<T> DoubleStack::allocateFront(T objectRequired, Args... args)
{
	//	std::cout << sizeof(T) << std::endl;

	if (m_currentFront + sizeof(T) > m_currentBack)
	{
		return NULL;
	}

	T *obj = new(m_currentFront) T(args...);
	m_actuals.emplace_back(ActualWrapper(m_currentFront), sizeof(T));
	m_currentFront += sizeof(T);
	return SmartPointer<T>(&m_actuals.back().first, m_manager, 1, 0, false);


}

template<typename T>
inline SmartPointer<T> DoubleStack::allocateFront(T objectRequired)
{

//	std::cout << sizeof(T) << std::endl;

	if (m_currentFront + sizeof(T) > m_currentBack)
	{
		return NULL;
	}

	T *obj = new(m_currentFront) T();
	m_actuals.emplace_back(ActualWrapper(m_currentFront), sizeof(T));
	m_currentFront += sizeof(T);
	return SmartPointer<T>(&m_actuals.back().first, m_manager, 1, 0, false);
}


template<typename T, typename... Args>
/// <summary>
/// function to allocate to the back of the stack.
/// </summary>
/// <param name="objectRequired">the object to be instanciated</param>
/// <returns>a pointer to the new object</returns>
inline SmartPointer<T> DoubleStack::allocateBack(T objectRequired, Args... args)
{

	//std::cout << sizeof(T) << std::endl;

	if (m_currentBack - sizeof(T) < m_currentFront)
	{
		return NULL;
	}
	m_currentBack -= sizeof(T);
	T *obj = new(m_currentFront) T(args...);

	//SmartPointer(ActualWrapper<T>* actual, MemoryManager* m, int l = POOL, int index = 0, bool frontBack = false);

	m_actuals.emplace_back(ActualWrapper(m_currentBack), sizeof(T));

	return SmartPointer<T>(&m_actuals.back().first, m_manager, 1, 0, false);
}

template<typename T>
inline SmartPointer<T> DoubleStack::allocateBack(T objectRequired)
{

	//std::cout << sizeof(T) << std::endl;

	if (m_currentBack - sizeof(T) < m_currentFront)
	{
		return NULL;
	}
	m_currentBack -= sizeof(T);
	T *obj = new(m_currentFront) T();

	//SmartPointer(ActualWrapper<T>* actual, MemoryManager* m, int l = POOL, int index = 0, bool frontBack = false);

	m_actuals.emplace_back(ActualWrapper(m_currentBack), sizeof(T));

	return SmartPointer<T>(&m_actuals.back().first, m_manager, 1, 0, false);

	
}



