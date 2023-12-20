#ifndef _EXILE_CORE_LOG_HANDLER_HPP_
#define _EXILE_CORE_LOG_HANDLER_HPP_

#include<exile/core/containers/string.hpp>
#include<exile/core/ulp/LogSource.hpp>
#include<exile/core/ulp/LogLevel.hpp>

namespace exile
{
	class UniversalLoggingProtocol;

	class LogHandler
	{

	public:

		virtual const u64 Handle(exile::UniversalLoggingProtocol* proto, const exile::String& message, const exile::LogSource& type, exile::LogLevel level)
		{
			return EX_SUCCESS;
		}

		virtual const exile::LogSourceType SourceTypeFilter() const
		{
			return exile::LogSourceType::LogSourceTypeALL;
		}

		virtual const exile::LogLevel LogLevelFilter() const
		{
			return exile::LogLevel::LogLevelAll;
		}

		virtual const char* GetName() const
		{
			return "unnamed!";
		}

	};
}


#endif