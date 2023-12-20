#include "../shared.h"

EXILE_API_EXPORT
void exFilePathGetFileName(exFilePath* path, char* buffer, u16 len)
{
	u64 l = strlen(path->path.memory);
	const char* pptr = path->path.memory;
	const char* end = pptr + l;
	exMemset(buffer, 0, len);

	const char* ptr = exStringGetLastCharPointer(pptr, '/');
	if (ptr == NULL)
	{
		const char* ptr = pptr;
		u16 count = ptr - end;
		
		for (u16 i = 0; ptr != end && i < len; i += 1, ptr += 1, buffer += 1)
		{
			*buffer = *ptr;
		}

		return;
	}

	ptr += 1;
	u64 count = ptr - end;

	for (u16 i = 0; ptr != end && i < len; i += 1, ptr += 1, buffer += 1)
	{
		*buffer = *ptr;
	}
}

