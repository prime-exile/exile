#ifndef _EXILE_CORE_CME_CME_H_
#define _EXILE_CORE_CME_CME_H_

#include <exile/core/API.h>

EX_API void exCMEInstallPanicMessage(const char* msg);

EX_API void exCMERunShell();

EX_API void exCMESetContinueExectionState(u8 state);

EX_API u8 exCMEContinue();

EX_API void exCMEInstallStackTrace(const char** const entry, u64 size);

#endif