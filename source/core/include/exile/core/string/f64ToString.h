#ifndef _EXILE_CORE_F32_TO_STRING_H_
#define _EXILE_CORE_F32_TO_STRING_H_

#include <exile/core/API.h>

static __forceinline u32 exF64DigitsCount(f64 n, u16 afterDecimalPoint = 15)
{
	if (n == 0.0f) return 1;

	u32 digits = 0;
	long long integerPart = (int)n;
	while (integerPart != 0)
	{
		integerPart /= 10;
		digits += 1;
	}

	digits += 1; // point;
	digits += afterDecimalPoint;

	return digits;
}

static __forceinline void* exF64ToString(f64 n, u32 digits, char* buffer, u16 afterDecimalPoint = 6)
{
	if (n == 0.0f)
	{
		buffer[0] = '0';
		buffer[0] = '\0';
		return buffer;
	}

	const u16 adp = afterDecimalPoint + 1;

	long long integerPart = (int)n;
	u32 i = 0;
	for (; i < digits - adp; i++)
	{
		buffer[(digits - adp )- i - 1] = '0' + integerPart % 10;

		integerPart /= 10;
	}

	buffer[(digits - afterDecimalPoint) - 1] = '.';

	integerPart = (int)n;
	f64 fractionalPart = n - (f64)integerPart;

	for (i = 1; i < afterDecimalPoint; i++)
	{
		fractionalPart *= 10;
		buffer[digits - adp + i] = '0' + ((int)fractionalPart) % 10;
	}

	buffer[digits] = '\0';

	return buffer;
}

#endif