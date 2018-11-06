#pragma once

class ActualWrapper
{
public:

	ActualWrapper(char * actualPointer);

	void UpdateActual(char * actualPointer);

	char * GetActual();

	char* GetActualComp();

	~ActualWrapper();
private:
	char * m_actual;
};

