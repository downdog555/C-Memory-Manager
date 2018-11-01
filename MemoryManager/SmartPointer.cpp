#include "SmartPointer.h"
#include "PointerCounter.h"




template<typename T>
SmartPointer<T>::SmartPointer(T * value, MemoryManager* m, Location l)
{
	m_actual = value;
	m_p = new PointerCounter();
	m_p->increase();
	m_manager = m;
	m_locationType = l;
}

template<typename T>
SmartPointer::~SmartPointer()
{
	if (m_p->decrease() == 0) 
	{
		//we can send a note to the memeory manager to remove them....
		Deallocate();
	}
}
template<typename T>
SmartPointer<T>::SmartPointer(const SmartPointer<T>& pointerToCopy)
{
	m_actual = pointerToCopy->GetActual();
	m_p = pointerToCopy->GetCounter();
	m_manager = pointerToCopy->GetManager();
	m_locationType = pointerToCopy->GetLocation;;
	m_p->increase();
}

template<typename T>
T & SmartPointer<T>::operator*()
{
	return *actual;
}

template<typename T>
T * SmartPointer<T>::operator->()
{
	return actual;
}

template<typename T>
T * SmartPointer<T>::GetActual()
{
	return m_actual;
}

template<typename T>
PointerCounter * SmartPointer<T>::GetCounter()
{
	return p;
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
void SmartPointer<T>::Deallocate()
{
	delete m_p;
	//we now need to send the message to the manager to deallocate
	m_manager->deallocate(m_actual, locationType);
}

template<typename T>
SmartPointer<T>& SmartPointer<T>::operator = (const SmartPointer<T>& pointerToAssign) 
{
	// we do not want to self assign...
	if (this != &pointerToAssign) 
	{
		//we need to decrease the counter so that for assignment within a code block there is not an inaccurate count
		if(m_p->decrease() == 0)
		{
			//we need to send message
			Deallocate();
		}
	}
	return *this;
}