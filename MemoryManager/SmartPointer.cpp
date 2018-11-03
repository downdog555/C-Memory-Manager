#include "SmartPointer.h"
#include "PointerCounter.h"




template<typename T>
SmartPointer::SmartPointer(ActualWrapper<T>* actual, MemoryManager* m, Location l, int index = 0, bool frontBack = false)
{
	m_actualWrapper = actual;
	m_p = new PointerCounter();
	m_p->increase();
	m_manager = m;
	m_locationType = l;
	m_index = index;
	m_listIndex = listIndex;
	m_frontBack = frontBack;
}

template<typename T>
SmartPointer::~SmartPointer()
{
	if (m_p->decrease() == 1) 
	{
		//we can send a note to the memeory manager to remove them....
		Deallocate();
	}
}

SmartPointer::SmartPointer( SmartPointer& pointerToCopy)
{
	
	m_p = pointerToCopy.GetCounter();
	m_manager = pointerToCopy.GetManager();
	m_locationType = pointerToCopy.GetLocation;;
	m_p->increase();
}

template<typename T>
T & SmartPointer::operator*()
{
	T * actual = *m_actualWrapper->GetActual();
	return *actual;
}

template<typename T>
T * SmartPointer::operator->()
{
	T * actual = *m_actualWrapper->GetActual();
	return actual;
}

template<typename T>
T * SmartPointer::GetActual()
{
	return *m_actualWrapper->GetActual();
}




int SmartPointer::GetIndex()
{
	return m_index;
}

template<typename T>
void SmartPointer::UpdateActual(char * actual)
{
	m_actualWrapper<T>->UpdateActual(actual);
}


PointerCounter * SmartPointer::GetCounter()
{
	return m_p;
}


MemoryManager * SmartPointer::GetManager()
{
	return m_manager;
}


Location SmartPointer::GetLocation()
{
	return m_locationType;
}


void SmartPointer::Deallocate()
{
	delete m_p;
	//we now need to send the message to the manager to deallocate
	//m_manager->deallocate(m_actual, locationType);
}


SmartPointer& SmartPointer::operator = (const SmartPointer& pointerToAssign) 
{
	// we do not want to self assign...
	if (this != &pointerToAssign) 
	{
		return this;
	}
	return NULL;
}

template<typename T>
bool SmartPointer::operator==(const SmartPointer& pointer)
{
	if (this.m_actualWrapper.GetActual() == pointer.GetActual())
	{
		return true
	}
	return false;
}

