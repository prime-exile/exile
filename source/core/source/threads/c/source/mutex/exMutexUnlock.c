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
u8 exMutexUnlock(exMutex* mutex)
{
#if defined(EXILE_UNIX)
	int result = pthread_mutex_unlock((pthread_mutex_t*)mutex->internal_data);
	EX_s1AssertR(result != 0, {}, EX_ERROR, "failed to unlock mutex");

	/*
	* TO DO
		            case EOWNERDEAD:
                KERROR("Unable to unlock mutex: owning thread terminated while mutex still active.");
                return false;
            case EPERM:
                KERROR("Unable to unlock mutex: mutex not owned by current thread.");
                return false;
            default:
                KERROR("An handled error has occurred while unlocking a mutex lock: errno=%i", result);
                return false;
	*/
#elif defined(EXILE_WIN)
	int result = ReleaseMutex(mutex);

	EX_s1AssertR(result == 0, {}, EX_ERROR, "failed to unlock mutex")

#endif
	return EX_SUCCESS;
}