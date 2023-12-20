#include "shared.h"

u64 gExileAllocatedMemory = 0;

EXILE_API_EXPORT
u64 exGetAllocatedMemorySize()
{
	return gExileAllocatedMemory;
}