#pragma once
#include <vector>
#include <iostream>
/// <summary>
/// class representing a double ended stack
/// </summary>
class DoubleStack
{

public:
	DoubleStack();
	DoubleStack(char * startLocation, unsigned const int numberOfBytes);
	~DoubleStack();
	template<typename T, typename... Args>
	T* allocateFront(T objectRequired, Args... args);
	template<typename T>
	bool deallocateFront(T *location);
	template<typename T, typename... Args>
	T* allocateBack(T objectRequired, Args... args);
	template<typename T>
	bool deallocateBack(T *location);
	int memoryRemaining();
private:
	char* m_start;
	char* m_currentFront;
	char* m_currentBack;
	char* m_endLocation;
	int m_sizeOfStack;
	//we used void pointers just to let us know where they have been allocated to, so we cna check if that is the nearest one
	//to deallocate
	std::vector<void*> allocationLocations;
};
template<typename T, typename... Args>
/// <summary>
/// Method To Allocate memory for a given class to the front 
/// we need to also keep track of each allocation
/// </summary>
/// <param name="objectRequired">The Object To Allocate</param>
/// <returns>A pointer to the object</returns>
inline	T * DoubleStack::allocateFront(T objectRequired, Args... args)
{
	std::cout << sizeof(T) << std::endl;

	if (m_currentFront + sizeof(T) > m_endLocation)
	{
		return NULL;
	}

	T *obj = new(m_currentFront) T();
	m_currentFront += sizeof(T);
	return obj;



}

template<typename T>
/// <summary>
/// Method to deallocate from the front of the stack from the front section
/// </summary>
/// <param name="location">the pointer to the object to remove</param>
/// <returns>succes or failure</returns>
inline bool DoubleStack::deallocateFront(T *location)
{

	if ((char*)location > m_currentFront)
	{
		return false;
	}
	if (m_currentFront - sizeof(T) == (char*)location)
	{
		//we can destruct
		location->~T();
		location = NULL;
		m_currentFront -= sizeof(T);
		return true;
	}
	else
	{
		//we cannot deallocate but we could mark for deallocation.
		return false;
	}





}

template<typename T, typename... Args>
/// <summary>
/// function to allocate to the back of the stack.
/// </summary>
/// <param name="objectRequired">the object to be instanciated</param>
/// <returns>a pointer to the new object</returns>
inline T * DoubleStack::allocateBack(T objectRequired, Args... args)
{

	if (m_currentBack - sizeof(T) >= m_currentFront) 
	{
		//we can go forward and allocate
		
		T *obj = new(m_currentBack - sizeof(T)) T();
		m_currentBack -= sizeof(T);
		return obj;
	}
	else 
	{
		return NULL;
	}
}

template<class T>
/// <summary>
/// method to deallocate from the back of the stack
/// </summary>
/// <param name="location">the pointer to the object to de allocate</param>
/// <returns></returns>
inline bool DoubleStack::deallocateBack(T * location)
{
	
	if (m_currentBack + sizeof(T) == (char*)location)
	{
		//we can destruct
		location->~T();
		location = NULL;
		m_currentBack += sizeof(T);
		return true;
	}
	else
	{
		//we cannot deallocate but we could mark for deallocation.
		return false;
	}
}


