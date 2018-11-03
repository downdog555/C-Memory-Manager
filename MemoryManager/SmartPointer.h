#pragma once
#include "MemoryManager.h"
#include "PointerCounter.h"
#include "ActualWrapper.h"
enum Location {STACK, DB_STACK, POOL};

/// <summary>
/// class representing the smart pointer
/// </summary>
class SmartPointer
{
public:
	template <typename T>
	SmartPointer(ActualWrapper<T>* actual, MemoryManager* m, Location l, int index = 0);
	~SmartPointer();
	SmartPointer( SmartPointer& pointerToCopy);
	SmartPointer& operator = (const SmartPointer& pointerToAssign);
	bool operator==(const SmartPointer& pointer);
	template <typename T>
	T& operator* ();
	template <typename T>
	T* operator->();
	template <typename T>
	T* GetActual();
	int GetIndex();
	void UpdateActual(char* actual);
	PointerCounter* GetCounter();
	MemoryManager* GetManager();
	Location GetLocation();
private:
	void Deallocate();
	template <typename T>
	ActualWrapper<T>* m_actualWrapper;
	
	MemoryManager* m_manager;
	//0,1,2 for dif
	Location m_locationType;
	PointerCounter* m_p;
	int m_index;
};

