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
u8 exMutexDestroy(exMutex* mutex)
{
	if (!mutex && !mutex->internalData) return EX_SUCCESS;

#if defined(EXILE_UNIX)
	int res = pthread_mutex_destroy(((pthread_mutex_t*)mutex->internalData));
	/*
		TO DO:
		res switch 
                switch (result) {
            case 0:
                break;
            case EBUSY:
                Unable to destroy mutex: mutex is locked or referenced
                break;
            case EINVAL:
                Unable to destroy mutex: the value specified by mutex is invalid
                break;
            default:
                An handled error has occurred while destroy a mutex: errno=%i", result);
                break;
        }

	*/
    exFree(mutex->internalData);
    mutex->internalData = NULL;
#elif defined(EXILE_WIN)
	CloseHandle(mutex->internalData);
	mutex->internalData = NULL;
#endif

	return EX_SUCCESS;
}