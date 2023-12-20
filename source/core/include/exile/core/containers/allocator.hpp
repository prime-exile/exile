#ifndef _EXILE_CORE_ALLOCATOR_HPP_
#define _EXILE_CORE_ALLOCATOR_HPP_

#include <exile/core/memory.hpp>
#include <stddef.h>
#include <stdint.h>

namespace exile
{
	template<class T>
	class ExileAllocator
	{

	public:
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef T value_type;

		ExileAllocator() {}
		ExileAllocator(const ExileAllocator&) {}

		pointer allocate(size_type n, const void* = 0) {
			T* t = exile::memory::AllocRaw<T>(n * sizeof(T));
			return t;
		}

		void deallocate(void* p, size_type) {
			if (p) {
				exile::memory::Free(p);
			}
		}

		pointer address(reference x) const { return &x; }
		const_pointer address(const_reference x) const { return &x; }

		ExileAllocator<T>& operator=(const ExileAllocator<T>&) { return *this; }

		void construct(pointer p, const T& val)
		{
			new ((T*)p) T(val);
		}
		void destroy(pointer p) { p->~T(); }

		size_type max_size() const { return size_t(-1); }

		template <class U>
		struct rebind { typedef ExileAllocator<U> other; };

		template <class U>
		ExileAllocator(const ExileAllocator<U>&) {}

		template <class U>
		ExileAllocator& operator=(const ExileAllocator<U>&) { return *this; }

		template <class U>
		bool
			operator==(ExileAllocator<U> const& x) noexcept
		{
			return true;
		}

		template <class U>
		bool
			operator!=(ExileAllocator<U> const& y) noexcept
		{
			return !(*this == y);
		}

	};
}

#endif