#ifndef _EXILE_CORE_API_H_
#define _EXILE_CORE_API_H_

#if defined(EXILE_WIN)
	#define EXILE_API_EXPORT __declspec(dllexport)
	#define EXILE_API_IMPORT __declspec(dllimport)
#elif defined(EXILE_UNIX)
	#define EXILE_API_EXPORT __attribute__((visibility("default"))) 
	#define EXILE_API_IMPORT

	#define __forceinline __attribute__((always_inline))
#endif

#if defined(EXILE_PRIVATE)
#define EX_API EXILE_API_EXPORT
#else
#define EX_API EXILE_API_IMPORT
#endif
// if we dont have here check expression in NULL (void*) reslove error in stdio.h
// void* -> _locale_t
#ifndef __cplusplus
	#ifndef NULL
	#define NULL ((void*)0)
	#endif
#endif

#define EX_FALSE 0
#define EX_TRUE 1

#define EX_ERROR EX_FALSE
#define EX_SUCCESS EX_TRUE

#define EX_BUILD_DATETIME ""__DATE__"@"__TIME__""

#include <stdint.h>

typedef float f32;
typedef double f64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

#endif
