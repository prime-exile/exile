#include "../shared.h"

EXILE_API_EXPORT
u8 exFilePathCopy(exFilePath* dest, const exFilePath* src)
{
	exMemcpy(dest->path, src->path, EX_PATH_LEN);
	return EX_SUCCESS;
}