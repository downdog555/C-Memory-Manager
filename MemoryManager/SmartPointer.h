#pragma once
#include "ActualWrapper.h"
#include "PointerCounter.h"
#include <iostream>

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
	/// 
	template<typename... Args>
	SmartPointer( MemoryManager* manager, int loc = POOL, Args... args);


	SmartPointer(MemoryManager* manager, int loc = POOL);
	SmartPointer(ActualWrapper<T>* actual, MemoryManager* m, int l = POOL, int index = 0, bool frontBack = false);
	SmartPointer();
	~SmartPointer();

	SmartPointer(const SmartPointer<T>& pointerToCopy);

	SmartPointer<T>& operator= ( SmartPointer<T>& pointerToAssign);
	bool operator==( SmartPointer<T>& pointer);

	T& operator *();

	T* operator ->();

	T* GetActual();

	char* GetActualComp();
	int GetIndex();

	void UpdateActual(T* actual);
	PointerCounter * GetCounter();
	MemoryManager * GetManager();
	int GetLocation();
	ActualWrapper<T>* GetActualWrapper();
	bool m_frontBack;
private:

	void Deallocate();

	ActualWrapper<T>* m_actualWrapper;
	
	MemoryManager * m_manager;
	//0,1,2 for dif
	int m_locationType;
	PointerCounter * m_p;
	int m_index;
};




template<typename T>
inline SmartPointer<T>::SmartPointer(MemoryManager * manager, int loc)
{
	std::cout << "Creation with smart pointer declaration" << std::endl;
	//we need to request a new smart pointer from the correct cache and what not....
	T type;
	SmartPointer<T> temp(manager->Allocate(type, loc, false));
	
	m_p = temp.GetCounter();
	m_actualWrapper = temp.GetActualWrapper();
	m_manager = temp.GetManager();
	m_locationType = temp.GetLocation();
	m_p->increase();



	

}

template<typename T>
inline SmartPointer<T>::SmartPointer(ActualWrapper<T>* actual, MemoryManager* m, int l, int index, bool frontBack)
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
inline SmartPointer<T>::SmartPointer()
{
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

template<typename T>
template<typename ...Args>
inline SmartPointer<T>::SmartPointer(MemoryManager * manager, int loc, Args... args)
{
	std::cout << "Creation with smart pointer declaration" << std::endl;
	//we need to request a new smart pointer from the correct cache and what not....
	T type;
	this = *manager.Allocate(type,loc, false, args);
}template<typename T>
inline SmartPointer<T>::~SmartPointer()
{
	if (m_p->decrease() == 1)
	{
		//we can send a note to the memeory manager to remove them....
		Deallocate();
	}
}
template<typename T>
inline SmartPointer<T>::SmartPointer(const SmartPointer<T>& pointerToCopy)
{

	this->m_p = pointerToCopy.GetCounter();

	this->m_manager = pointerToCopy.GetManager();
	this->m_locationType = pointerToCopy.GetLocation();
	this->m_p->increase();
}



template<typename T>
inline char * SmartPointer<T>::GetActualComp()
{
	return m_actualWrapper->GetActualComp();
}
template<typename T>
inline int SmartPointer<T>::GetIndex()
{
	return m_index;
}

template<typename T>
PointerCounter * SmartPointer<T>::GetCounter()
{
	return m_p;
}

template<typename T>
MemoryManager * SmartPointer<T>::GetManager()
{
	return m_manager;
}

template<typename T>
int SmartPointer<T>::GetLocation()
{
	return m_locationType;
}
template<typename T>
inline ActualWrapper<T> * SmartPointer<T>::GetActualWrapper()
{
	return m_actualWrapper;
}






template<typename T>
inline SmartPointer<T>& SmartPointer<T>::operator=( SmartPointer<T>& pointerToAssign)
{
	// we do not want to self assign...
	if (this != &pointerToAssign)
	{
		T* temp = pointerToAssign.GetActual();
		//we should have 1 refernece left in the pool stack ir double stack
		if (m_p != NULL && m_p->decrease() == 1)
		{

			//we can send a note to the memeory manager to remove them....
			Deallocate();
		}

		m_p = pointerToAssign.GetCounter();
		m_actualWrapper = pointerToAssign.GetActualWrapper();
		m_manager = pointerToAssign.GetManager();
		m_locationType = pointerToAssign.GetLocation();
		m_p->increase();

	}
	return *this;
}

template<typename T>
inline bool SmartPointer<T>::operator==(SmartPointer& pointer)
{
	if (this->GetActualComp() == pointer.GetActualComp())
	{
		return true;
	}
	return false;
}
