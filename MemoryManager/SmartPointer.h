#pragma once
#include "MemoryManager.h"
#include "PointerCounter.h"
enum Location {STACK, DB_STACK, POOL};
template <typename T>
/// <summary>
/// class representing the smart pointer
/// </summary>
class SmartPointer
{
public:
	
	SmartPointer(T* value, MemoryManager* m, Location l);
	~SmartPointer();
	SmartPointer(const SmartPointer<T>& pointerToCopy);
	SmartPointer<T>& operator = (const SmartPointer<T>& pointerToAssign)
	T& operator* ();
	T* operator->();
	T* GetActual();

	PointerCounter* GetCounter();
	MemoryManager* GetManager();
	Location GetLocation();
private:
	void Deallocate();
	T * m_actual;
	MemoryManager* m_manager;
	//0,1,2 for dif
	Location m_locationType;
	PointerCounter* m_p;
};

