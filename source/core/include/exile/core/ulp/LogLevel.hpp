#ifndef _EXILE_CORE_LOG_LEVEL_HPP_
#define _EXILE_CORE_LOG_LEVEL_HPP_

extern "C"
{
#include <exile/core/API.h>
}

namespace exile
{
	enum LogLevel : u8 
	{
		None = 0,
		Success = 1 << 1,
		Info = 1 << 2,
		Warning = 1 << 3,
		Error = 1 << 4,
		Fatal = 1 << 5,
		LogLevelAll = Success | Info | Warning | Error | Fatal
	};

	__forceinline static const char* LogLevelToString(LogLevel level)
	{
		switch (level)
		{
		case exile::Success: return "Success";
		case exile::Info:return "Info";
		case exile::Warning:return "Warning";
		case exile::Error:return "Error";
		case exile::Fatal:return "Fatal";
		default: return "None";
		}
	}
}


#endif