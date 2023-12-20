#ifndef _EXILE_CORE_MEMORY_H_
#define _EXILE_CORE_MEMORY_H_

#include <string.h>
#include <exile/core/API.h>

EX_API void* exMalloc(u64 bytes);
EX_API void* exRealloc(void* address, u64 newSize);
EX_API void exFree(void* address);

EX_API u64 exGetAllocatedMemorySize();

//EX_API void* exMemset(void* dest, char val, int len);

#define exMemset(dest, val, len)(memset(dest, val, len))
#define exMemcpy(dest, source, len)(memcpy(dest, source, len))

#endif