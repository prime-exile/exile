#define EXILE_PRIVATE
#include <exile/core/cme/panic.hpp>
#include <exile/core/instance.hpp>

extern "C"
{
#include <exile/core/critical.h>
#include <exile/core/memory.h>
}

#include <cstdarg>
#include <inttypes.h>

static u8 exCMEPanic(const char* message, const char* filename, const u64 line, const char* function, ...)
{
	va_list args;
	va_start(args, function);

	int FormatedMessageSize = vsnprintf(NULL, 0, message, args);
	char* buffer = (char*)exMalloc(FormatedMessageSize + 1);

	if (buffer == NULL)
	{
		/*
			TO DO:
			may be better output
		*/
		exit(-1);
	}

	va_start(args, function);
	FormatedMessageSize = vsnprintf(buffer, FormatedMessageSize + 1, message, args);

	buffer[FormatedMessageSize] = '\0';

	va_end(args);
	
	exile::String strBuffer(buffer);
	exFree(buffer);
	
	return exGEngine->GoToCMEPanic(strBuffer.c_str());
}

EXILE_API_EXPORT
void exile::cme::InstallPanicHandler()
{
	/*
		TO DO:
		make cme warning handler
	*/
	exSetupCriticalConfiguration(exCMEPanic, exCMEPanic);
}