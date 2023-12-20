#include "shared.h"

extern long example_bl();

EXILE_API_EXPORT
void exFree(void* address)
{
    example_bl();


    if (!address) return;
    gExileAllocatedMemory -= msize(address);

    free(address);
}