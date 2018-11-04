#pragma once
#include "ActualWrapper.h"
#include "PointerCounter.h"

enum Location { STACK, DB_STACK, POOL };
class MemoryManager;
/// <summary>
/// class representing the smart pointer
/// </summary>
class SmartPointer
{
public:
	template<typename T>
	/// <summary>
	/// used to request a smart pointer of a certain type...
	/// </summary>
	/// <param name="type">the object to be requested</param>
	/// <param name="manager">the memeory manger in use</param>
	SmartPointer(T* type, MemoryManager* manager, Location loc = 2);
	
	SmartPointer(ActualWrapper* actual, MemoryManager* m, Location l, int index , bool frontBack );

	~SmartPointer();
	SmartPointer(SmartPointer& pointerToCopy);
	SmartPointer& operator = ( SmartPointer& pointerToAssign);
	bool operator==( SmartPointer& pointer);
	template <typename T>
	T& operator *();
	template <typename T>
	T* operator ->();
	template <typename T>
	T* GetActual();

	char* GetActualComp();
	int GetIndex();
	template<typename T>
	void UpdateActual(T* actual);
	PointerCounter * GetCounter();
	MemoryManager * GetManager();
	Location GetLocation();
	ActualWrapper* GetActualWrapper();
	bool m_frontBack;
private:
	void Deallocate();
	
	ActualWrapper* m_actualWrapper;
	
	MemoryManager * m_manager;
	//0,1,2 for dif
	Location m_locationType;
	PointerCounter * m_p;
	int m_index;
};


template<typename T>
inline SmartPointer::SmartPointer(T * type, MemoryManager * manager, Location loc)
{
	//we need to request a new smart pointer from the correct cache and what not....

}


SmartPointer::SmartPointer(ActualWrapper* actual, MemoryManager* m, Location l, int index = 0, bool frontBack = false)
{
	m_actualWrapper = actual;
	m_p = new PointerCounter();
	m_p->increase();
	m_manager = m;
	m_locationType = l;
	m_index = index;

	m_frontBack = frontBack;
}



template<typename T>
inline T & SmartPointer::operator*()
{
	T * actual = *m_actualWrapper->GetActual();
	return *actual;
}

template<typename T>
inline T * SmartPointer::operator->()
{
	T * actual = *m_actualWrapper->GetActual();
	return actual;
}

template<typename T>
inline T * SmartPointer::GetActual()
{
	return *m_actualWrapper->GetActual();
}




template<typename T>
inline void SmartPointer::UpdateActual(T * actual)
{
	m_actualWrapper->UpdateActual(actual);
}

