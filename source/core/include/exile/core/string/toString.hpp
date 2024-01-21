#ifndef _EXILE_CORE_U64_TO_STRING_HPP_
#define _EXILE_CORE_U64_TO_STRING_HPP_

extern "C"
{
#include <exile/core/string/u64ToString.h>
}


#include <exile/core/containers/string.hpp>

namespace exile
{

	const exile::String __forceinline static ToString(u8 n)
	{
		u8 register digits = exU8DigitsCount(n);
		char* buffer = reinterpret_cast<char*>(exMalloc(digits + 2));

		::exU8ToString(n, digits + 1, buffer);

		exile::String res;
		res.assign(buffer);
		exFree(buffer);

		return res;
	}

	const exile::String __forceinline static ToString(u16 n)
	{
		u16 register digits = exU16DigitsCount(n);
		char* buffer = reinterpret_cast<char*>(exMalloc(digits + 2));

		::exU16ToString(n, digits + 1, buffer);

		exile::String res;
		res.assign(buffer);
		exFree(buffer);

		return res;
	}

	const exile::String __forceinline static ToString(u32 n)
	{
		u32 register digits = exU32DigitsCount(n);
		char* buffer = reinterpret_cast<char*>(exMalloc(digits + 2));

		::exU32ToString(n, digits + 1, buffer);

		exile::String res;
		res.assign(buffer);
		exFree(buffer);

		return res;
	}

	const exile::String __forceinline static ToString(u64 n)
	{
		u64 register digits = exU64DigitsCount(n);
		char* buffer = reinterpret_cast<char*>(exMalloc(digits + 2));

		::exU64ToString(n, digits + 1, buffer);

		exile::String res;
		res.assign(buffer);
		exFree(buffer);

		return res;
	}

	const exile::String __forceinline static ToString(i8 n)
	{
		i8 register digits = exI8DigitsCount(n);
		char* buffer = reinterpret_cast<char*>(exMalloc(digits + 2));

		::exI8ToString(n, digits + 1, buffer);

		exile::String res;
		res.assign(buffer);
		exFree(buffer);

		return res;
	}

	const exile::String __forceinline static ToString(i16 n)
	{
		i16 register digits = exI16DigitsCount(n);
		char* buffer = reinterpret_cast<char*>(exMalloc(digits + 2));

		::exI16ToString(n, digits + 1, buffer);

		exile::String res;
		res.assign(buffer);
		exFree(buffer);

		return res;
	}

	const exile::String __forceinline static ToString(i32 n)
	{
		i32 register digits = exI32DigitsCount(n);
		char* buffer = reinterpret_cast<char*>(exMalloc(digits + 2));

		::exI32ToString(n, digits + 1, buffer);

		exile::String res;
		res.assign(buffer);
		exFree(buffer);

		return res;
	}

	const exile::String __forceinline static ToString(i64 n)
	{
		i64 register digits = exI64DigitsCount(n);
		char* buffer = reinterpret_cast<char*>(exMalloc(digits + 2));

		::exI64ToString(n, digits + 1, buffer);

		exile::String res;
		res.assign(buffer);
		exFree(buffer);

		return res;
	}

	const exile::String __forceinline static ToString(f32 n)
	{
		f32 register digits = exF32DigitsCount(n);
		char* buffer = reinterpret_cast<char*>(exMalloc(digits + 2));

		::exF32ToString(n, digits + 1, buffer);

		exile::String res;
		res.assign(buffer);
		exFree(buffer);

		return res;
	}

	const exile::String __forceinline static ToString(f64 n)
	{
		f64 register digits = exF64DigitsCount(n);
		char* buffer = reinterpret_cast<char*>(exMalloc(digits + 2));

		::exF64ToString(n, digits + 1, buffer);

		exile::String res;
		res.assign(buffer);
		exFree(buffer);

		return res;
	}
}

#endif