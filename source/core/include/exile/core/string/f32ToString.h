#ifndef _EXILE_CORE_F32_TO_STRING_H_
#define _EXILE_CORE_F32_TO_STRING_H_

#include <exile/core/API.h>

static __forceinline u16 exF32DigitsCount(f32 n, u8 afterDecimalPoint = 6)
{
	if (n == 0.0f) return 1;

	u16 digits = 0;
	int integerPart = (int)n;
	while (integerPart != 0)
	{
		integerPart /= 10;
		digits += 1;
	}

	digits += 1; // point;
	digits += afterDecimalPoint;

	return digits;
}

static __forceinline void* exF32ToString(f32 n, u16 digits, char* buffer, u8 afterDecimalPoint = 6)
{
	if (n == 0.0f)
	{
		buffer[0] = '0';
		buffer[0] = '\0';
		return buffer;
	}

	const u8 adp = afterDecimalPoint + 1;

	int integerPart = (int)n;
	u16 i = 0;
	for (; i < digits - adp; i++)
	{
		buffer[(digits - adp )- i - 1] = '0' + integerPart % 10;

		integerPart /= 10;
	}

	buffer[(digits - afterDecimalPoint) - 1] = '.';

	integerPart = (int)n;
	f32 fractionalPart = n - ((f32)integerPart);

	for (i = 1; i < afterDecimalPoint; i++)
	{
		fractionalPart *= 10;
		buffer[digits - adp + i] = '0' + ((int)fractionalPart) % 10;
	}

	buffer[digits] = '\0';

	return buffer;
}

#endif