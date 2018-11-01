#pragma once
/// <summary>
/// class representing the counter for the smart pointer.
/// </summary>
class PointerCounter
{
public:
	PointerCounter();
	~PointerCounter();
	void increase();
	int decrease();
private:
	int count;
};

