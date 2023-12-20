#ifndef _EXILE_CORE_VECTOR_HPP
#define _EXILE_CORE_VECTOR_HPP

#include <vector>
#include <exile/core/containers/allocator.hpp>

namespace exile
{
	template<class T>
	using Vector = std::vector<T, exile::ExileAllocator<T>>;
}

#endif