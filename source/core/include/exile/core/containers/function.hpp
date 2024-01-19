#ifndef _EXILE_CORE_FUNCTION_HPP_
#define _EXILE_CORE_FUNCTION_HPP_

#include <exile/core/memory.hpp>
#include <functional>

namespace exile
{
	template<class T>
	using Function = std::function<T>;
}

#endif