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

	thread->internalData = CreateThread(NULL, NULL, threadStart, params, NULL, (DWORD*)&thread->threadId);

	EX_s1AssertR(thread->internalData == NULL, {}, EX_ERROR, "CreateThread: failed to create thread");

	if (detach)
	{
		CloseHandle(thread->internalData);
	}

#elif defined(EXILE_UNIX)

	/*
	* to do:
	        switch (result) {
            case EAGAIN:
                ERROR("Failed to create thread: insufficient resources to create another thread.");
                return false;
            case EINVAL:
                ERROR("Failed to create thread: invalid settings were passed in attributes..");
                return false;
            default:
                ERROR("Failed to create thread: an unhandled error has occurred. errno=%i", result);
                return false;
        }
	*/

    int status = pthread_create((pthread_t*)&thread->threadId, NULL, threadStart, params);
	EX_s1AssertR(status != 0, {
	}, EX_ERROR, "pthread_create:failed to create thread");

	/*
	        if (result != 0) {
            switch (result) {
                case EINVAL:
                    KERROR("Failed to detach newly-created thread: thread is not a joinable thread.");
                    return false;
                case ESRCH:
                    KERROR("Failed to detach newly-created thread: no thread with the id %#x could be found.", out_thread->thread_id);
                    return false;
                default:
                    KERROR("Failed to detach newly-created thread: an unknown error has occurred. errno=%i", result);
                    return false;
            }
        }
	*/

    if (detach)
    {
        status = pthread_detach(thread->threadId);
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
