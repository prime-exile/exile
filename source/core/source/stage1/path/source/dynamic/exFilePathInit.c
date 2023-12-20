#include "../shared.h"

EXILE_API_EXPORT
u8 exFilePathInit(exFilePath* path)
{
	if (exArrayInit(&path->path, 4) != EX_SUCCESS) return EX_ERROR;
	exMemset(&path->path.memory, 0, 4);
}


EXILE_API_EXPORT
u8 exFilePathInit2(exFilePath* path, const char* newPath)
{
	u64 len = strlen(newPath);
	if (exArrayInit(&path->path, len + 1) != EX_SUCCESS) return EX_ERROR;
	path->path.occupied += len;
	exMemcpy(path->path.memory, newPath, len);
	((char*)path->path.memory)[len] = '\0';
	
	return EX_SUCCESS;
}
