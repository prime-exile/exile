#define EXILE_PRIVATE
#include <exile/core/thread/thread.h>
#include <exile/core/assert.h>

#if defined (EXILE_UNIX)
#include <pthread.h>
#include <errno.h>
#elif defined(EXILE_WIN)
#include <Windows.h>
#endif

EXILE_API_EXPORT
u8 exThreadJoin(exThread* thread)
{
#if defined(EXILE_WIN)
	return WaitForSingleObject(thread->internalData, INFINITE) != WAIT_FAILED;
#elif defined(EXILE_UNIX)
	int res = pthread_join(*(pthread_t*)thread->internalData, NULL);
	exAssertFR(res != 0, {}, EX_ERROR, "failed to join thread! errno=%i", res);
#endif
}
