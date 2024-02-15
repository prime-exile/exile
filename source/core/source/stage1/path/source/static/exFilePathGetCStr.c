#include "../shared.h"

EXILE_API_EXPORT
const char* exFilePathGetCStr(const exFilePath* path)
{
	return path->path;
}