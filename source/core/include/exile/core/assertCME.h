#ifndef _EXILE_CORE_ASSERT_CME_H_
#define _EXILE_CORE_ASSERT_CME_H_

#include <exile/core/API.h>
#include <exile/core/thread/thread.h>

#if defined(EXILE_WIN)
#include<Windows.h>
#include<DbgHelp.h>
#include <stdio.h>
#elif defined(EXILE_UNIX)
#include <errno.h>
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>

//#include <cxxabi.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <execinfo.h>
#endif

#if defined(EXILE_WIN)
static __forceinline void exAssertFormatDword64ToString(char* buffer, u32 buflen, ...)
{
	va_list args;
	va_start(args, buflen);
	vsnprintf(buffer, buflen, "%016llX", args);
	va_end(args);
}

#endif

static __forceinline u8 exCMEAssertCollectStacktrace()
{
#if defined(EXILE_WIN)
	// Initialize symbol handling
	SymSetOptions(SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS);
	HANDLE process = GetCurrentProcess();
	SymInitialize(process, NULL, TRUE);

	// Capture context
	CONTEXT context;
	RtlCaptureContext(&context);

	// Initialize stack frame for walking
	STACKFRAME64 stackFrame;
	DWORD machineType = IMAGE_FILE_MACHINE_I386;

#ifdef _M_X64
	machineType = IMAGE_FILE_MACHINE_AMD64;
	stackFrame.AddrPC.Offset = context.Rip;
	stackFrame.AddrPC.Mode = AddrModeFlat;
	stackFrame.AddrFrame.Offset = context.Rbp;

	stackFrame.AddrFrame.Mode = AddrModeFlat;
	stackFrame.AddrStack.Offset = context.Rsp;
	stackFrame.AddrStack.Mode = AddrModeFlat;
#else
	stackFrame.AddrPC.Offset = context.Eip;
	stackFrame.AddrPC.Mode = AddrModeFlat;
	stackFrame.AddrFrame.Offset = context.Ebp;

	stackFrame.AddrFrame.Mode = AddrModeFlat;
	stackFrame.AddrStack.Offset = context.Esp;
	stackFrame.AddrStack.Mode = AddrModeFlat;
#endif

/*
	TO DO:
	check documentation about winapi `_CONTEXT`
*/

#if !defined(WIN64)

#else

#endif



	// Walk the stack
	const int maxFrames = 32;

	exCMEStackTraceReserve(maxFrames);
	for (int frameNum = 0; frameNum < maxFrames; ++frameNum) {
		BOOL result = StackWalk64(
			machineType,
			process,
			GetCurrentThread(),
			&stackFrame,
			&context,
			NULL,
			SymFunctionTableAccess64,
			SymGetModuleBase64,
			NULL
		);

		if (!result || stackFrame.AddrFrame.Offset == 0) {
			break;
		}

		// Get function name and offset
		char symbolBuffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
		PSYMBOL_INFO symbol = (PSYMBOL_INFO)symbolBuffer;
		symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
		symbol->MaxNameLen = MAX_SYM_NAME;

		DWORD64 displacement = 0;
		if (SymFromAddr(process, stackFrame.AddrPC.Offset, &displacement, symbol)) {
			char entry[1024];
			char displacementBuffer[512];
			exMemset(entry, 0, 1024);
			strcpy(entry, symbol->Name);
			strcat(entry, "+");

			exAssertFormatDword64ToString(displacementBuffer, 512, displacement);
			strcat(entry, displacementBuffer);

			exCMEAddStackTrace(entry);
			//std::cout << "[" << frameNum << "] " << symbol->Name << " + " << displacement << std::endl;
		}
		else {

			exCMEAddStackTrace("unknown");

			//std::cout << "[" << frameNum << "] <unknown function>" << std::endl;
		}
	}

	// Cleanup symbol handling
	SymCleanup(process);

	return EX_SUCCESS;
#elif defined(EXILE_UNIX)
	void* stackTrace[10];
	int stackSize = backtrace(stackTrace, 10);
	char** stackSymbols = backtrace_symbols(stackTrace, stackSize);


	if (stackSymbols == NULL)
	{
		perror("backtrace_symbols");
		return EX_ERROR;
	}

	for (int i = 0; i < stackSize; ++i)
	{
		exCMEAddStackTrace(stackSymbols[i]);
	}

	free(stackSymbols);

	return EX_SUCCESS;
#endif
}

static __forceinline u8 exCMEDump()
{
	exCMEAssertCollectStacktrace();
	exCMESetThreadId(exThreadGetCurrentId());
	
	return EX_SUCCESS;
}


#endif