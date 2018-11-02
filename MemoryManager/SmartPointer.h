#pragma once
#include "MemoryManager.h"
#include "PointerCounter.h"
#include "ActualWrapper.h"
enum Location {STACK, DB_STACK, POOL};
template <typename T>
/// <summary>
/// class representing the smart pointer
/// </summary>
class SmartPointer
{
public:
	
	SmartPointer(ActualWrapper* actual, MemoryManager* m, Location l, int index = 0);
	~SmartPointer();
	SmartPointer(const SmartPointer<T>& pointerToCopy);
	SmartPointer<T>& operator = (const SmartPointer<T>& pointerToAssign);
	bool operator==(const SmartPointer<T>& pointer);
	T& operator* ();
	T* operator->();
	T* GetActual();
	int GetIndex();
	void UpdateActual(char* actual);
	PointerCounter* GetCounter();
	MemoryManager* GetManager();
	Location GetLocation();
private:
	void Deallocate();
	ActualWrapper* m_actualWrapper;
	
	MemoryManager* m_manager;
	//0,1,2 for dif
	Location m_locationType;
	PointerCounter* m_p;
	int m_index;
};

