#include "../shared.h"

EXILE_API_EXPORT
void exFilePathFree(exFilePath* path)
{
	exMemset(path->path, 0, EX_PATH_LEN);
}