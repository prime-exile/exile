#include <stdio.h>

#include "shared.h"


EXILE_API_EXPORT
void* exMalloc(u64 bytes)
{
    void* mem = malloc(bytes);
    if (!mem) return NULL;

    gExileAllocatedMemory += msize(mem);
    return mem;
}