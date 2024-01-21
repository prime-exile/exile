#ifndef _EXILE_CORE_U64_TO_STRING_HPP_
#define _EXILE_CORE_U64_TO_STRING_HPP_

extern "C"
{
#include <exile/core/string/u64ToString.h>
}


#include <exile/core/containers/string.hpp>

namespace exile
{
	const exile::String __forceinline static u64ToString(u64 n)
	{
		 u64 register digits = exU64DigitsCount(n);
		 char* buffer = reinterpret_cast<char*>(exMalloc(digits + 2));

		 ::exU64ToString(n, digits + 1, buffer);
		 
		 exile::String res;
		 res.assign(buffer);
		 exFree(buffer);

		 return res;
	}
}

#endif