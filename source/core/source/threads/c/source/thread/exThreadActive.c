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
u8 exThreadActive(exThread* thread)
{
#if defined(EXILE_WIN)
	DWORD exitCode = WaitForSingleObject(thread->internalData, 0);
	return exitCode == WAIT_TIMEOUT;
#elif defined(EXILE_UNIX)
	return thread->internalData != NULL;
#endif
}
