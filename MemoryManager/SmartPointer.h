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
	
	SmartPointer(T* value, MemoryManager* m, Location l, int index = 0);
	~SmartPointer();
	SmartPointer(const SmartPointer<T>& pointerToCopy);
	SmartPointer<T>& operator = (const SmartPointer<T>& pointerToAssign);
	bool operator==(const SmartPointer<T>& pointer);
	T& operator* ();
	T* operator->();
	T* GetActual();
	int GetIndex();
	void UpdateActual();
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
	int m_index;
};

