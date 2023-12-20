#include "../shared.h"

EXILE_API_EXPORT
void exFilePathFree(exFilePath* path)
{
	exArrayFree(&path->path);
}