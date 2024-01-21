#ifndef _EXILE_CORE_THREAD_HPP_
#define _EXILE_CORE_THREAD_HPP_

extern "C"
{
#include <exile/core/thread/thread.h>
}

#include <exile/core/containers/function.hpp>
#include <exile/core/api.h>

namespace exile
{
	class EX_API Thread
	{
	private:

		struct ThreadCallData
		{
			void* functionContainerPointer;
			void* argumentsPointer;
		};

	private:

		exThread rawThread;


	public:
		Thread();
		Thread(const Thread&) = delete;

		template<class Arguments>
		inline u8 Run(exile::Function<u32(Arguments*)>& func, Arguments* args);

		//recommended way!
		inline u8 Run(exile::Function<u32()> func);

		inline u64 GetThreadId();

		static u64 GetCurrentThreadId();

		void Destroy();

		u8 IsActive();

		u8 Join();

		void Cancel();
		
		Thread& operator=(const Thread&) = delete;
		Thread& operator==(const Thread&) = delete;

	};

	template<class Arguments>
	inline u8 Thread::Run(exile::Function<u32(Arguments*)>& func, Arguments* args)
	{
		ThreadCallData* data = exile::memory::Alloc<ThreadCallData>();
		data->argumentsPointer = args;

		// prepare function container
		exile::Function<u32(Arguments*)>* heapContainer = exile::memory::Alloc<exile::Function<u32(Arguments*)>>();
		//*heapContainer = std::move(func);
		(*heapContainer) = func;
		data->functionContainerPointer = heapContainer;

		exAssertR(exThreadCreate(&rawThread, [](void* ldata)->u32 {
			ThreadCallData* rdata = reinterpret_cast<ThreadCallData*>(ldata);

			exile::Function<u32(Arguments*)>* sfptr = reinterpret_cast<exile::Function<u32(Arguments*)>*>(rdata->functionContainerPointer);

			u32 val = (*sfptr)(reinterpret_cast<Arguments*>(rdata->argumentsPointer));

			sfptr->~function();

			exile::memory::Free(rdata->functionContainerPointer);
			exile::memory::Free(rdata);
			return val;
			}, data, EX_FALSE) == EX_ERROR, {}, EX_ERROR, "failed to create thread");

		return EX_SUCCESS;
	}

	inline u8 Thread::Run(exile::Function<u32()> func)
	{
		exAssertR(exThreadCreate(&rawThread, [](void* data)->u32 {
			exile::Function<u32()>* ptr = reinterpret_cast<exile::Function<u32()>*>(data);
			return (*ptr)();
		}, &func, EX_FALSE) == EX_ERROR, {}, EX_ERROR, "failed to run thread!");

		return EX_SUCCESS;
	}


}

#endif