#ifndef _EXILE_DULP_STDOUT_LOG_HANDLER_HPP_
#define _EXILE_DULP_STDOUT_LOG_HANDLER_HPP_

#include <exile/core/ulp/LogHandler.hpp>

namespace exile
{
	class StdOutLogHandler final : public exile::LogHandler
	{

	public:
		const u64 Handle(exile::UniversalLoggingProtocol* proto, const exile::String& message, const exile::LogSource& type, exile::LogLevel level) override;

		const exile::LogSourceType SourceTypeFilter()const override;

		const exile::LogLevel LogLevelFilter() const override;

		const char* GetName() const
		{
			return "exileDefaultULP:StdOutLogHandler";
		}


	};
}
#endif