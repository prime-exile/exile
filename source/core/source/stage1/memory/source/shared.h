
#define EXILE_PRIVATE
#include <exile/core/memory.h>

#include <memory.h>
#include <malloc.h>
#include <stdlib.h>

extern u64 gExileAllocatedMemory;

#if defined(EXILE_WIN)
#define msize(address)(_msize(address))
#elif defined(EXILE_UNIX)
#define msize(address)(malloc_usable_size(address))
#endif