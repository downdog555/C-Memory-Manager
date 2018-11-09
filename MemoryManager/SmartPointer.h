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
	template<typename... Args>
	/// <summary>
	/// Constructor for smart pointer
	/// </summary>
	/// <param name="manager">reference to the memeory manager</param>
	/// <param name="loc">location for object to be stored</param>
	/// <param name="frontBack">fornt back for db stack, defaults to false</param>
	/// <param name="...args">args for the consttructor of object</param>
	SmartPointer( MemoryManager* manager, int loc = 2, bool frontBack = false, Args... args);

	/// <summary>
	/// constructor for smart pointer
	/// </summary>
	/// <param name="manager">reference to the memeory manager</param>
	/// <param name="loc">location for object to be stored</param>
	/// <param name="frontBack">fornt back for db stack, defaults to false</param>
	SmartPointer(MemoryManager* manager, int loc = 2, bool frontBack = false);
	/// <summary>
	/// constructor for creating the smart pointer in a data structure
	/// </summary>
	/// <param name="actual">actual wrapper pointere</param>
	/// <param name="m">pointer to the memeory manager</param>
	/// <param name="l">int for location of where to store</param>
	/// <param name="index">block index if applicable</param>
	/// <param name="frontBack">fronmt back bool for db stack</param>
	SmartPointer(ActualWrapper* actual, MemoryManager* m, int l = POOL, int index = 0, bool frontBack = false);
	/// <summary>
	/// default constructor
	/// </summary>
	SmartPointer();
	/// <summary>
	/// destructor
	/// </summary>
	~SmartPointer();
	/// <summary>
	/// copy constructor
	/// </summary>
	/// <param name="pointerToCopy">pointer to copy</param>
	SmartPointer(const SmartPointer<T>& pointerToCopy);
	/// <summary>
	/// assignment operator
	/// </summary>
	/// <param name="pointerToAssign">pointer to assign</param>
	/// <returns>reference to smart pointer</returns>
	SmartPointer<T>& operator= (const SmartPointer<T>& pointerToAssign);
	/// <summary>
	/// equality operator
	/// </summary>
	/// <param name="pointer"></param>
	/// <returns></returns>
	bool operator==( SmartPointer<T>& pointer);
	/// <summary>
	/// deref operator
	/// </summary>
	/// <returns>reference to object</returns>
	T& operator *();
	/// <summary>
	/// returns pointer to object
	/// </summary>
	/// <returns></returns>
	T* operator ->();
	/// <summary>
	/// returns T*
	/// </summary>
	/// <returns>T*</returns>
	T* GetActual();
	/// <summary>
	/// gets char pointer of actual
	/// </summary>
	/// <returns>char*</returns>
	char* GetActualComp();
	/// <summary>
	/// gets the index of the stroage block if applicable
	/// </summary>
	/// <returns>index</returns>
	int GetIndex();

	/// <summary>
	/// gets pointer to counter
	/// </summary>
	/// <returns>PointerCounter*</returns>
	PointerCounter * GetCounter();
	/// <summary>
	/// gets a pointer to the memeory manager
	/// </summary>
	/// <returns>MemeoryManager*</returns>
	MemoryManager * GetManager();
	/// <summary>
	/// Gets the front back bool
	/// </summary>
	/// <returns>m_front back</returns>
	bool GetFrontBack();
	/// <summary>
	/// Gets the stroage location
	/// </summary>
	/// <returns>int location</returns>
	int GetLocation();
	/// <summary>
	/// Gets the actual wrapper
	/// </summary>
	/// <returns>ActualWrapper*</returns>
	ActualWrapper*  GetActualWrapper();
	bool m_frontBack;
private:
	/// <summary>
	/// function to allocate
	/// </summary>
	/// <param name="actual">the actual wrapper to dealloc</param>
	void Deallocate(ActualWrapper* actual);
	/// <summary>
	/// actual wrappper *
	/// </summary>
	ActualWrapper*  m_actualWrapper;
	/// <summary>
	/// memory manager *
	/// </summary>
	MemoryManager * m_manager;
	//0,1,2 for dif
	/// <summary>
	/// storage location
	/// </summary>
	int m_locationType;
	/// <summary>
	/// pointer to  hte counter
	/// </summary>
	PointerCounter * m_p;
	/// <summary>
	/// block index if applicable
	/// </summary>
	int m_index;
};




template<typename T>

/// <summary>
/// constructor for smart pointer
/// </summary>
/// <param name="manager">reference to the memeory manager</param>
/// <param name="loc">location for object to be stored</param>
/// <param name="frontBack">fornt back for db stack, defaults to false</param>
inline SmartPointer<T>::SmartPointer(MemoryManager * manager, int loc, bool frontBack)
{
	std::cout << "Creation with smart pointer declaration1" << std::endl;
	//we need to request a new smart pointer from the correct cache and what not....
	T type{};
	//call manager allocate function 
	*this = SmartPointer<T>(manager->Allocate(type, loc, frontBack));

}

template<typename T>
/// <summary>
/// constructor for creating the smart pointer in a data structure
/// </summary>
/// <param name="actual">actual wrapper pointere</param>
/// <param name="m">pointer to the memeory manager</param>
/// <param name="l">int for location of where to store</param>
/// <param name="index">block index if applicable</param>
/// <param name="frontBack">fronmt back bool for db stack</param>
inline SmartPointer<T>::SmartPointer(ActualWrapper* const actual, MemoryManager* m, int l, int index, bool frontBack)
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
/// <summary>
/// Default constructor
/// </summary>
inline SmartPointer<T>::SmartPointer()
{
}

template<typename T>
/// <summary>
/// function to allocate
/// </summary>
/// <param name="actual">the actual wrapper to dealloc</param>
 inline void SmartPointer<T>::Deallocate(ActualWrapper * actual)
{

	
	 //gets actual wrapper 
	 ActualWrapper * temp = m_actualWrapper;
	 m_manager->Deallocate(actual, m_locationType, m_frontBack);

	//we now need to send the message to the manager to deallocate
	//TODO send message to manager
	//m_manager->deallocate(m_actual, locationType);
}

template<typename T>
/// <summary>
/// deref operator
/// </summary>
/// <returns>reference to object</returns>
inline T & SmartPointer<T>::operator*()
{

	
	return *(T*)m_actualWrapper->GetActual();
}

template<typename T>
/// <summary>
/// returns pointer to object
/// </summary>
/// <returns></returns>
inline T * SmartPointer<T>::operator->()
{
	T * actual = (T*)m_actualWrapper->GetActual();
	return actual;
}

template<typename T>
/// <summary>
/// returns T*
/// </summary>
/// <returns>T*</returns>
inline T * SmartPointer<T>::GetActual()
{
	return *m_actualWrapper->GetActual();
}






template<typename T>
template<typename ...Args>
/// <summary>
/// Constructor for smart pointer
/// </summary>
/// <param name="manager">reference to the memeory manager</param>
/// <param name="loc">location for object to be stored</param>
/// <param name="frontBack">fornt back for db stack, defaults to false</param>
/// <param name="...args">args for the consttructor of object</param>
inline SmartPointer<T>::SmartPointer(MemoryManager * manager, int loc, bool frontBack,Args... args)
{
	//std::cout << "Creation with smart pointer declaration1" << std::endl;
	//we need to request a new smart pointer from the correct cache and what not....
	T type{};
	//call for allocation
	*this = SmartPointer<T>(manager->Allocate(type, loc, frontBack,args...));
}
template<typename T>
/// <summary>
/// destructor
/// </summary>
inline SmartPointer<T>::~SmartPointer()
{
	//if there are no more references
	if (m_p->decrease() == 0)
	{
		//we can send a note to the memeory manager to remove them....
		Deallocate(m_actualWrapper);
		//remove all pointers now
		//delete m_actualWrapper;
		//delete m_manager;
		//delete m_manager;
		//delete m_p;

	}
	
}

template<typename T>
/// <summary>
/// copy constructor
/// </summary>
/// <param name="pointerToCopy"></param>
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
/// <summary>
/// gets char pointer of actual
/// </summary>
/// <returns>char*</returns>
inline char * SmartPointer<T>::GetActualComp()
{
	return m_actualWrapper->GetActualComp();
}
template<typename T>
/// <summary>
/// gets block index if applicable
/// </summary>
/// <returns></returns>
inline int SmartPointer<T>::GetIndex()
{
	return m_index;
}

template<typename T>
/// <summary>
/// gets counter if applicable
/// </summary>
/// <returns>counter*</returns>
PointerCounter * SmartPointer<T>::GetCounter()
{
	return m_p;
}

template<typename T>
/// <summary>
/// gets manager pointer
/// </summary>
/// <returns>memeorymanager*</returns>
MemoryManager * SmartPointer<T>::GetManager()
{
	return m_manager;
}

template<typename T>
/// <summary>
/// gets front back bool
/// </summary>
/// <returns>front back bool</returns>
inline bool SmartPointer<T>::GetFrontBack()
{
	return m_frontBack;
}

template<typename T>
/// <summary>
/// gets storage location
/// </summary>
/// <returns>int</returns>
int SmartPointer<T>::GetLocation()
{
	return m_locationType;
}
template<typename T>
/// <summary>
/// gets the actual wrapper
/// </summary>
/// <returns>Actual wrapper*</returns>
inline  ActualWrapper *  SmartPointer<T>::GetActualWrapper()
{
	return m_actualWrapper;
}






template<typename T>
/// <summary>
/// assigment operator
/// </summary>
/// <param name="pointerToAssign"></param>
/// <returns></returns>
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
/// <summary>
/// equaltiy operator
/// </summary>
/// <param name="pointer">pointer to compare</param>
/// <returns></returns>
inline bool SmartPointer<T>::operator==(SmartPointer& pointer)
{
	if (this->GetActualComp() == pointer.GetActualComp())
	{
		return true;
	}
	return false;
}
