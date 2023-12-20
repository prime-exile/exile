#ifndef _EXILE_CORE_SHARED_POINTER_HPP_
#define _EXILE_CORE_SHARED_POINTER_HPP_

#include <exile/core/memory.hpp>

namespace exile
{
	template<class T>
	class SharedPointer
	{
		u32 counter;
		T* ptr;

		
	public:
		SharedPointer(T* ptr)
			:ptr(ptr)
		{

		}

		inline T* operator->()
		{
			return ptr;
		}
	};


}

#endif