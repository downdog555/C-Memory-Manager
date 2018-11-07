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

	void* mem2 = malloc(300);
	MemoryManager manager(100, 100, 100, 10);
	std::cout << "Size of struct 1 is " << sizeof(one) << std::endl;
	std::cout << "Size of struct 2 is " << sizeof(two) << std::endl;
	

	SmartPointer<two> test(&manager,0);
	std::cout << "Number of bytes left on stack " << manager.GetStackBytesLeft() << std::endl;
	SmartPointer<two> test1(&manager,0);
	std::cout << "Number of bytes left on stack " << manager.GetStackBytesLeft() << std::endl;
	SmartPointer<two> test2(&manager,0);
	std::cout << "Number of bytes left on stack " << manager.GetStackBytesLeft() << std::endl;
	SmartPointer<two> test3(&manager,0);
	std::cout << "Number of bytes left on stack " << manager.GetStackBytesLeft() << std::endl;

	test3.~SmartPointer();
	std::cout << "Number of bytes left on stack " << manager.GetStackBytesLeft() << std::endl;
	SmartPointer<two> test4(&manager, 1, true);
	std::cout << "Number of bytes left db stack " << manager.GetDBStackBytesLeft() << std::endl;
	SmartPointer<two> test5(&manager, 1, true);
	std::cout << "Number of bytes left db stack " << manager.GetDBStackBytesLeft() << std::endl;
	SmartPointer<two> test6(&manager, 1, false);
	std::cout << "Number of bytes left db stack " << manager.GetDBStackBytesLeft() << std::endl;
	SmartPointer<two> test7(&manager, 1, false);

	std::cout << "Number of bytes left db stack " << manager.GetDBStackBytesLeft() << std::endl;
	std::cout << "dealloc tests" << std::endl;

	test7.~SmartPointer();
	std::cout << "Number of bytes left db stack " << manager.GetDBStackBytesLeft() << std::endl;
	test6.~SmartPointer();
	
	std::cout << "Number of bytes left db stack " << manager.GetDBStackBytesLeft() << std::endl;

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

	std::cout << *ptr << std::endl;

	ptr2.~SmartPointer();
	std::cout << "number of blocks left pool: " << manager.GetPoolBlocksLeft() << std::endl;
	poolAlloc = manager.DisplayPoolAlloc();
	for (int i = 0; i < poolAlloc.size(); i++)
	{

		std::cout << poolAlloc[i] << std::endl;
	}

	std::cout << "Pointer 3 is " << *ptr3 << std::endl;
	manager.Defrag();

	poolAlloc = manager.DisplayPoolAlloc();
	for (int i = 0; i < poolAlloc.size(); i++)
	{

		std::cout << poolAlloc[i] << std::endl;
	}
	std::cout << "number of blocks left pool: " << manager.GetPoolBlocksLeft() << std::endl;
	std::cout << "Pointer 3 is " << *ptr3 << std::endl;
	*ptr3 = 56.6;
	std::cout << "Pointer 3 is " << *ptr3 << std::endl;

	free(mem2);
	int i = 0;
	std::cin >> i;
	return 0;
}