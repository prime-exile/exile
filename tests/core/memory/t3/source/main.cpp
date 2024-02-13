#include<iostream>

extern "C"
{
	#include<exile/core/memory.h>
	#include<exile/core/array.h>
}

#include<time.h>
#include <vector>
#include <exile/core/memory.hpp>

class Test
{

	int* s;

public:

	Test()
	{
		s = exile::memory::Alloc<int>();
	}

	~Test()
	{
		exile::memory::Free(s);
	}

};

int main()
{
	std::cout << exGetAllocatedMemorySize() << std::endl;;

	Test* t = exile::memory::AllocArray<Test>(1000);
	
	std::cout << exGetAllocatedMemorySize() << std::endl;;
	exile::memory::FreeArr<Test>(t) ;

	std::cout << exGetAllocatedMemorySize() << std::endl;;

	return 0;
}
