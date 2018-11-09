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
	/// <summary>
	/// Default Constructor
	/// </summary>
	DoubleStack();
	/// <summary>
	/// Actual Constructor
	/// </summary>
	/// <param name="startLocation">start location of this stack</param>
	/// <param name="numberOfBytes">size of this stack</param>
	/// <param name="m">pointer to the memory manager</param>
	DoubleStack(char * startLocation, unsigned const int numberOfBytes, MemoryManager* m);
	/// <summary>
	/// destructor
	/// </summary>
	~DoubleStack();
	template<typename T, typename... Args>
	/// <summary>
	/// Function to allocate to the front with args
	/// </summary>
	/// <param name="objectRequired">blank version of the obejct</param>
	/// <param name="...args">the args for the constructor of the object</param>
	/// <returns>a smartpointer of correct object</returns>
	SmartPointer<T> allocateFront(T objectRequired, Args... args);
	template<typename T>
	/// <summary>
	/// allocates to the front of the stack
	/// </summary>
	/// <param name="objectRequired">blanck version of the required object</param>
	/// <returns>smart pointer of the correct type</returns>
	SmartPointer<T> allocateFront(T objectRequired);
	/// <summary>
	/// deallocates from the front of the stack
	/// </summary>
	/// <param name="toRemove">pointer to the wrapper to be removed</param>
	/// <returns>boolean of success or not</returns>
	bool deallocateFront(ActualWrapper * toRemove);
	/// <summary>
	/// deallocates from the back
	/// </summary>
	/// <param name="toRemove">pointer to the wrapper to be removed</param>
	/// <returns>boolean of success</returns>
	bool deallocateBack(ActualWrapper * toRemove);

	template<typename T, typename... Args>
	/// <summary>
	/// Allocates to the back stack with args for the objects constructor
	/// </summary>
	/// <param name="objectRequired">the required object</param>
	/// <param name="...args">the required arguments</param>
	/// <returns>Smart pointer of the correct type</returns>
	SmartPointer<T> allocateBack(T objectRequired, Args... args);
	template<typename T>
	/// <summary>
	/// Allocates to the back stack 
	/// </summary>
	/// <param name="objectRequired">the required object</param>
	/// <returns>Smart pointer of the correct type</returns>
	SmartPointer<T> allocateBack(T objectRequired);
	/// <summary>
	/// gets the amount of memory remaining
	/// </summary>
	/// <returns>amount of memeory remaing </returns>
	int memoryRemaining();
private:
	/// <summary>
	/// Function to chec kmemeory
	/// </summary>
	void CheckMemeory();

	/// <summary>
	/// start of the stack
	/// </summary>
	char* m_start;
	/// <summary>
	/// pointer to hte current front of teh stack
	/// </summary>
	char* m_currentFront;
	/// <summary>
	/// pointer to hte current back of the stack
	/// </summary>
	char* m_currentBack;
	/// <summary>
	/// end of the stack
	/// </summary>
	char* m_endLocation;
	/// <summary>
	/// size of the stack
	/// </summary>
	int m_sizeOfStack;
	/// <summary>
	/// pointer to the memory manager
	/// </summary>
	MemoryManager * m_manager;
	/// <summary>
	/// list of the actuals
	/// </summary>
	std::list<std::pair<ActualWrapper, int>> m_actuals;
};
template<typename T, typename... Args>
/// <summary>
/// Function to allocate to the front with args
/// </summary>
/// <param name="objectRequired">blank version of the obejct</param>
/// <param name="...args">the args for the constructor of the object</param>
/// <returns>a smartpointer of correct object</returns>
inline	SmartPointer<T> DoubleStack::allocateFront(T objectRequired, Args... args)
{
	//	std::cout << sizeof(T) << std::endl;
	//if current front plus the size of object is greater than the current back reutrn null
	if (m_currentFront + sizeof(T) > m_currentBack)
	{
		return NULL;
	}
	//create object at secified location
	T *obj = new(m_currentFront) T(args...);
	//add actual wrapper and size of object to list
	m_actuals.emplace_back(ActualWrapper(m_currentFront), sizeof(T));
	//increment the current front pointer by size of obj
	m_currentFront += sizeof(T);
	CheckMemeory();
	//return a smart pointer
	return SmartPointer<T>(&m_actuals.back().first, m_manager, 1, 0, false);

}

template<typename T>
/// <summary>
/// allocates to the front of the stack
/// </summary>
/// <param name="objectRequired">blanck version of the required object</param>
/// <returns>smart pointer of the correct type</returns>
inline SmartPointer<T> DoubleStack::allocateFront(T objectRequired)
{

//	std::cout << sizeof(T) << std::endl;
	//if current front plus the size of object is greater than the current back reutrn null
	if (m_currentFront + sizeof(T) > m_currentBack)
	{
		return NULL;
	}
	//create object at secified location
	T *obj = new(m_currentFront) T();
	//add actual wrapper and size of object to list
	m_actuals.emplace_back(ActualWrapper(m_currentFront), sizeof(T));
	//increment the current front pointer by size of obj
	m_currentFront += sizeof(T);
	CheckMemeory();
	//return a smart pointer
	return SmartPointer<T>(&m_actuals.back().first, m_manager, 1, 0, false);
}


template<typename T, typename... Args>
/// <summary>
/// Allocates to the back stack with args for the objects constructor
/// </summary>
/// <param name="objectRequired">the required object</param>
/// <param name="...args">the required arguments</param>
/// <returns>Smart pointer of the correct type</returns>
inline SmartPointer<T> DoubleStack::allocateBack(T objectRequired, Args... args)
{

	//std::cout << sizeof(T) << std::endl;
	//if the back minus the size of the object is less than the front return null
	if (m_currentBack - sizeof(T) < m_currentFront)
	{
		return NULL;
	}
	//decrement the current back to the front of the object
	m_currentBack -= sizeof(T);
	//create hte object at specific location with args
	T *obj = new(m_currentFront) T(args...);

	//SmartPointer(ActualWrapper<T>* actual, MemoryManager* m, int l = POOL, int index = 0, bool frontBack = false);
	//add and acutal wrapper and size of obj to the list
	m_actuals.emplace_back(ActualWrapper(m_currentBack), sizeof(T));
	CheckMemeory();
	//return the smart pointer
	return SmartPointer<T>(&m_actuals.back().first, m_manager, 1, 0, false);
}

template<typename T>
/// <summary>
/// Allocates to the back stack 
/// </summary>
/// <param name="objectRequired">the required object</param>
/// <returns>Smart pointer of the correct type</returns>
inline SmartPointer<T> DoubleStack::allocateBack(T objectRequired)
{

	//std::cout << sizeof(T) << std::endl;
	//if the back minus the size of the object is less than the front return null
	if (m_currentBack - sizeof(T) < m_currentFront)
	{
		return NULL;
	}
	//decrement the current back to the front of the object
	m_currentBack -= sizeof(T);
	//create hte object at specific location
	T *obj = new(m_currentBack) T();

	//SmartPointer(ActualWrapper<T>* actual, MemoryManager* m, int l = POOL, int index = 0, bool frontBack = false);
	//add and acutal wrapper and size of obj to the list
	m_actuals.emplace_back(ActualWrapper(m_currentBack), sizeof(T));
	CheckMemeory();
	//return the smart pointer
	return SmartPointer<T>(&m_actuals.back().first, m_manager, 1, 0, false);

	
}



