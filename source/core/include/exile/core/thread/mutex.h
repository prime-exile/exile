#ifndef _EXILE_CORE_MUTEX_H_
#define _EXILE_CORE_MUTEX_H_

#include <exile/core/API.h>


typedef struct
{
	void* internalData;
} exMutex;

EX_API u8 exMutexCreate(exMutex* mutex);

EX_API u8 exMutexDestroy(exMutex* mutex);

EX_API u8 exMutexLock(exMutex* mutex);

EX_API u8 exMutexUnlock(exMutex* mutex);

#endif