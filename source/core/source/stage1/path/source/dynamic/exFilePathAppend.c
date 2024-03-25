#include "../shared.h"

EXILE_API_EXPORT
u8 exFilePathAppend(exFilePath* path, char c)
{
	exArray* arr = &path->path;
	if (arr->allocated <= arr->occupied+2)
	{
		if (exArrayResize(arr, arr->occupied + 2) != EX_SUCCESS) return EX_ERROR;
	}


	char* mem = path->path.memory;

	mem[arr->occupied] = c;
	mem[arr->occupied + 1] = '\0';

	return EX_TRUE;
}