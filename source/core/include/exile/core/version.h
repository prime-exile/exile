#ifndef _EXILE_CORE_VERSION_H_
#define _EXILE_CORE_VERSION_H_

#include <exile/core/API.h>

typedef union 
{
	struct 
	{
		u8 minor:8;
		u8 major:8;
		u16 alpha:16;
	} components;

	u32 version;
}exVersionRaw;

typedef struct
{
	exVersionRaw ver;
	u8 isExp;
} exVersion;

EX_API u8 exVersionParse(exVersion* out, const char* str);

EX_API u32 exVersionStr(const exVersion* in, u32 bufferSize, char* buffer);

#endif
