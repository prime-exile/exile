#include <inttypes.h>

#include <stdio.h>
#include <stdarg.h>

#define EXILE_PRIVATE
#include <exile/core/critical.h>
#include <exile/core/string/u64ToString.h>
#include <exile/core/psstring.h>
#include <exile/core/module.h>


extern exNativeModule mdl;

static u8 exDefaultPanic(const char* message, const char* filename, const u64 line, const char* function, ...)
{
	va_list args;
	va_start(args, function);

	int FormatedMessageSize = vsnprintf(NULL, 0, message, args);
	va_end(args);
	if (FormatedMessageSize + 1 < 512)
	{
		exString512x messageTmpBuffer;
		exString512xInit(&messageTmpBuffer);
		va_start(args, function);
		int size= vsnprintf(messageTmpBuffer.buffer, FormatedMessageSize + 1, message, args);
		messageTmpBuffer.buffer[FormatedMessageSize] = '\0';
		va_end(args);
		printf("message: %s in %s line %" PRIu64 " (function '%s')\n", messageTmpBuffer.buffer, filename, line, function);
	}
	else
	{
		char* buffer = exMalloc(FormatedMessageSize + 1);
		if (buffer == NULL)
		{
			printf("message(buffer == NULL): %s in %s line %" PRIu64 " (function '%s')\n", message, filename, line, function);
		}

		snprintf(buffer, FormatedMessageSize + 1, message, args);

		buffer[FormatedMessageSize] = '\0';

		va_end(args);
		printf("message: %s in %s line %" PRIu64 " (function '%s')\n", buffer, filename, line, function);

		exFree(buffer);
	}
	
	return EX_TRUE;
}

EXILE_API_EXPORT
void exSetupCriticalDefaultConfiguration()
{
	mdl.moduleType = exNativeModuleType_InBuilt;
	gExileCriticalInstance.panic = exDefaultPanic;
}
