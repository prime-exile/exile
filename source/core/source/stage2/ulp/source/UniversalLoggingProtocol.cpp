#include "exile/core/memory.hpp"
#include <cstdio>
#define EXILE_PRIVATE
#include <exile/core/ulp/UniversalLoggingProtocol.hpp>


#include <algorithm> 
#include <stdarg.h>

static __forceinline u8 contains(const exile::Vector<exile::LogSource>& vec, const exile::String& name)
{
	register u64 size = vec.size();
	for (const exile::LogSource& src : vec)
	{
		if (src.GetName() == name) return true;
	}
	return false;
}

static __forceinline u8 contains(const exile::Vector<exile::LogHandler*>& vec, const exile::String& name)
{
	register u64 size = vec.size();
	for (const exile::LogHandler* handler : vec)
	{
		if (handler->GetName() == name) return true;
	}
	return false;
}

exile::UniversalLoggingProtocol::UniversalLoggingProtocol()
{
	exile::LogSource coreSource(exile::LogSourceTypeCore, "exile.core");

	RegisterSource(coreSource, coreId);
}

const  exile::LogId& exile::UniversalLoggingProtocol::GetCoreId() const
{
	return coreId;
}

void exile::UniversalLoggingProtocol::Log(u64 sourceId, exile::LogLevel l, const exile::String& desc)
{
	const exile::LogSource& src = sources[sourceId];

	for (exile::LogHandler* handler : handlers)
	{
		if((handler->LogLevelFilter() & l) && (handler->SourceTypeFilter() & src.GetType()))
		{
			handler->Handle(this, desc, src, l);
		}
	}
}

void exile::UniversalLoggingProtocol::Log(u64 sourceId, exile::LogLevel l, const char* desc, ...)
{
	/*
		CMake option:
		optimized mode 1024!
		dynamic mode - use 1024 if we can, but if we cannot use it will allocate buffer!
		full dynamic mode - use only dynamic allocated buffer!
	*/

#if defined(EXILE_ULP_LOG_OPTIMIZED)
	char buffer[1024];

	va_list args;

	va_start(args, desc);
	vsnprintf(buffer, sizeof(buffer), desc, args);
	va_end(args);

	const exile::LogSource& src = sources[sourceId];

	for (exile::LogHandler* handler : handlers)
	{
		if ((handler->LogLevelFilter() & l) && (handler->SourceTypeFilter() & src.GetType()))
		{
			handler->Handle(this, buffer, src, l);
		}
	}
#elif defined(EXILE_ULP_LOG_DYNAMIC)

	va_list args;

	va_start(args, desc);
	int formatedMessageSize = vsnprintf(NULL, 0, desc, args);
	if (formatedMessageSize + 1 < 1024)
	{
		char buffer[1024];
		vsnprintf(buffer, formatedMessageSize + 1, desc, args);
		const exile::LogSource& src = sources[sourceId];

		for (exile::LogHandler* handler : handlers)
		{
			if ((handler->LogLevelFilter() & l) && (handler->SourceTypeFilter() & src.GetType()))
			{
				handler->Handle(this, buffer, src, l);
			}
		}
	}
	else
	{
		char* buffer = exile::memory::AllocRaw<char>(formatedMessageSize + 2);
		EX_s1AssertF(buffer == NULL, {}, EX_ERROR, "buffer == NULL");
		vsnprintf(buffer, formatedMessageSize + 1, desc, args);
		buffer[formatedMessageSize + 1] = '\0';

		const exile::LogSource& src = sources[sourceId];

		for (exile::LogHandler* handler : handlers)
		{
			if ((handler->LogLevelFilter() & l) && (handler->SourceTypeFilter() & src.GetType()))
			{
				handler->Handle(this, buffer, src, l);
			}
		}

		exile::memory::Free(static_cast<void*>(buffer));
	}
	va_end(args);

#elif defined(EXILE_ULP_LOG_FULL_DYNAMIC)
	va_list args;

	va_start(args, desc);
	int formatedMessageSize = vsnprintf(NULL, 0, desc, args);
	char* buffer = exile::memory::AllocRaw<char>(formatedMessageSize + 1);
	EX_s1AssertF(buffer == NULL, {}, EX_ERROR, "buffer == NULL");
	vsnprintf(buffer, formatedMessageSize, desc, args);
	
	const exile::LogSource& src = sources[sourceId];

	for (exile::LogHandler* handler : handlers)
	{
		if ((handler->LogLevelFilter() & l) && (handler->SourceTypeFilter() & src.GetType()))
		{
			handler->Handle(this, buffer, src, l);
		}
	}

	exile::memory::Free(static_cast<void*>(buffer));

	va_end(args);

	
#endif

}


u8 exile::UniversalLoggingProtocol::RegisterSource(const LogSource& source)
{
	if (contains(sources, source.GetName()))
	{
		return EX_FALSE;
	}

	sources.emplace_back(source);
	
	return EX_SUCCESS;
}

u8 exile::UniversalLoggingProtocol::RegisterSource(const LogSource& source, LogId& sourceId)
{
	if (contains(sources, source.GetName()))
	{
		return EX_FALSE;
	}

	sources.emplace_back(source);
	sourceId = sources.size() - 1;

	return EX_SUCCESS;
}
u8 exile::UniversalLoggingProtocol::RegisterHandler(LogHandler* handler, LogId& handlerId)
{
	if (contains(handlers, handler->GetName()))
	{
		return EX_FALSE;
	}
	handlers.emplace_back(handler);
	handlerId = sources.size() - 1;

	return EX_SUCCESS;
}

u8 exile::UniversalLoggingProtocol::RegisterHandler(LogHandler* handler)
{
	if (contains(handlers, handler->GetName()))
	{
		return EX_FALSE;
	}

	handlers.emplace_back(handler);

	return EX_SUCCESS;
}

u8 exile::UniversalLoggingProtocol::RemoveSource(const exile::String& name)
{
	auto it = std::remove_if(sources.begin(), sources.end(), [name](const exile::LogSource& source) {
		return source.GetName() == name;
	});

	return it == sources.end();
}

u8 exile::UniversalLoggingProtocol::RemoveHandler(const exile::String& name)
{
	auto it = std::remove_if(handlers.begin(), handlers.end(), [name](const exile::LogHandler* handler) {
		return handler->GetName() == name;
	});

	return it == handlers.end();
}

void exile::UniversalLoggingProtocol::RemoveSource(const LogId id)
{
	sources.erase(sources.begin() + id);
}
void exile::UniversalLoggingProtocol::RemoveHandler(const LogId id)
{
	handlers.erase(handlers.begin() + id);
}
