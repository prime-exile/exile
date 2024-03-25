#ifndef _EXILE_CORE_PATH_H_
#define _EXILE_CORE_PATH_H_

#include<exile/core/API.h>

#if defined(EXILE_DYNAMIC_PATH_LEN)
#include<exile/core/array.h>
#else
	#if defined(EXILE_CUSTOM_PATH_LEN)
		#define EX_PATH_LEN EXILE_CUSTOM_PATH_LEN
	#else 
		#if defined(EXILE_WIN)
			#if defined(EXILE_WIN_LONG_PATH)
				#define EX_PATH_LEN 32767
			#else 
				#define EX_PATH_LEN 260
			#endif
		#elif defined(EXILE_UNIX)
			#define EX_PATH_LEN 4096
		#endif
	#endif

#endif

typedef enum
{
	exFilePathType_Invalid,
	exFilePathType_Dir,
	exFilePathType_File
} exFilePathType;

#if defined(EX_PATH_LEN)

typedef struct
{
	char path[EX_PATH_LEN];
} exFilePath;


#else
typedef struct
{
	exArray path;
} exFilePath;

#endif

EX_API u8 exFilePathInit(exFilePath* path);
EX_API u8 exFilePathInit2(exFilePath* path, const char* newPath);
EX_API exFilePathType exFilePathGetType(exFilePath* path);
EX_API const char* exFilePathGetFileExtension(exFilePath* path);
EX_API void exFilePathGetFileName(exFilePath* path, char* buffer, u16 len);
EX_API const char* exFilePathGetCStr(const exFilePath* path);

EX_API u8 exFilePathCopy(exFilePath* dest, const exFilePath* src);
EX_API u8 exFilePathAppend(exFilePath* path, char c);

EX_API void exFilePathFree(exFilePath* path);


#endif
