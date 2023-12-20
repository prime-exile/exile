#include "shared.h"

void exNativeModuleFree(exNativeModule *mdl)
{
	if(mdl->handle == NULL) return;
#if defined(EXILE_WIN)
	FreeLibrary(mdl->handle);
#elif defined(EXILE_UNIX)
	dlclose(mdl->handle);
#endif
	exFilePathFree(&mdl->path);

	mdl->handle = NULL;
}
