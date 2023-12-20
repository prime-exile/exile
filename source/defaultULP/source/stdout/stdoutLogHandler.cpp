#include "stdoutLogHandler.hpp"

const u64 exile::StdOutLogHandler::Handle(exile::UniversalLoggingProtocol* proto, const exile::String& message, const exile::LogSource& source, exile::LogLevel level)
{
	printf("[%s][%s]: %s\n", exile::LogLevelToString(level), source.GetName().c_str(), message.c_str());
	return EX_SUCCESS;
}

const exile::LogSourceType exile::StdOutLogHandler::SourceTypeFilter() const
{
	return exile::LogSourceType::LogSourceTypeALL;
}

const exile::LogLevel exile::StdOutLogHandler::LogLevelFilter() const
{
	return exile::LogLevel::LogLevelAll;
}