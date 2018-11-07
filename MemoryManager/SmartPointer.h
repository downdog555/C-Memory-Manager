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
	SmartPointer(ActualWrapper* actual, MemoryManager* m, int l = POOL, int index = 0, bool frontBack = false);
	SmartPointer();
	~SmartPointer();

	SmartPointer(const SmartPointer<T>& pointerToCopy);

	SmartPointer<T>& operator= (const SmartPointer<T>& pointerToAssign);
	bool operator==( SmartPointer<T>& pointer);

	T& operator *();

	T* operator ->();

	T* GetActual();

	char* GetActualComp();
	int GetIndex();


	PointerCounter * GetCounter();
	MemoryManager * GetManager();
	bool GetFrontBack();
	int GetLocation();
	ActualWrapper*  GetActualWrapper();
	bool m_frontBack;
private:

	void Deallocate();

	ActualWrapper* m_actualWrapper;
	
	MemoryManager * m_manager;
	//0,1,2 for dif
	int m_locationType;
	PointerCounter * m_p;
	int m_index;
};




template<typename T>
inline SmartPointer<T>::SmartPointer(MemoryManager * manager, int loc)
{
	std::cout << "Creation with smart pointer declaration1" << std::endl;
	//we need to request a new smart pointer from the correct cache and what not....
	T type{};

	*this = SmartPointer<T>(manager->Allocate(type, loc, false));

}

template<typename T>
inline SmartPointer<T>::SmartPointer(ActualWrapper* actual, MemoryManager* m, int l, int index, bool frontBack)
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

	 //raise exception if we cannot dealloc
	 m_manager->Deallocate(m_actualWrapper,m_locationType,m_frontBack);
	//we now need to send the message to the manager to deallocate
	//TODO send message to manager
	//m_manager->deallocate(m_actual, locationType);
}

template<typename T>
inline T & SmartPointer<T>::operator*()
{

	
	return *(T*)m_actualWrapper->GetActual();
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
template<typename ...Args>
inline SmartPointer<T>::SmartPointer(MemoryManager * manager, int loc, Args... args)
{
	std::cout << "Creation with smart pointer declaration" << std::endl;
	//we need to request a new smart pointer from the correct cache and what not....
	T type{};
	this = manager.Allocate(type,loc, false, args...);
}
template<typename T>
inline SmartPointer<T>::~SmartPointer()
{
	if (m_p->decrease() == 0)
	{
		//we can send a note to the memeory manager to remove them....
		Deallocate();
		//remove all pointers now
	
	//delete m_manager;
		//delete m_p;

	}
	
}

template<typename T>
inline SmartPointer<T>::SmartPointer(const SmartPointer<T>& pointerToCopy)
{
	m_p = pointerToCopy.m_p;
	m_actualWrapper = pointerToCopy.m_actualWrapper;
	m_manager = pointerToCopy.m_manager;
	m_locationType = pointerToCopy.m_locationType;
	m_index = pointerToCopy.m_index;
	m_frontBack = pointerToCopy.m_frontBack;
	m_p->increase();
	
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
inline bool SmartPointer<T>::GetFrontBack()
{
	return m_frontBack;
}

template<typename T>
int SmartPointer<T>::GetLocation()
{
	return m_locationType;
}
template<typename T>
inline  ActualWrapper *  SmartPointer<T>::GetActualWrapper()
{
	return m_actualWrapper;
}






template<typename T>
inline SmartPointer<T>& SmartPointer<T>::operator=(const SmartPointer<T>& pointerToAssign)
{
	// we do not want to self assign...
	if (this != &pointerToAssign)
	{
		
		

		m_p = pointerToAssign.m_p;
		m_actualWrapper = pointerToAssign.m_actualWrapper;
		m_manager = pointerToAssign.m_manager;
		m_locationType = pointerToAssign.m_locationType;
		m_index = pointerToAssign.m_index;
		m_frontBack = pointerToAssign.m_frontBack;
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
