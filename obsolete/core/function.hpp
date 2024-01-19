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
			:callable(NULL),
			counter(NULL)
		{
		}

		template<typename T>
		Function(T t)
			: callable(exile::memory::Alloc<CallableT<T>>(t))
		{
		}

		Function(Function<ReturnValue(Args...)>& other)
		{
			other.counter = exile::memory::Alloc();
			*other.counter = 1;
			this->counter = other.counter;
		}

		static void MoveFunction(Function<ReturnValue(Args...)>& in, Function<ReturnValue(Args...)>& out)
		{
			in.counter = exile::memory::AllocRaw<int>(sizeof(int));
			*in.counter = 1;
			out.counter = in.counter;
			out.callable = in.callable;
			//in.callable = NULL;
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
				if (counter != NULL)
				{
					if ((*counter) < 1)
					{
						exile::memory::Free(callable);
						exile::memory::Free(counter);
					}
					else
					{
						*counter -= 1;
					}
				}
				else exile::memory::Free(callable);
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
			friend Function;
		public:
			CallableT(const T& t)
				: c(t) {
			}

			CallableT(const CallableT<T>& other)
				: c(other.c) {
			}

			~CallableT() override = default;

			ReturnValue Invoke(Args... args) override {
				return c(args...);
			}

		private:
			T c;
		};

		int* counter;

		ICallable* callable;
	};
}

#endif