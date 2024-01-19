#include "vsoutputLogHandler.hpp"

static __forceinline u8 DebugOutput(const char* desc, ...)
{
	va_list list;
	va_start(list, desc);

	int formatedMessageSize = vsnprintf(NULL, 0, desc, list);
	char* buffer = exile::memory::AllocRaw<char>(formatedMessageSize + 1);
	exAssertR(buffer == NULL, { va_end(list); }, EX_ERROR, "buffer == NULL");
	vsnprintf(buffer, formatedMessageSize, desc, list);

	buffer[formatedMessageSize] = '\0';

	OutputDebugStringA(buffer);

	exile::memory::Free(static_cast<void*>(buffer));
	va_end(list);

	return EX_SUCCESS;
}


const u64 exile::VSOutLogHandler::Handle(exile::UniversalLoggingProtocol* proto, const exile::String& message, const exile::LogSource& source, exile::LogLevel level)
{
	register u8 res = DebugOutput("[%s][%s]: %s\r\n", exile::LogLevelToString(level), source.GetName().c_str(), message.c_str());

	exAssertR(
		res != EX_SUCCESS, {}, EX_ERROR, "buffer == NULL");
	return EX_SUCCESS;
}

const exile::LogSourceType exile::VSOutLogHandler::SourceTypeFilter() const
{
	return exile::LogSourceType::LogSourceTypeALL;
}

const exile::LogLevel exile::VSOutLogHandler::LogLevelFilter() const
{
	return exile::LogLevel::LogLevelAll;
}