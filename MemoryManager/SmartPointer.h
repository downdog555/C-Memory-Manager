#pragma once
#include "ActualWrapper.h"
#include "PointerCounter.h"

enum Location { STACK, DB_STACK, POOL };
class MemoryManager;
/// <summary>
/// class representing the smart pointer
/// </summary>
template<typename T>
class SmartPointer
{
public:
	
	/// <summary>
	/// used to request a smart pointer of a certain type...
	/// </summary>
	/// <param name="type">the object to be requested</param>
	/// <param name="manager">the memeory manger in use</param>
	SmartPointer(T* type, MemoryManager* manager, Location loc = 2);

	SmartPointer(ActualWrapper<T>* actual, MemoryManager* m, Location l, int index = 0, bool frontBack = false);
	
	~SmartPointer();

	SmartPointer(SmartPointer& pointerToCopy);

	SmartPointer& operator = ( SmartPointer& pointerToAssign);
	bool operator==( SmartPointer& pointer);

	T& operator *();

	T* operator ->();

	T* GetActual();

	char* GetActualComp();
	int GetIndex();

	void UpdateActual(T* actual);
	PointerCounter * GetCounter();
	MemoryManager * GetManager();
	Location GetLocation();
	ActualWrapper<T>* GetActualWrapper();
	bool m_frontBack;
private:

	void Deallocate();

	ActualWrapper<T>* m_actualWrapper;
	
	MemoryManager * m_manager;
	//0,1,2 for dif
	Location m_locationType;
	PointerCounter * m_p;
	int m_index;
};


template<typename T>
inline SmartPointer<T>::SmartPointer(T * type, MemoryManager * manager, Location loc)
{
	//we need to request a new smart pointer from the correct cache and what not....

}

template<typename T>
inline SmartPointer<T>::SmartPointer(ActualWrapper<T>* actual, MemoryManager* m, Location l, int index, bool frontBack)
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
 inline void SmartPointer<T>::Deallocate()
{
	
	//we now need to send the message to the manager to deallocate
	//TODO send message to manager
	//m_manager->deallocate(m_actual, locationType);
}

template<typename T>
inline T & SmartPointer<T>::operator*()
{
	T * actual = *m_actualWrapper->GetActual();
	return *actual;
}

template<typename T>
inline T * SmartPointer<T>::operator->()
{
	T * actual = *m_actualWrapper->GetActual();
	return actual;
}

template<typename T>
inline T * SmartPointer<T>::GetActual()
{
	return *m_actualWrapper->GetActual();
}




template<typename T>
inline void SmartPointer<T>::UpdateActual(T * actual)
{
	m_actualWrapper->UpdateActual(actual);
}

