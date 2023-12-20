#ifndef _EXILE_CORE_STACK_HPP_
#define _EXILE_CORE_STACK_HPP_

#include <exile/core/containers/deque.hpp>

#include <stack>

namespace exile
{
	template<class T>
	using Stack = std::stack<T, exile::Deque<T>>;
}

#endif