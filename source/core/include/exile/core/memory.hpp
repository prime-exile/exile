#ifndef _EXILE_CORE_MEMORY_HPP_
#define _EXILE_CORE_MEMORY_HPP_

extern "C"
{
	#include <exile/core/memory.h>
	#include <exile/core/assert.h>
}

#include <exile/core/critical.hpp>
#include <typeinfo>


#include <memory.h>
#include <malloc.h>
#include <stdlib.h>

#if defined(EXILE_WIN)
#define msize(address)(_msize(address))
#elif defined(EXILE_UNIX)
#define msize(address)(malloc_usable_size(address))
#endif

namespace exile
{
	namespace memory
	{
		template<class T, class ... Args>
		inline T* Alloc(const Args& ... args)
		{
			T* ptr = reinterpret_cast<T*>(exMalloc(sizeof(T)));
			exAssertFatalF(ptr == NULL, {}, "failed to allocated %ll bytes for class %s", sizeof(T), typeid(T).name())
			return new (ptr) T(args...);
		}

		template<class T>
		inline T* Alloc()
		{
			T* ptr = reinterpret_cast<T*>(exMalloc(sizeof(T)));
			exAssertFatalF(ptr == NULL, {}, "failed to allocated %ll bytes for class %s", sizeof(T), typeid(T).name())
			return new (ptr) T();
		}


		template<class T>
		inline T* AllocRaw(u64 b)
		{
			return reinterpret_cast<T*>(exMalloc(b));
		}

		template<class T>
		constexpr inline T* AllocArray(u64 count)
		{
#if defined(EXILE_UNIX)
			count -= 1;
#endif

			T* ptr = reinterpret_cast<T*>(exMalloc(sizeof(T)* count));
			exAssertFatalF(ptr == NULL, {}, "failed to allocated %ll bytes for class array %s", sizeof(T), typeid(T).name());

			for(u64 i = 0; i < count; i += 1)
			{
				new (&ptr[i]) T();
			}
			
			return ptr;
		}

		
		template<class T, class ... Args>
		constexpr inline T* AllocArray(u64 count, const Args& ... args)
		{
			T* ptr = reinterpret_cast<T*>(exMalloc(sizeof(T)* count));
			exAssertFatalF(ptr == NULL, {}, "failed to allocated %ll bytes for class array %s", sizeof(T), typeid(T).name())
			
			for(u64 i = 0; i < count; i += 1)
			{
				new (&ptr[i]) T(args...);
			}
			
			return ptr;
		}

		template<class T>
		constexpr inline void FreeArr(T* arr)
		{
			u64 size = msize(arr);
			u64 count = size/sizeof(T);

			for(u64 i = 0; i < count; i+=1)
			{
				arr[i].~T();
			}

			exFree(arr);
		}


		template<class T>
		inline void Free(T* address)
		{
			exAssertFatalF(address == NULL, {}, "failed to free class %s address == NULL", typeid(T).name());
			address->~T();
			exFree(address);
		}


		inline void Free(void* address)
		{
			exAssertFatal(address == NULL, {}, "failed to free class 'void*' address == NULL");
			exFree(address);
		}

	}
}

#endif