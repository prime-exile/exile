#include<exile/core/memory.h>
#include<exile/core/critical.h>

#include<time.h>
#include <stdio.h>

EXILE_API_IMPORT int t22();

int main()
{
	int i[512];
	

	clock_t start, end;
	double cpu_time_used;

	start = clock();


	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Time used: %f\n", cpu_time_used);
	
	return 0;
}
