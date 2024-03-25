#ifndef _EXILE_CORE_ARRAY_H_
#define _EXILE_CORE_ARRAY_H_

#include <exile/core/API.h>
#include <exile/core/memory.h>

#define exArrayGetElement(arr, type, index)(((type*)arr.memory)[index])

typedef struct
{
	u64 allocated;
	u64 occupied;
	u64 count;
	void* memory;
} exArray;


static __forceinline u8 exArrayInit(exArray* arr, u64 preAllocated)
{
	arr->allocated = preAllocated;
	arr->occupied = 0;
	arr->memory = exMalloc(preAllocated);

	if (arr->memory == NULL) return EX_ERROR;

	arr->count = 0;

	return EX_SUCCESS;
}


static __forceinline u8 exArrayPush(exArray* arr, void* value, u32 len)
{
	u64 free = arr->allocated - arr->occupied;
	if (free < len)
	{
		u64 newSize = arr->allocated + len;
		arr->memory = exRealloc(arr->memory, newSize);
		if (arr->memory == NULL)
		{
			return EX_ERROR;
		}
		char* AddressOffset = (char*)arr->memory;
		AddressOffset += arr->occupied;
		exMemcpy(AddressOffset, value, len);
		arr->count += 1;
		arr->allocated = newSize;
		arr->occupied += len;
	}
	else
	{
		char* AddressOffset = (char*)arr->memory;
		AddressOffset += arr->occupied;
		exMemcpy(AddressOffset, value, len);
		arr->count += 1;
		arr->occupied += len;
	}

	return EX_SUCCESS;
}


static __forceinline u8 exArrayPreAllocate(exArray* arr, u64 bytes)
{
	u64 newSize = arr->allocated + bytes;

	arr->memory = exRealloc(arr->memory, newSize);
	if (arr->memory == NULL)
	{
		return EX_ERROR;
	}

	arr->allocated = newSize;

	return EX_SUCCESS;
}


static __forceinline u8 exArrayResize(exArray* arr, u64 newSize)
{
	arr->memory = exRealloc(arr->memory, newSize);
	if (arr->memory == NULL)
	{
		return EX_ERROR;
	}

	arr->allocated = newSize;

	return EX_SUCCESS;
}

static __forceinline u8 exArrayCopy(exArray* dest, const exArray* source)
{
	if (dest->allocated == source->allocated)
	{
		dest->count = source->count;
		dest->occupied = source->occupied;
		exMemcpy(dest->memory, source->memory, source->occupied);
	}
	else
	{
		if (exArrayResize(dest, source->allocated) == EX_ERROR) return EX_ERROR;

		dest->count = source->count;
		dest->occupied = source->occupied;
		exMemcpy(dest->memory, source->memory, source->occupied);
	}
	
	return EX_SUCCESS;

}


static __forceinline void exArrayFree(exArray* arr)
{
	exFree(arr->memory);
	arr->allocated = 0;
	arr->count = 0;
	arr->occupied = 0;
	arr->memory = NULL;
}

#endif