#define EXILE_PRIVATE
#include <exile/core/thread/thread.h>
#include <exile/core/assert.h>

#if defined(EXILE_WIN)
#include <Windows.h>
#elif defined(EXILE_UNIX)
#include <pthread.h>
#endif


EXILE_API_EXPORT 
u8 exThreadCreate(exThread* thread, PFNExThreadStart threadStart, void* params, u8 detach)
{
#if defined(EXILE_WIN)

	thread->internalData = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)threadStart, params, NULL, (DWORD*)&thread->threadId);

    exAssertR(thread->internalData == NULL, {}, EX_ERROR, "CreateThread: failed to create thread");

	if (detach)
	{
		CloseHandle(thread->internalData);
	}

#elif defined(EXILE_UNIX)


    int status = pthread_create((pthread_t*)&thread->threadId, NULL, threadStart, params);
    if (status != 0)
    {
        switch (status)
        {
        case EAGAIN:
            exAssertR(1, {}, EX_ERROR, "pthread_create: Failed to create thread: insufficient resources to create another thread.");
        case EINVAL:
            exAssertR(1, {}, EX_ERROR, "pthread_create: Failed to create thread: invalid settings were passed in attributes..");
        default: 
            exAssertFR(1, {}, EX_ERROR, "pthread_create: Failed to create thread: an unhandled error has occurred. errno=%i", status);
        }
    }

    if (detach)
    {
        status = pthread_detach(thread->threadId);
        if (status != 0)
        {
            switch (status)
            {
            case ESRCH:
                exAssertFR(1, {}, EX_ERROR, "pthread_detach: Failed to detach newly-created thread: no thread with the id %#x could be found.", thread->threadId);
            case EINVAL:
                exAssertR(1, {}, EX_ERROR, "pthread_detach: Failed to detach newly-created thread: invalid settings were passed in attributes..");
            default:
                exAssertFR(1, {}, EX_ERROR, "pthread_detach: Failed to detach newly-created thread: an unhandled error has occurred. errno=%i", status);
            }
        }
        EX_s1AssertR(status != 0, {
        }, EX_ERROR, "pthread_detach:failed to detach");
    }
    else
    {
        thread->internalData = thread->threadId;
    }

#endif

	return EX_SUCCESS;
}
