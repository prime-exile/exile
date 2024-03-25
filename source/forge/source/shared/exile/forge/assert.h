#ifndef _FORGE_BOOT_ASSERT_H_
#define _FORGE_BOOT_ASSERT_H_

#include <exile/core/critical.h>

#define EX_ForgeAssert(pred, message)\
	if(pred){\
		exPanic(message); \
	}

#define EX_ForgeAssertR(pred, value, message)\
	if(pred){\
		exPanic(message);\
		return value;\
	}

#define EX_ForgeAssertF(pred, message, ...)\
	if(pred){\
		exPanicF(message, __VA_ARG__);\
	}\

#define EX_ForgeAssertFR(pred, value, message,...)\
	if(pred){\
		exPanicF(message, __VA_ARG__);\
		return value;\
	}

#endif