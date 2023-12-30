#include <exile/core/version.h>
#include <exile/core/u16ToString.h>
#include <exile/core/u8ToString.h>
#include <string.h>

/*
	"exp:" += 4;
	"12" += 3;
	"12" += 3;
	"12" += 3;
*/


EXILE_API_EXPORT
u32 exVersionStr(const exVersion* in, u32 bufferSize, char* buffer)
{
	u32 len = in->isExp == EX_TRUE ? 4 : 0;
	len += exU8DigitsCount(in->ver.components.major) + exU8DigitsCount(in->ver.components.minor) + 3;
	
	if (buffer == NULL || bufferSize < len) return len;

	char* pointer = buffer;
	if (in->isExp)
	{
		strcpy(buffer, "exp:");
		pointer += 4;
	}

	u16 digits = exU8DigitsCount(in->ver.components.major);
	exU8ToString(in->ver.components.major, digits, pointer);
	pointer += digits;
	*pointer = '.';
	pointer += 1;
	
	digits = exU8DigitsCount(in->ver.components.minor);
	exU8ToString(in->ver.components.minor, digits, pointer);
	pointer += digits;
	*pointer = '.';
	pointer += 1;

	digits = exU16DigitsCount(in->ver.components.alpha);
	exU16ToString(in->ver.components.alpha, digits, pointer);
	pointer += digits;
	
	*(pointer + 1) = '\0';
	return len;
}
