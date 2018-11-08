#pragma once
/// <summary>
/// Class Wrapping around a char pointer so it can be relocated
/// </summary>
class ActualWrapper
{
public:
	/// <summary>
	/// default constructor
	/// </summary>
	ActualWrapper();
	/// <summary>
	/// Correct Constructor
	/// </summary>
	/// <param name="actualPointer">the pointer of the object</param>
	ActualWrapper(char * actualPointer);
	/// <summary>
	/// returns a pointer to this wrapper
	/// </summary>
	/// <returns>a pointer to this wrapper</returns>
	ActualWrapper * GetWrapper();
	/// <summary>
	/// updates the actual pointer
	/// </summary>
	/// <param name="actualPointer">new pointer</param>
	void UpdateActual(char * actualPointer);
	/// <summary>
	/// gets the actual char*
	/// </summary>
	/// <returns>the actual char*</returns>
	char * GetActual();
	/// <summary>
	/// Depricated
	/// </summary>
	/// <returns></returns>
	char* GetActualComp();
	/// <summary>
	/// destructor
	/// </summary>
	~ActualWrapper();
private:
	/// <summary>
	/// pointer of the actual value
	/// </summary>
	char * m_actual;
};

