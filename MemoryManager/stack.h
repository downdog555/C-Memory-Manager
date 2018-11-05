#pragma once
#include <vector>
#include <iostream>
/// <summary>
/// class representing a stack, for any object requried
/// </summary>
	class Stack
	{
	
	public:
		Stack();
		Stack(char * startLocation, unsigned const int numberOfBytes);
		~Stack();
		template<typename T, typename... Args>
		T* allocate(T objectRequired, Args... args);
		template<typename T>
		bool deallocate(T *location);
		int memoryRemaining();
	private:
		char* m_start;
		char* m_current;
		char* m_endLocation;
		int m_sizeOfStack;
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
	inline	T * Stack::allocate(T objectRequired, Args... args)
	{
		std::cout << sizeof(T) << std::endl;

		if (m_current + sizeof(T) > m_endLocation)
		{
			return NULL;
		}

		T *obj = new(m_current) T();
		m_current += sizeof(T);
		return obj;



	}

	template<typename T>
	/// <summary>
	/// function to deallocate the object from the stack with a given pointer
	/// </summary>
	/// <param name="location">the pointer to the objec to remove</param>
	/// <returns>success or faliure</returns>
	inline bool Stack::deallocate(T *location)
	{
		
		if ((char*)location > m_current)
		{
			return false;
		}
		if (m_current - sizeof(T) == (char*)location) 
		{
			//we can destruct
			location->~T();
			location = NULL;
			m_current -= sizeof(T);
			return true;
		}
		else 
		{
			//we cannot deallocate but we could mark for deallocation.
			return false;
		}



		

	}


