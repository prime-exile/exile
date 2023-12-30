#ifndef _EXILE_CORE_U8_TO_STRING_H_
#define _EXILE_CORE_U8_TO_STRING_H_

#include <exile/core/API.h>

static __forceinline u8 exU8DigitsCount(u8 n)
{
	if (n == 0) return 1;

	u8 digits = 0;
	while (n != 0)
	{
		n /= 10;
		digits += 1;
	}

	return digits;
}

static __forceinline void* exU8ToString(u8 n, u8 digits, char* buffer)
{
	for (u8 i = 0; i < digits; i++)
	{
		buffer[digits - i - 1] = '0' + n % 10;

		n /= 10;
	}

	buffer[digits] = '\0';

	return buffer;
}

#endif