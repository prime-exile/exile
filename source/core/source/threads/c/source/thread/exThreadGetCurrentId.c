#define EXILE_PRIVATE
#include <exile/core/thread/thread.h>
#include <exile/core/assert.h>

#if defined(EXILE_WIN)
#include <Windows.h>
#elif defined(EXILE_UNIX)
#include <pthread.h>
#endif

EXILE_API_EXPORT
u64 exThreadGetCurrentId()
{
#if defined(EXILE_WIN)
	return (u64)GetCurrentThreadId();
#elif defined(EXILE_UNIX)
	return (u64)pthread_self();
#endif
}
