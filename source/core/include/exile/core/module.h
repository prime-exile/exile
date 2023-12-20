#ifndef _EXILE_CORE_MODULE_H_
#define _EXILE_CORE_MODULE_H_

#include <exile/core/path.h>
#include <exile/core/API.h>

#if defined(EXILE_WIN)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
typedef HINSTANCE exNativeModuleRawHandle;
#elif defined(EXILE_UNIX)
#include <dlfcn.h>
typedef void* exNativeModuleRawHandle;
#endif

typedef enum
{
	exNativeModuleType_Shared = 0,
	exNativeModuleType_InBuilt = 1,
}exNativeModuleType;

typedef struct
{
	exFilePath path;
	exNativeModuleRawHandle handle;
	u8 moduleType;
} exNativeModule;

EX_API u8 exNativeModuleLoad(exNativeModule* mdl, const char* path);
EX_API void* exNativeModuleGetAddress(exNativeModule* mdl, const char* name);
EX_API void exNativeModuleFree(exNativeModule* mdl);

#endif