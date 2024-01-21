#ifndef _EXILE_CORE_I8_TO_STRING_H_
#define _EXILE_CORE_I8_TO_STRING_H_

#include <exile/core/API.h>

static __forceinline i8 exI8DigitsCount(i8 n)
{
	if (n == 0) return 1;

	u8 digits = 0;
	if (n < 0)
	{
		digits++;  // Account for negative sign
		n = -n;
	}
	
	while (n != 0)
	{
		n /= 10;
		digits += 1;
	}

	return digits;
}

static __forceinline void* exI8ToString(i8 n, u8 digits, char* buffer)
{
	if (n < 0)
	{
		buffer[0] = '-';
		n = -n;
	}

	for (u8 i = 0; i < digits - 1; i++)
	{
		buffer[digits - i - 1] = '0' + n % 10;

		n /= 10;
	}

	buffer[digits + 1] = '\0';

	return buffer;
}

#endif