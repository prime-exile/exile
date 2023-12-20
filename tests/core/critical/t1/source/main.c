#include<exile/core/memory.h>
#include<exile/core/critical.h>

#include<time.h>
#include <stdio.h>

int main()
{
	int i[512];

	clock_t start, end;
	double cpu_time_used;
	exSetupCriticalDefaultConfiguration();
	printf("%p\n", &gExileCriticalInstance);

	start = clock();
	u8 res = exLoadCriticalConfiguration("critical.conf");
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Time used: %f\n", cpu_time_used);
	if (res != EX_SUCCESS) return -1;

	printf("%p\n", &gExileCriticalInstance);
	printf("%p\n", gExileCriticalInstance.panic);
	
	exPanic("sd");

	return 0;
}
