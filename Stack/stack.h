#pragma once
#include <vector>
	class stack
	{
	
	public:
		stack();
		stack(char * startLocation, unsigned const int numberOfBytes);
		~stack();
		template<class T>
		T* allocate(T objectRequired);
		template<class T>
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
	template<class T>
	/// <summary>
	/// Method To Allocate memory for a given class
	/// we need to also keep track of each allocation
	/// </summary>
	/// <param name="objectRequired">The Object To Allocate</param>
	/// <returns>A pointer to the object</returns>
	inline	T * stack::allocate(T objectRequired)
	{

		if (&m_current + sizeof(T) > &m_endLocation)
		{
			return NULL;
		}

		T *obj = new(&m_current) T();
		m_current += sizeof(T);
		return obj;



	}

	template<class T>
	inline bool stack::deallocate(T *location)
	{

		if (&location > &m_current)
		{
			return false;
		}
		if (&m_current - sizeof(T) == &location) 
		{
			//we can destruct
			*location->~T();
			location = NULL;
		}
		else 
		{
			//we cannot deallocate but we could mark for deallocation.
			return false;
		}



		return false;

	}


