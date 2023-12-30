#ifndef _EXILE_CORE_PLUGIN_LOADER_HPP_
#define _EXILE_CORE_PLUGIN_LOADER_HPP_

#include <exile/core/containers/string.hpp>
#include <exile/core/API.h>
extern "C"
{
#include <exile/core/version.h>
}

namespace exile
{
	namespace core
	{
		class PluginManager;
		class IPlugin;

		typedef u16 PluginId;
		constexpr PluginId PluginIdInvalid = UINT16_MAX;

		class IPluginLoader
		{
			u8 type;

		protected:

			IPluginLoader(u8 freeTypeId)
				:type(freeTypeId)
			{

			}

		public:

			virtual u8 operator()(exile::core::PluginManager* manager, const exile::String& entry, const exVersion& version, exile::core::PluginId id)
			{
				return 0;
			}

			virtual void Unload(exile::core::IPlugin* plugin, exile::core::PluginId id)
			{

			}

			inline void RegisterType(u8 type)
			{
				this->type = type;
			}

			inline const u8 SupportedPluginType() const
			{
				return type;
			}

			virtual exile::String GetPluginTypeTitle() const 
			{
				return "None";
			}
		};
	}
}

#endif