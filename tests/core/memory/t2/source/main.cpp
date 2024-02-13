#include<iostream>

extern "C"
{
	#include<exile/core/memory.h>
	#include<exile/core/array.h>
}

#include <time.h>
#include <vector>

int main()
{
	 exArray arr;

	 clock_t start, end;
	 double cpu_time_used;

	 exArrayInit(&arr, 1);


	 start = clock();
	
	 for (int i = 0; i < 1000000; i++)
	 {
	 	exArrayPush(&arr, &i, sizeof(int));
	 }
	
	 end = clock();
	 cpu_time_used = ((double)(end - start)) / (CLOCKS_PER_SEC * 1000);
	 exArrayFree(&arr);

	 std::cout << "allocated memory: " << exGetAllocatedMemorySize() << " bytes in time " << cpu_time_used  << " ms" << std::endl;

	 std::vector<int> vec;

	 start = clock();

	 for (int i = 0; i < 1000000; i++)
	 {
	 	vec.push_back(i);
	 }

	 end = clock();
	 cpu_time_used = ((double)(end - start)) / (CLOCKS_PER_SEC * 1000);


	 std::cout << "vector in time " << cpu_time_used << " ms" << std::endl;

	return 0;
}
