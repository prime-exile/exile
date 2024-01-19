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
u8 exMutexCreate(exMutex* mutex)
{
#if defined(EXILE_UNIX)
	pthread_mutex_t rawMutex;

	pthread_mutexattr_t mutexAttr;
	pthread_mutexattr_init(&mutexAttr);
	pthread_mutexattr_settype(&mutexAttr, PTHREAD_MUTEX_RECURSIVE);

	int res = pthread_mutex_init(&rawMutex, &mutexAttr);
	exAssertR(res != 0, {}, EX_ERROR, "failed to create mutex");

	mutex->internalData = exMalloc(sizeof(pthread_mutex_t));
	
	*(pthread_mutex_t*)mutex->internalData = rawMutex;

#elif defined(EXILE_WIN)
	mutex->internalData = CreateMutexA(NULL, NULL, NULL);
	
	exAssertR(!mutex->internalData, {}, EX_ERROR, "failed to create mutex");

#endif

	return EX_SUCCESS;
}
