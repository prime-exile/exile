#ifndef _EXILE_CORE_U32_TO_STRING_H_
#define _EXILE_CORE_U32_TO_STRING_H_

#include <exile/core/API.h>

static __forceinline u16 exU32DigitsCount(u32 n)
{
	if (n == 0) return 1;

	u16 digits = 0;
	while (n != 0)
	{
		n /= 10;
		digits += 1;
	}

	return digits;
}

static __forceinline void* exU32ToString(u32 n, u16 digits, char* buffer)
{
	for (u16 i = 0; i < digits; i++)
	{
		buffer[digits - i - 1] = '0' + n % 10;

		n /= 10;
	}

	buffer[digits] = '\0';

	return buffer;
}

#endif