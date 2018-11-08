#pragma once
/// <summary>
/// class representing the counter for the smart pointer.
/// </summary>
class PointerCounter
{
public:
	/// <summary>
	/// Default Constructor
	/// </summary>
	PointerCounter();
	/// <summary>
	/// Destructor
	/// </summary>
	~PointerCounter();
	/// <summary>
	/// increases the count
	/// </summary>
	void increase();
	/// <summary>
	/// decreases the count
	/// </summary>
	/// <returns>the new value</returns>
	int decrease();
private:
	/// <summary>
	/// count
	/// </summary>
	int count;
};

