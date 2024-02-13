#ifndef _EXILE_CORE_PLUGIN_MANAGER_HPP_
#define _EXILE_CORE_PLUGIN_MANAGER_HPP_

#include <exile/core/API.h>
#include <exile/core/plugin.hpp>
#include <exile/ll/ini/iniParser.hpp>
#include <exile/core/pluginLoader.hpp>
#include <exile/core/containers/vector.hpp>
#include <exile/core/containers/stack.hpp>


namespace exile
{
	namespace core
	{

		class EX_API PluginDepencyMap
		{
			exile::UnorderedMap<u32, exile::String> names;
			exile::UnorderedMap<u32, exile::Vector<u32>> dependices;

		public:
			
			void RegisterNames(const exile::Vector<exile::String>& names);
			void RegisterDepency(const exile::String& plugin, const exile::String& depency);

			void TryLoadDep(u32 dep);

			void SortDependices(exile::Vector<u32>& out);

			void TranslateSequence(const exile::Vector<u32>& in, exile::Vector<exile::String>& out);

			void DebugPrintNames();

		};

		typedef u8 PluginLoaderId;

		class EX_API PluginDepencyManager
		{
		private:

			exile::UnorderedMap<PluginId, exile::Vector<PluginId>> dependices;

		public:

			PluginDepencyManager()
			{}

			PluginDepencyManager(const PluginDepencyManager& other) = delete;
			
			const exile::Vector<PluginId>& GetDependices(PluginId pluginId) const;

			void RemoveDepency(PluginId depency, PluginId pluginId);

			void AddDepency(PluginId depency, PluginId pluginId);

			PluginId IsPluginDepencyFree(PluginId pluginId);

			exile::core::PluginDepencyManager& operator=(exile::core::PluginDepencyManager& other) = delete;
			exile::core::PluginDepencyManager& operator==(exile::core::PluginDepencyManager& other) = delete;


		};

		class EX_API PluginManager
		{
		private:

			exile::Vector<exile::core::IPlugin*> plugins;
			exile::Vector<exile::core::IPluginLoader*> loaders;

			exile::Vector<PluginId> unloadedIndices;

			PluginDepencyManager depencyManager;

			
		public:
			void ConfigureIniParser(exile::ll::IniParser& parser);
			PluginManager();

			PluginManager(const PluginDepencyManager& other) = delete;

			PluginDepencyManager& GetDepencyManager();

			u8 AddPlugin(exile::core::IPlugin* plugin);
			u8 AddPlugin(exile::core::IPlugin* plugin, PluginId& id);

			PluginLoaderId AddPluginLoader(exile::core::IPluginLoader* loader);
			void RemovePluginLoader(PluginLoaderId id);
			exile::core::IPluginLoader* GetPluginLoader(const PluginLoaderId id);
			exile::core::IPlugin* GetPluginByName(const exile::String& name);
			PluginId GetPluginIdByName(const exile::String& name);

			const exile::Vector<const exile::core::IPlugin*> GetPluginDependices(const PluginId id);

			u8 LoadPlugin(const exile::String& directory);

			u8 UnloadPlugin(const exile::String& name);
			u8 UnloadPlugin(const PluginId id);

			void UnloadPlugins();


			exile::core::PluginManager& operator=(exile::core::PluginManager& other) = delete;
			exile::core::PluginManager& operator==(exile::core::PluginManager& other) = delete;


		};
	}
}

#endif
