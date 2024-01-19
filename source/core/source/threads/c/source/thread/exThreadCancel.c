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
void exThreadCancel(exThread* thread)
{
#if defined (EXILE_UNIX)
	if(thread->internalData)
	{
		int res = pthread_cancel(*(pthread_t*)thread->internalData);
		if (res != 0)
		{
			switch (res) {
			case ESRCH:
				exAssertF(1, {}, "Failed to cancel thread: no thread with the id %#x could be found.", thread->threadId);
				break;
			default:
				exAssertF(1, {}, "Failed to cancel thread: an unknown error has occurred. errno=%i", res);
				break;
			}
		}
		
		thread->internalData = NULL;
		thread->threadId = 0;
	}
#elif defined(EXILE_WIN)
	if(thread->internalData)
	{
		TerminateThread(thread->internalData, 0);
		thread->internalData = 0;
	}
#endif

}
