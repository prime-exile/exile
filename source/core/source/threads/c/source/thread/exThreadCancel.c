#define EXILE_PRIVATE
#include <exile/core/thread/thread.h>

#if defined (EXILE_UNIX)
#include <pthread.h>
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
		/*
		 * to do:
		 * assert
		 * case - ESRCH: thread not found
		 */
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
