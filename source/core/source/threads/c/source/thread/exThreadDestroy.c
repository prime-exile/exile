#define EXILE_PRIVATE
#include <exile/core/thread/thread.h>
#include <exile/core/assert.h>

#if defined(EXILE_WIN)
#include <Windows.h>
#elif defined(EXILE_UNIX)
#include <pthread.h>
#endif

#if defined(EXILE_UNIX)
#include <pthread.h>
#elif defined(EXILE_WIN)
#include <Windows.h>
#endif




EXILE_API_EXPORT
u8 exThreadDestroy(exThread *thread)
{
#if defined(EXILE_UNIX)
	exThreadCancel(thread);
#elif defined(EXILE_WIN)
	if(thread->internalData)
	{
		DWORD exitCode = 0x0;
		GetExitCodeThread(thread->internalData, &exitCode);
		CloseHandle((HANDLE) thread->internalData);
		thread->internalData = NULL;
		thread->threadId = 0;
	}
#endif
}


