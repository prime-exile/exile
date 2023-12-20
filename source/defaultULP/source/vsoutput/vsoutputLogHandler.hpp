#ifndef _EXILE_DULP_VS_OUT_LOG_HANDLER_HPP_
#define _EXILE_DULP_VS_OUT_LOG_HANDLER_HPP_

#include <exile/core/ulp/LogHandler.hpp>

namespace exile
{
	class VSOutLogHandler final : public exile::LogHandler
	{

	public:
		const u64 Handle(exile::UniversalLoggingProtocol* proto, const exile::String& message, const exile::LogSource& type, exile::LogLevel level);

		const exile::LogSourceType SourceTypeFilter()const;

		const exile::LogLevel LogLevelFilter() const;

		const char* GetName() const
		{
			return "exileDefaultULP:VSOutLogHandler";
		}


	};
}
#endif