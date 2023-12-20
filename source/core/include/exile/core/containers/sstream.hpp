#ifndef _EXILE_CORE_SSTREAM_HPP_
#define _EXILE_CORE_SSTREAM_HPP_

#include <sstream>
#include <exile/core/containers/allocator.hpp>

namespace exile
{
	using Stringstream = std::basic_stringstream<char, std::char_traits<char>, exile::ExileAllocator<char>>;
	template<typename CharType>
	using CStringstream = std::basic_stringstream<CharType, std::char_traits<CharType>, exile::ExileAllocator<CharType>>;
}

#endif