#include "shared.h"

EXILE_API_EXPORT
void* exRealloc(void* address, u64 newSize)
{
    gExileAllocatedMemory -= msize(address);

    void* newAddress = realloc(address, newSize);
    if (!newAddress) return NULL;

    gExileAllocatedMemory += msize(newAddress);

    return newAddress;
}