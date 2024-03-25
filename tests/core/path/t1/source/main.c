#include<exile/core/memory.h>
#include<exile/core/path.h>

#include<time.h>
#include <stdio.h>

int main()
{
	exFilePath p;
	exFilePathInit2(&p, "critical.conf");

	exFilePathAppend(&p, 'd');
	
	clock_t start, end;
	double cpu_time_used;

	start = clock();

	char bytes[256];
	const char* ext = exFilePathGetFileExtension(&p);

	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("exFilePathGetFileExtension Time used: %f\n", cpu_time_used);
	puts(ext);

	start = clock();

	exFilePathGetFileName(&p, bytes, 256);

	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("exFilePathGetFileName Time used: %f\n", cpu_time_used);


	puts(bytes);

	start = clock();

	auto at = exFilePathGetType(&p);

	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("exFilePathGetType Time used: %f\n", cpu_time_used);

	switch (at)
	{
	case exFilePathType_File:
		printf("file!");
		break;
	case exFilePathType_Dir:
		printf("dir!");
		break;
	case exFilePathType_Invalid:
		printf("invalid!");
		break;
	}

	exFilePathFree(&p);

	return 0;
}
