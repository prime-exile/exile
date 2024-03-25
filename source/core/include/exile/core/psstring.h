#ifndef _EXILE_CORE_STATIC_STRING_H_
#define _EXILE_CORE_STATIC_STRING_H_

#include <exile/core/API.h>
#include <exile/core/memory.h>

typedef struct
{
	u8 occupied;
	char buffer[256];
}exString256x;

static __forceinline void exString256xInit(exString256x* str)
{
	str->occupied = 0;
	exMemset(str->buffer, 0, 256);
}

static __forceinline void exString256xPushChar(exString256x* str, char s)
{
	str->buffer[str->occupied] = s;
	str->occupied += 1;
}

static __forceinline void exString256xClear(exString256x* str)
{
	str->occupied = 0;
	exMemset(str->buffer, 0, 256);
}

static __forceinline void exString256xCopy(exString256x* dest, exString256x* src)
{
	dest->occupied = src->occupied;
	exMemcpy(dest->buffer, src->buffer, 256);
}

typedef struct
{
	u8 occupied;
	char buffer[512];
}exString512x;


static __forceinline void exString512xInit(exString512x* str)
{
	str->occupied = 0;
	exMemset(str->buffer, 0, 512);
}

static __forceinline void exString512xPushChar(exString512x* str, char s)
{
	str->buffer[str->occupied] = s;
	str->occupied += 1;
}

static __forceinline void exString512xClear(exString512x* str)
{
	str->occupied = 0;
	exMemset(str->buffer, 0, 512);
}

static __forceinline void exString512xCopy(exString512x* dest, exString512x* src)
{
	dest->occupied = src->occupied;
	exMemcpy(dest->buffer, src->buffer, 512);
}

typedef struct
{
	u8 occupied;
	char buffer[1024];
}exString1024x;


static __forceinline void exString1024xInit(exString1024x* str)
{
	str->occupied = 0;
	exMemset(str->buffer, 0, 1024);
}

static __forceinline void exString1024xPushChar(exString1024x* str, char s)
{
	str->buffer[str->occupied] = s;
	str->occupied += 1;
}

static __forceinline void exString1024xClear(exString1024x* str)
{
	str->occupied = 0;
	exMemset(str->buffer, 0, 1024);
}

static __forceinline void exString1024xCopy(exString1024x* dest, exString1024x* src)
{
	dest->occupied = src->occupied;
	exMemcpy(dest->buffer, src->buffer, 1024);
}


#endif