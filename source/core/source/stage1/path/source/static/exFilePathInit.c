#include "../shared.h"

EXILE_API_EXPORT
u8 exFilePathInit(exFilePath* path)
{
	exMemset(path->path, 0, EX_PATH_LEN);
	return EX_SUCCESS;
}

EXILE_API_EXPORT
u8 exFilePathInit2(exFilePath* path, const char* newPath)
{
	strcpy(path->path, newPath);
	return EX_SUCCESS;
}
