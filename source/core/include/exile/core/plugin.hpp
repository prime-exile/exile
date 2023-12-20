#ifndef _EXILE_CORE_PLUGIN_HPP_
#define _EXILE_CORE_PLUGIN_HPP_

#include<exile/core/containers/string.hpp>

namespace exile
{
	namespace core
	{

		class IPlugin
		{
			u8 type;
			exile::String name;

		protected:

			inline IPlugin(const exile::String& name, const u8 type)
				:name(name), type(type)
			{
				
			}

		public:

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