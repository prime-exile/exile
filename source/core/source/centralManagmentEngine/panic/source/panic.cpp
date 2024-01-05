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
	va_end(args);
	char* buffer = (char*)exMalloc(FormatedMessageSize + 1);
	/*
		TO DO Buffer == NULL!
	*/
	//if (buffer == NULL)
	//{
	//	printf("message(buffer == NULL): %s in %s line %" PRIu64 " (function '%s')\n", message, filename, line, function);
	//}

	snprintf(buffer, FormatedMessageSize + 1, message, args);

	buffer[FormatedMessageSize] = '\0';

	va_end(args);
	
	exile::String strBuffer(buffer);
	exFree(buffer);
	
	return exile::core::Engine::Get().GoToCMEPanic(strBuffer.c_str());
}

EXILE_API_EXPORT
void exile::cme::InstallPanicHandler()
{
	exSetupCriticalConfiguration(exCMEPanic);
}