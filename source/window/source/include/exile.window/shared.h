#ifndef _EXILE_WINDOW_SHARED_H_
#define _EXILE_WINDOW_SHARED_H_

#include <exile/core/API.h>

typedef struct
{
	void* handle;
	u8 closed;
}exWindow;

typedef enum
{
	exWindowCreationFlag_None = 1 << 0,
	exWindowCreationFlag_Decorated = 1 << 1
} exWindowCreationFlag;

#endif