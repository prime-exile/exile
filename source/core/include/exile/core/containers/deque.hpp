#ifndef _EXILE_CORE_DEQUE_HPP_
#define _EXILE_CORE_DEQUE_HPP_

#include <exile/core/containers/allocator.hpp>

#include <deque>

namespace exile
{
	template<class T>
	using Deque = std::deque<T, exile::ExileAllocator<T>>;

}


#endif