#include <exile/core/API.h>
#include <exile/core/memory.h>
#include <stdio.h>
#include <stdarg.h>
#include <inttypes.h>

EXILE_API_EXPORT 
void exPanic(const char* message, const char* filename, const u64 line, const char* function, ...)
{
	va_list args;
	va_start(args, function);

	int FormatedMessageSize = vsnprintf(NULL, 0, message, args);
	va_end(args);
	if (FormatedMessageSize + 1 < 512)
	{
		char messageTmpBuffer[512];
		exMemset(messageTmpBuffer, 0, 512);
		va_start(args, function);
		int size = vsnprintf(messageTmpBuffer, FormatedMessageSize + 1, message, args);
		messageTmpBuffer[FormatedMessageSize] = '\0';
		va_end(args);
		printf("message: %s in %s line %" PRIu64 " (function '%s')\n", messageTmpBuffer, filename, line, function);
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


}