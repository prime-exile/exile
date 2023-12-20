#ifndef _EXILE_CORE_LOG_SOURCE_HPP_
#define _EXILE_CORE_LOG_SOURCE_HPP_

#include <exile/core/containers/string.hpp>
#include <exile/core/API.h>

namespace exile
{
	enum LogSourceType : u8
	{
		LogSourceTypeNone,
		LogSourceTypePlugin,
		LogSourceTypeCore,
		LogSourceTypeALL = LogSourceTypeCore | LogSourceTypePlugin
	};

	class  LogSource
	{
		LogSourceType type;
		exile::String name;

	public:
		inline LogSource(LogSourceType type, const exile::String& name)
			:type(type), name(name)
		{

		}

		inline const LogSourceType GetType() const
		{
			return type;
		}

		inline const exile::String& GetName() const 
		{
			return name;
		}
	};
}


#endif