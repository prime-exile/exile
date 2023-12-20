#ifndef _EXILE_LOCAL_SHARED_H_
#define _EXILE_LOCAL_SHARED_H_

#define EXILE_PRIVATE

#include <exile/core/path.h>
#include <exile/core/memory.h>

#if defined(EXILE_WIN)
#include<Windows.h>
#elif defined(EXILE_UNIX)
#include<sys/types.h>
#include<sys/stat.h>
#endif

static __forceinline const char* exStringGetLastCharPointer(const char* str, char c)
{
	u64 l = strlen(str);
	const char* it = str;
	const char* end = it + l;

	const char* last = NULL;

	for (; it != end; it += 1)
	{
		if (*it == c) last = it;
	}

	return last;
}

#endif
