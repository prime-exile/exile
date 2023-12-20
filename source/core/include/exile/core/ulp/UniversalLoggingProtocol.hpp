#ifndef _EXILE_CORE_UNIVERSAL_LOGGING_PROTOCOL_HPP_
#define _EXILE_CORE_UNIVERSAL_LOGGING_PROTOCOL_HPP_

#include <exile/core/containers/vector.hpp>
#include <exile/core/ulp/LogHandler.hpp>
#include <exile/core/ulp/LogLevel.hpp>
#include <exile/core/ulp/LogSource.hpp>

namespace exile
{
	typedef u64 LogId;

	class EX_API UniversalLoggingProtocol
	{
		exile::Vector<LogHandler*> handlers;
		exile::Vector<LogSource> sources;
		LogId coreId;
	public:

		UniversalLoggingProtocol();

		const LogId& GetCoreId() const;

		void Log(u64 sourceId, exile::LogLevel Level, const exile::String& desc);
		void Log(u64 sourceId, exile::LogLevel Level, const char* desc, ...);

		u8 RegisterSource(const LogSource& source);
		u8 RegisterSource(const LogSource& source, LogId& sourceId);

		u8 RegisterHandler(LogHandler* handler);
		u8 RegisterHandler(LogHandler* handler, LogId& handlerId);

		u8 RemoveSource(const exile::String& name);
		u8 RemoveHandler(const exile::String& name);

		void RemoveSource(const LogId id);
		void RemoveHandler(const LogId id);

	};
}

#endif