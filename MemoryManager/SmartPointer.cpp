#include "SmartPointer.h"
#include "PointerCounter.h"

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
	m_locationType = pointerToCopy.GetLocation();
	m_p->increase();
}




char * SmartPointer::GetActualComp()
{
	return nullptr;
}

int SmartPointer::GetIndex()
{
	return m_index;
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
		return *this;
	}
	return NULL;
}

bool SmartPointer::operator==(const SmartPointer& pointer)
{
	if (*this == pointer)
	{
		return true;
	}
	return false;
}
