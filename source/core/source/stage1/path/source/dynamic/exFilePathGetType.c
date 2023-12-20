#include <exile/core/path.h>
#include <exile/core/memory.h>

#if defined(EXILE_WIN)
#include <Windows.h>
#elif defined(EXILE_UNIX)
#include <sys/types.h>
#include <sys/stat.h>
#endif

EXILE_API_EXPORT
exFilePathType exFilePathGetType(exFilePath* path)
{
#if defined(EXILE_WIN)
	DWORD dwAttrib = GetFileAttributes(path->path.memory);

	if (dwAttrib == INVALID_FILE_ATTRIBUTES)
	{
		return exFilePathType_Invalid;
	}
	else if (dwAttrib == FILE_ATTRIBUTE_DIRECTORY)
	{
		return exFilePathType_Dir;
	}
	else
	{
		return exFilePathType_File;
	}
#else
	struct stat sb;

	if (stat(path->path.memory, &sb) == -1)
	{
		return exFilePathType_Invalid;
	}
	else if (S_ISDIR(sb.st_mode))
	{
		return exFilePathType_Dir;
	}
	else if (S_ISREG(sb.st_mode))
	{
		return exFilePathType_File;
	}
	else
	{
		return exFilePathType_Invalid;
	}
#endif
}
