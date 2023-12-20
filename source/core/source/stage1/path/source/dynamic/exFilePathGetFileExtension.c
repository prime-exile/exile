#include "../shared.h"

EXILE_API_EXPORT
const char* exFilePathGetFileExtension(exFilePath* path)
{
	return exStringGetLastCharPointer(path->path.memory, '.') + 1;
}

