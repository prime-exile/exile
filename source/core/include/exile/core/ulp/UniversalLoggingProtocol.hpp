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
	private:

		static UniversalLoggingProtocol* impl;

	protected:

		exile::Vector<LogHandler*> handlers;
		exile::Vector<LogSource> sources;
		LogId coreId;

	public:

		static void SetupImpl(UniversalLoggingProtocol* impl);
		static UniversalLoggingProtocol* Get();
 
		virtual const exile::Vector<LogHandler*>& GetLogHandlers();
		virtual const exile::Vector<LogSource>& GetSources();

		UniversalLoggingProtocol();
		UniversalLoggingProtocol(const UniversalLoggingProtocol&) = delete;

		const LogId& GetCoreId() const;

		virtual void Log(LogId sourceId, exile::LogLevel Level, const exile::String& desc);
		virtual void Log(LogId sourceId, exile::LogLevel Level, const char* desc, ...);

		virtual u8 RegisterSource(const LogSource& source);
		virtual u8 RegisterSource(const LogSource& source, LogId& sourceId);

		virtual u8 RegisterHandler(LogHandler* handler);
		virtual u8 RegisterHandler(LogHandler* handler, LogId& handlerId);

		virtual u8 RemoveSource(const exile::String& name);
		virtual u8 RemoveHandler(const exile::String& name);

		virtual void RemoveSource(const LogId id);
		virtual void RemoveHandler(const LogId id);

		exile::UniversalLoggingProtocol& operator=(exile::UniversalLoggingProtocol& other) = delete;
		exile::UniversalLoggingProtocol& operator==(exile::UniversalLoggingProtocol& other) = delete;

		virtual ~UniversalLoggingProtocol(){}

	};
}

#endif