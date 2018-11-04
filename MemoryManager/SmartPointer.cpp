#include "SmartPointer.h"
#include "PointerCounter.h"
template<typename T>
SmartPointer<T>::~SmartPointer()
{
	if (m_p->decrease() == 1) 
	{
		//we can send a note to the memeory manager to remove them....
		Deallocate();
	}
}
template<typename T>
SmartPointer<T>::SmartPointer( SmartPointer<T>& pointerToCopy)
{
	
	this->m_p = pointerToCopy.GetCounter();
	
	this->m_manager = pointerToCopy.GetManager();
	this->m_locationType = pointerToCopy.GetLocation();
	this->m_p->increase();
}



template<typename T>
char * SmartPointer<T>::GetActualComp()
{
	return m_actualWrapper->GetActualComp();
}
template<typename T>
int SmartPointer<T>::GetIndex()
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
Location SmartPointer<T>::GetLocation()
{
	return m_locationType;
}
template<typename T>
ActualWrapper<T> * SmartPointer<T>::GetActualWrapper()
{
	return m_actualWrapper;
}



template <typename T>
SmartPointer<T>& SmartPointer<T>::operator = ( SmartPointer<T>& pointerToAssign) 
{
	// we do not want to self assign...
	if (this != &pointerToAssign) 
	{
		T* temp = pointerToAssign.GetActual();
		//we should have 1 refernece left in the pool stack ir double stack
		if (m_p->decrease() == 1)
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
bool SmartPointer<T>::operator==( SmartPointer& pointer)
{
	if (this->GetActualComp() == pointer.GetActualComp())
	{
		return true;
	}
	return false;
}
