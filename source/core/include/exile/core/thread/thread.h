#ifndef _EXILE_CORE_THREAD_H_
#define _EXILE_CORE_THREAD_H_

#include <exile/core/API.h>

typedef	struct exThread
{
	void* internalData;
	u64 threadId;
} exThread;

typedef u32(*PFNExThreadStart)(void* data);

EX_API u8 exThreadCreate(exThread* thread, PFNExThreadStart threadStart, void* params, u8 detach);

EX_API u8 exThreadDestroy(exThread* thread);

EX_API void exThreadCancel(exThread* thread);

EX_API u64 exThreadGetCurrentId();

EX_API void exThreadSleep(u64 ms);
#endif
