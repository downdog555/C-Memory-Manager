#pragma once
#include <vector>
#include "ActualWrapper.h"
#include <iostream>
#include "SmartPointer.h"
/// <summary>
/// class representing a stack, for any object requried
/// </summary>
	class Stack
	{
	
	public:
		Stack();
		Stack(char * startLocation, unsigned const int numberOfBytes, MemoryManager* m);
		~Stack();
		template<typename T, typename... Args>
		SmartPointer<T> allocate(T objectRequired, Args... args);
		template<typename T>
		SmartPointer<T> allocate(T objectRequired);

		bool deallocate(ActualWrapper * toRemove);
		int memoryRemaining();
	private:
		char* m_start;
		char* m_current;
		char* m_endLocation;
		int m_sizeOfStack;
		MemoryManager* m_manager;
		std::vector<std::pair<ActualWrapper, int>> actuals;
		//we used void pointers just to let us know where they have been allocated to, so we cna check if that is the nearest one
		//to deallocate
		std::vector<void*> allocationLocations;
	};
	template<typename T, typename... Args>
	/// <summary>
	/// Method To Allocate memory for a given class
	/// we need to also keep track of each allocation
	/// </summary>
	/// <param name="objectRequired">The Object To Allocate</param>
	/// <returns>A pointer to the object</returns>
	inline	SmartPointer<T> Stack::allocate(T objectRequired, Args... args)
	{

		std::cout << sizeof(T) << std::endl;

		if (m_current + sizeof(T) > m_endLocation)
		{
			return NULL;
		}

		T *obj = new(m_current) T(args...);
		m_current += sizeof(T);
		return obj;







		//SmartPointer(ActualWrapper<T>* actual, MemoryManager* m, int l = POOL, int index = 0, bool frontBack = false);
		ActualWrapper actual(start);
		//SmartPointer<T> temp(&actual, m_manager, 2, startBlock, false);
		std::pair<ActualWrapper, int> tempPair(actual, sizeof(T));

		actuals.push_back(tempPair);
		int index = actuals.size() - 1;
		return SmartPointer<T>(actuals[index].first.GetWrapper(), m_manager, 0, startBlock, false);
	}


	

	template<typename T>
	inline SmartPointer<T> Stack::allocate(T objectRequired)
	{

		std::cout << sizeof(T) << std::endl;

		if (m_current + sizeof(T) > m_endLocation)
		{
			return NULL;
		}

		T *obj = new(m_current) T();
		m_current += sizeof(T);
		//SmartPointer(ActualWrapper<T>* actual, MemoryManager* m, int l = POOL, int index = 0, bool frontBack = false);
		ActualWrapper actual(m_current);
		//SmartPointer<T> temp(&actual, m_manager, 2, startBlock, false);
		std::pair<ActualWrapper, int> tempPair(actual, sizeof(T));

		actuals.push_back(tempPair);
		int index = actuals.size() - 1;
		return SmartPointer<T>(actuals[index].first.GetWrapper(), m_manager, 0, 0, false);
	}


