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

	class LogSource
	{
	protected:

		LogSourceType type;
		exile::String name;

	public:
		
		LogSource() 
		{}
		
		inline LogSource(LogSourceType type, const exile::String& name)
		:type(type), name(name)
		{}

		inline LogSource(const LogSource& source)
		:name(source.name), type(source.type)
		{}

		inline const LogSourceType GetType() const
		{
			return type;
		}

		inline const exile::String& GetName() const 
		{
			return name;
		}

		exile::LogSource& operator= (const exile::LogSource& other)
		{
			name = other.name;
			type = other.type;
			return *this;
		}

		exile::LogSource& operator==(exile::LogSource& other) = delete;

		virtual ~LogSource(){}
	};
}


#endif