#include "PointerCounter.h"


/// <summary>
/// Default Constructor
/// </summary>
PointerCounter::PointerCounter()
{
	count = 0;
}

/// <summary>
/// destructor
/// </summary>
PointerCounter::~PointerCounter()
{
}
/// <summary>
/// increases the count
/// </summary>
void PointerCounter::increase()
{
	count++;
}
/// <summary>
/// decreases the count
/// </summary>
/// <returns>the new value</returns>
int PointerCounter::decrease()
{
	return --count;
}
