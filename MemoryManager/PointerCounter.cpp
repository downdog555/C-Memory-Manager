#include "PointerCounter.h"



PointerCounter::PointerCounter()
{
	count = 0;
}


PointerCounter::~PointerCounter()
{
}

void PointerCounter::increase()
{
	count++;
}

int PointerCounter::decrease()
{
	return --count;
}
