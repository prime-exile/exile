#include "shared.h"

void* exNativeModuleGetAddress(exNativeModule* mdl, const char* name)
{
#if defined(EXILE_WIN)
	return GetProcAddress(mdl->handle, name);
#elif defined(EXILE_UNIX)
	return dlsym(mdl->handle, name);
#endif
}
