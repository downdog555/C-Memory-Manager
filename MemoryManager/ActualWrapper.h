#pragma once

class ActualWrapper
{
public:
	ActualWrapper();
	ActualWrapper(char * actualPointer);
	ActualWrapper * GetWrapper();
	void UpdateActual(char * actualPointer);

	char * GetActual();

	char* GetActualComp();

	~ActualWrapper();
private:
	char * m_actual;
};

