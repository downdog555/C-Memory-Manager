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

ActualWrapper * SmartPointer::GetActualWrapper()
{
	return m_actualWrapper;;
}


void SmartPointer::Deallocate()
{
	delete m_p;
	delete m_actualWrapper;
	//we now need to send the message to the manager to deallocate
//TODO send message to manager
	//m_manager->deallocate(m_actual, locationType);
}


SmartPointer& SmartPointer::operator = ( SmartPointer& pointerToAssign) 
{
	// we do not want to self assign...
	if (this != &pointerToAssign) 
	{
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

bool SmartPointer::operator==( SmartPointer& pointer)
{
	if (this->GetActualComp() == pointer.GetActualComp())
	{
		return true;
	}
	return false;
}
