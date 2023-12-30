#ifndef _EXILE_CORE_PLUGIN_HPP_
#define _EXILE_CORE_PLUGIN_HPP_

#include<exile/core/containers/string.hpp>
extern "C"
{
#include <exile/core/version.h>
}

namespace exile
{
	namespace core
	{
		class IPlugin
		{
			u8 type;
			exile::String name;
			exVersion version;

		protected:

			inline IPlugin(const exile::String& name, const u8 type, const exVersion& version)
				:name(name), type(type), version(version)
			{
				
			}

		public:

			const exVersion& GetVersion() const
			{
				return version;
			}

			virtual const exile::String& GetDescription() const
			{
				return "";
			}

			const u8 GetType() const
			{
				return type;
			}

			const exile::String& GetName() const
			{
				return name;
			}

			virtual ~IPlugin()
			{

			}
		};

	}
}

#endif