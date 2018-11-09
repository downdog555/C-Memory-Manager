#pragma once
#include <exception>
struct AllocationException : public std::exception
{
	const char* what() const throw() 
	{
		return "Error Allocating, Most likely not enough memeory";
	}
};
struct DeallocationException : public std::exception
{
	const char* what() const throw()
	{
		return "Error Deallocating, Most likely trying to deallocate in the incorrect order on a stack, or an incorrectr pointer has been passed";
	}
};