#ifndef _EXILE_CORE_MEMORY_HPP_
#define _EXILE_CORE_MEMORY_HPP_

extern "C"
{
	#include <exile/core/memory.h>
	#include <exile/core/assert.h>
}

#include <exile/core/critical.hpp>
#include <typeinfo>

namespace exile
{
	namespace memory
	{
		template<class T, class ... Args>
		inline T* Alloc(const Args& ... args)
		{
			T* ptr = reinterpret_cast<T*>(exMalloc(sizeof(T)));
			EX_s1FatalAssertF(ptr == NULL, {}, "failed to allocated %ll bytes for class %s", sizeof(T), typeid(T).name());
			return new (ptr) T(args...);
		}

		template<class T>
		inline T* Alloc()
		{
			T* ptr = reinterpret_cast<T*>(exMalloc(sizeof(T)));
			EX_s1FatalAssertF(ptr == NULL, {}, "failed to allocated %ll bytes for class %s", sizeof(T), typeid(T).name());
			return new (ptr) T();
		}

		template<class T>
		inline T* AllocRaw(u64 b)
		{
			return reinterpret_cast<T*>(exMalloc(b));
		}

		template<class T>
		inline void Free(T* address)
		{
			EX_s1FatalAssertF(address == NULL, {}, "failed to free class %s address == NULL", typeid(T).name());
			address->~T();
			exFree(address);
		}


		inline void Free(void* address)
		{
			EX_s1FatalAssert(address == NULL, {}, "failed to free class 'void*' address == NULL");
			exFree(address);
		}

	}
}

#endif