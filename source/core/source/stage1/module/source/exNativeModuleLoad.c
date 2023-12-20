#include "shared.h"
#include <exile/core/critical.h>

u8 exNativeModuleLoad(exNativeModule* mdl, const char* path)
{
	LRETURN_IF_FAILED(exFilePathInit2(&mdl->path, path), {});
	
	exFilePathType type = exFilePathGetType(&mdl->path);
	if (type != exFilePathType_File)
	{
		exPanicF("[exLoadModule]: file path '%s' is invalid, or directory", path);
		return EX_ERROR;
	}

#if defined(EXILE_WIN)
	mdl->handle = LoadLibraryA(path);
#elif defined(EXILE_UNIX)
	mdl->handle = dlopen(path, RTLD_LAZY);
#endif

	if (mdl->handle == NULL)
	{
#if defined(EXILE_WIN)
		LPVOID lpMsgBuf;
		DWORD dw = GetLastError();

		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			dw,
			MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf,
			0, NULL);

		printf("Failed to load library: error code %lu\n", dw);
		printf("Error message: %s\n", (LPCTSTR)lpMsgBuf);
		exPanicF("[exLoadModule]: failed to load module %s. error: %s", path, (LPCTSTR)lpMsgBuf);
		LocalFree(lpMsgBuf);

#else
		exPanicF("[exLoadModule]: failed to load module %s. error: %s", path, dlerror());
#endif
		return EX_ERROR;
	}

	return EX_SUCCESS;
}

