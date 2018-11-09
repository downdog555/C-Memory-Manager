#pragma once
#include <vector>
#include "ActualWrapper.h"
#include <iostream>
#include <list>
#include "SmartPointer.h"
/// <summary>
/// class representing a stack, for any object requried
/// </summary>
	class Stack
	{
	
	public:
		/// <summary>
		/// default constructor
		/// </summary>
		Stack();
		/// <summary>
		/// the correct constructor
		/// </summary>
		/// <param name="startLocation">char pointer to the start of the stack in memeory</param>
		/// <param name="numberOfBytes">the number of bytes being used for the stack</param>
		/// <param name="m">a pointer to the memeory manager creating this stack</param>
		Stack(char * startLocation, unsigned const int numberOfBytes, MemoryManager* m);
		/// <summary>
		/// destructor
		/// </summary>
		~Stack();

		template<typename T, typename... Args>
		/// <summary>
		/// Function to allocate and object and return a smart pointer
		/// </summary>
		/// <param name="objectRequired">a blank version of the object</param>
		/// <param name="...args">the extra arguments, passed to the constructor</param>
		/// <returns>a smart pointer of the correct types, initlised using the provided args</returns>
		SmartPointer<T> allocate(T objectRequired, Args... args);
		template<typename T>
		/// <summary>
		/// function to allocate object that does not require intilisation from its constructor
		/// returns a smart pointer
		/// </summary>
		/// <param name="objectRequired">a blank version of the object</param>
		/// <returns>a smart pointer of the correct type</returns>
		SmartPointer<T> allocate(T objectRequired);

		/// <summary>
		/// function to deallocate an object
		/// </summary>
		/// <param name="toRemove">a pointer to the actual wrapper</param>
		/// <returns>boolean providing success or faliure</returns>
		bool deallocate(ActualWrapper * toRemove);
		/// <summary>
		/// used to get the remaining amount of memeory
		/// </summary>
		/// <returns>int of the memeory remaining</returns>
		int memoryRemaining();
	private:
		/// <summary>
		/// function to check amount of memeory remaining
		/// </summary>
		void CheckMemeory();
		/// <summary>
		/// Start of the stack in memeory
		/// </summary>
		char* m_start;
		/// <summary>
		/// current front of stack(where we can allocate)
		/// </summary>
		char* m_current;
		/// <summary>
		/// end of the stack
		/// </summary>
		char* m_endLocation;
		/// <summary>
		/// size of the stack in bytes
		/// </summary>
		int m_sizeOfStack;
		/// <summary>
		/// pointer to the manager
		/// </summary>
		MemoryManager* m_manager;
		/// <summary>
		/// list of pairs, containg the wrapper around a pointer to the allocated classes and an int 
		/// </summary>
		std::list<std::pair<ActualWrapper, int>> m_actuals;
		//we used void pointers just to let us know where they have been allocated to, so we cna check if that is the nearest one
		//to deallocate
		
	};
	template<typename T, typename... Args>
	/// <summary>
	/// Function to allocate and object and return a smart pointer
	/// </summary>
	/// <param name="objectRequired">a blank version of the object</param>
	/// <param name="...args">the extra arguments, passed to the constructor</param>
	/// <returns>a smart pointer of the correct types, initlised using the provided args</returns>
	inline	SmartPointer<T> Stack::allocate(T objectRequired, Args... args)
	{

		//std::cout << sizeof(T) << std::endl;
		//if there is not enough space left return null
		if (m_current + sizeof(T) > m_endLocation)
		{
			return NULL;
		}
		//create a pointer to T object at the current position with args
		T *obj = new(m_current) T(args...);

		//SmartPointer(ActualWrapper<T>* actual, MemoryManager* m, int l = POOL, int index = 0, bool frontBack = false);

		//create an acutal wrapper that points to current, with size of the object as the second pair
		m_actuals.emplace_back(ActualWrapper(m_current), sizeof(T));
		//increase the current counter
		m_current += sizeof(T);
		CheckMemeory();
		//return a smart pointer of type T
		return SmartPointer<T>(&m_actuals.back().first, m_manager, 0, 0, false);
	}


	

	template<typename T>
	/// <summary>
	/// function to allocate object that does not require intilisation from its constructor
	/// returns a smart pointer
	/// </summary>
	/// <param name="objectRequired">a blank version of the object</param>
	/// <returns>a smart pointer of the correct type</returns>
	inline SmartPointer<T> Stack::allocate(T objectRequired)
	{

		//std::cout << sizeof(T) << std::endl;
		//if there is not enough space left return null
		if (m_current + sizeof(T) > m_endLocation)
		{
			return NULL;
		}
		//create a pointer to T object at the current position
		T *obj = new(m_current) T();
		
		//SmartPointer(ActualWrapper<T>* actual, MemoryManager* m, int l = POOL, int index = 0, bool frontBack = false);
		//create an acutal wrapper that points to current, with size of the object as the second pair
		m_actuals.emplace_back(ActualWrapper(m_current), sizeof(T));
		//increase the current counter
		m_current += sizeof(T);
		CheckMemeory();
		//return a smart pointer of type T
		return SmartPointer<T>(&m_actuals.back().first, m_manager, 0, 0, false);


	}


