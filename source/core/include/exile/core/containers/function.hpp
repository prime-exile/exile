#ifndef _EXILE_CORE_FUNCTION_HPP_
#define _EXILE_CORE_FUNCTION_HPP_

#include <exile/core/memory.hpp>

namespace exile
{
	template <typename T>
	class Function;
	template <typename ReturnValue, typename... Args>
	class Function<ReturnValue(Args...)> {
	public:

		Function()
			:callable(NULL)
		{
		}

		template<typename T>
		Function(T t)
			: callable(exile::memory::Alloc<CallableT<T>>(t))
		{
		}

		template<typename T>
		Function& operator=(T t)
		{
			if (callable != NULL)
			{
				exile::memory::Free(callable);
			}
			callable = exile::memory::Alloc<CallableT<T>>(t);
			return *this;
		}

		ReturnValue operator()(Args... args) const 
		{
			return callable->Invoke(args...);
		}

		virtual ~Function()
		{
			if (callable != NULL)
			{
				exile::memory::Free(callable);
			}
		}

	private:
		class ICallable {
		public:
			virtual ~ICallable() = default;
			virtual ReturnValue Invoke(Args...) = 0;
		};

		template <typename T>
		class CallableT : public ICallable {
		public:
			CallableT(const T& t)
				: c(t) {
			}

			~CallableT() override = default;

			ReturnValue Invoke(Args... args) override {
				return c(args...);
			}

		private:
			T c;
		};

		ICallable* callable;
	};
}

#endif