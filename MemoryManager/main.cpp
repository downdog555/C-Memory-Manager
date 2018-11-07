#include <stdio.h>
#include <iostream>
#include <string>
#include "MemoryManager.h"


//#include "SmartPointer.h"
struct one 
{
	int i = 0;


};
struct two
{
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;

};
class twoC 
{
public:
	twoC() 
	{
		i = 1;
		j = 1;
		k = 1;
	}
private:
	int i;
	int j;
	int k;
};
int main() 
{
	//we need to reserve memeory
	void* memory = malloc(16);
	//we then need to create a stack
	Stack stackCurrent((char*)memory, 16);
	std::cout << "Size of struct 1 is " << sizeof(one) << std::endl;
	std::cout << "Size of struct 2 is " << sizeof(two) << std::endl;
	one a;
	two b;
	two* meow2 = stackCurrent.allocate(b);

	std::cout << "Memory Remaing is " << stackCurrent.memoryRemaining() << std::endl;
	one* meow = stackCurrent.allocate(a);
	if (meow == NULL)
	{
		std::cout << "No Memory Left..." << std::endl;
	}
	else 
	{
		std::cout << "Memory Remaing is " << stackCurrent.memoryRemaining() << std::endl;
	}

	if (stackCurrent.deallocate(meow2))
	{
		//we have success
		std::cout << "Deallocation successful" << stackCurrent.memoryRemaining() <<std::endl;

	}
	else 
	{
		std::cout << "error" << std::endl;
	}
	
	free(memory);
	void* mem2 = malloc(300);
	MemoryManager manager(100,100,100,10);
	std::cout << "number of bytes left stack: " << manager.GetStackBytesLeft() << std::endl;
	std::cout << "number of bytes left db stack " << manager.GetDBStackBytesLeft() << std::endl;
	std::cout << "number of blocks left pool: " << manager.GetPoolBlocksLeft() << std::endl;
	
	//this should default to pool
	

	
	SmartPointer<double> ptr(&manager);

	*ptr = 22.0;
	std::cout << "number of blocks left pool: " << manager.GetPoolBlocksLeft() << std::endl;

	std::vector<std::string> poolAlloc = manager.DisplayPoolAlloc();
	for (int i = 0; i < poolAlloc.size(); i++) 
	{
		 
		std::cout << poolAlloc[i] << std::endl;
	}


	SmartPointer<int> ptr2(&manager);
	*ptr2 = 4;
	std::cout << "number of blocks left pool: " << manager.GetPoolBlocksLeft() << std::endl;
	poolAlloc = manager.DisplayPoolAlloc();
	for (int i = 0; i < poolAlloc.size(); i++)
	{

		std::cout << poolAlloc[i] << std::endl;
	}

	SmartPointer<float> ptr3(&manager);
	*ptr3 = 46.6;
	std::cout << "number of blocks left pool: " << manager.GetPoolBlocksLeft() << std::endl;
	 poolAlloc = manager.DisplayPoolAlloc();
	for (int i = 0; i < poolAlloc.size(); i++)
	{

		std::cout << poolAlloc[i] << std::endl;
	}
	ptr3.~SmartPointer();
	std::cout << "number of blocks left pool: " << manager.GetPoolBlocksLeft() << std::endl;
	poolAlloc = manager.DisplayPoolAlloc();
	for (int i = 0; i < poolAlloc.size(); i++)
	{

		std::cout << poolAlloc[i] << std::endl;
	}
	free(mem2);
	int i = 0;
	std::cin >> i;
	return 0;
}