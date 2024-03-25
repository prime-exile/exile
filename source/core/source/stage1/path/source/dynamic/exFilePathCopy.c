#include "../shared.h"

EXILE_API_EXPORT
u8 exFilePathCopy(exFilePath* dest, const exFilePath* src)
{
	return exArrayCopy(dest, src);
}