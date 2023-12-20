#ifndef _EXILE_CORE_U64_TO_STRING_H_
#define _EXILE_CORE_U64_TO_STRING_H_

#include <exile/core/API.h>

static __forceinline u64 exU64DigitsCount(u64 n)
{
	if (n == 0) return 0;

	u64 digits = 0;
	while (n != 0) 
	{
		n /= 10;
		digits += 1;
	}

	return digits;
}

static __forceinline void* exU64ToString(u64 n, u64 digits, char* buffer)
{
	for (u64 i = 0; i < digits; i++)
	{
		buffer[digits - i - 1] = '0' + n % 10;

		n /= 10;
	}

	buffer[digits] = '\0';

	return buffer;
}

#endif