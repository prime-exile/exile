#ifndef _EXILE_CORE_QUEUE_HPP_
#define _EXILE_CORE_QUEUE_HPP_

#include <exile/core/containers/deque.hpp>

#include <queue>

namespace exile
{
	template<class T>
	using Queue = std::queue<T, exile::Deque<T>>;
}

#endif