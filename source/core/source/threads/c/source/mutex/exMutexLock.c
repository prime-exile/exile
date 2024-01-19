#define EXILE_PRIVATE
#include <exile/core/thread/thread.h>
#include <exile/core/thread/mutex.h>
#include <exile/core/assert.h>

#if defined(EXILE_WIN)
#include <Windows.h>
#elif defined(EXILE_UNIX)
#include <pthread.h>
#endif

EXILE_API_EXPORT 
u8 exMutexLock(exMutex* mutex)
{
#if defined(EXILE_UNIX)
	int result = pthread_mutex_lock((pthread_mutex_t*)mutex->internalData);
	/*
		TO DO SWITCH WITH ERROR!
	*/
	exAssertR(result != 0, {}, EX_ERROR, "failed to lock mutex");
#elif defined(EXILE_WIN)
	DWORD result = WaitForSingleObject(mutex->internalData, INFINITE);

	/*
		TO DO SWITCH WITH ERROR!
	*/

	exAssertR(result == WAIT_ABANDONED, {}, EX_ERROR, "failed to lock mutex");
#endif

	return EX_SUCCESS;
}
