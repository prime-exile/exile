#include "../shared.h"


EXILE_API_EXPORT
u8 exFilePathAppend(exFilePath* path, char c)
{
	u32 bytes = strlen(path->path);
	if (bytes + 1 >= EX_PATH_LEN)
	{
		return EX_FALSE;
	}

	char* p = path->path;
	p[bytes] = c;
	p[bytes + 1] = '\0';

	return EX_TRUE;
}