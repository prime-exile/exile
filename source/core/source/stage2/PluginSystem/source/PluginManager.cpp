#define EXILE_PRIVATE
#include <exile/core/pluginManager.hpp>
#include <exile/core/fs/Path.hpp>

extern "C"
{
#include <exile/core/version.h>
}

#include <exile/core/assert.h>

#include <exile/core/string/u64ToString.hpp>
#include <algorithm>

void exile::core::PluginManager::ConfigureIniParser(exile::ll::IniParser& parser)
{
	exile::ll::IniInterpretatorSection pluginTypeSection;
	
	for (exile::core::IPluginLoader* loader : loaders)
	{
		pluginTypeSection.Add(loader->GetPluginTypeTitle(), exile::u64ToString(loader->SupportedPluginType()));
	}

	parser.AddSection("PluginType", pluginTypeSection);
}

exile::core::PluginManager::PluginManager()
{
}

exile::core::PluginDepencyManager& exile::core::PluginManager::GetDepencyManager()
{
	return depencyManager;
}

u8 exile::core::PluginManager::AddPlugin(exile::core::IPlugin* plugin)
{
	plugins.push_back(plugin);
	return EX_SUCCESS;
}

u8 exile::core::PluginManager::AddPlugin(exile::core::IPlugin* plugin, PluginId& id)
{
	id = plugins.size();
	plugins.push_back(plugin);
	return EX_SUCCESS;
}

exile::core::PluginLoaderId exile::core::PluginManager::AddPluginLoader(exile::core::IPluginLoader* loader)
{
	loader->RegisterType(loaders.size());
	loaders.push_back(loader);
	return EX_SUCCESS;
}

void exile::core::PluginManager::RemovePluginLoader(PluginLoaderId id)
{
	loaders[id] = NULL;
}

exile::core::IPluginLoader* exile::core::PluginManager::GetPluginLoader(const PluginLoaderId id)
{
	for (exile::core::IPluginLoader* loader : loaders)
	{
		if (loader->SupportedPluginType() == id) return loader;
	}

	return NULL;
}

exile::core::IPlugin* exile::core::PluginManager::GetPluginByName(const exile::String& name)
{
	for (exile::core::IPlugin* plugin : plugins)
	{
		if (plugin->GetName() == name)
		{
			return plugin;
		}
	}

	return NULL;
}

exile::core::PluginId exile::core::PluginManager::GetPluginIdByName(const exile::String& name)
{
	exile::core::PluginId counter = 0;
	for (exile::core::IPlugin* plugin : plugins)
	{
		if (plugin->GetName() == name) return counter;
		counter += 1;
	}

	return exile::core::PluginIdInvalid;
}


const exile::Vector<const exile::core::IPlugin*> exile::core::PluginManager::GetPluginDependices(const PluginId id)
{
	exile::Vector<const exile::core::IPlugin*> plugins = {};
	const exile::Vector<PluginId> deps = depencyManager.GetDependices(id);

	for (PluginId dep : deps)
	{
		plugins.push_back(plugins[dep]);
	}

	return plugins;
}

u8 exile::core::PluginManager::LoadPlugin(const exile::String& directory)
{
	exile::core::Path dirPath(directory);
	
	exile::core::Path configurationFilePath(directory + "/exile.ini");

	if (!configurationFilePath.exists()) return 0;
	exile::ll::IniParser ini;
	ConfigureIniParser(ini);

	exAssertFR(ini.ParseFromFile(configurationFilePath) != EX_SUCCESS, {}, EX_ERROR, "failed to parse ini file %s", configurationFilePath.Str().c_str());

	/* ini file example for plugin
		[exile]
		type = PluginType.Native;
		entry = "main.dll";
	*/
	constexpr const char* pluginConfigSectionName = "exile_" EXILE_PLATFORM_STRING;

	const exile::ll::IniInterpretatorSection& pluginConfig = ini.GetInterpretator().GetSection(pluginConfigSectionName);
	const exile::ll::IniInterpretatorSection& pluginTypeSection = ini.GetInterpretator().GetSection("PluginType");

	const exile::String pluginType = pluginConfig.GetValue("type");
	u8 typeId = atoi(pluginType.c_str());

	exile::core::IPluginLoader* loader = GetPluginLoader(typeId);
	exAssertFR(loader == NULL, {}, EX_ERROR, "unregistered loader id: %i for plugin %s", typeId, directory.c_str());
	//if (loader == NULL)
	//{
	//	/*
	//		TO DO ERROR:
	//		UNREGISTERED LOADER!
	//	*/
	//}

	const exile::String pluginEntry = pluginConfig.GetValue("entry");
	exile::String fullPluginEntry = directory + "/";
	fullPluginEntry += pluginEntry;
	
	exVersion pluginVersion{};
	if(pluginConfig.Containts("version"))
	{
		const exile::String pluginVersionStr = pluginConfig.GetValue("version");
		exAssertFR(exVersionParse(&pluginVersion, pluginVersionStr.c_str()) != EX_SUCCESS, {}, EX_ERROR, "failed to parse version string %s", pluginVersionStr.c_str());
	}
	
	exAssertFR((*loader)(this, fullPluginEntry, pluginVersion, plugins.size()) != EX_SUCCESS, {}, EX_ERROR, "failed to load plugin entry for %s", directory.c_str());

	return EX_SUCCESS;
}

u8 exile::core::PluginManager::UnloadPlugin(const exile::String& name)
{
	PluginId id = GetPluginIdByName(name);
	exAssertFR(id == exile::core::PluginIdInvalid, {}, EX_ERROR, "failed to find plugin %s", name.c_str());
	return UnloadPlugin(id);
}

u8 exile::core::PluginManager::UnloadPlugin(const PluginId id)
{
	if (plugins.size() <= id) return EX_FALSE;
	IPlugin* plugin = plugins[id];

	if (!depencyManager.IsPluginDepencyFree(id))return EX_FALSE;

	IPluginLoader* loader = GetPluginLoader(plugin->GetType());
	loader->Unload(plugin, id);

	plugins[id] = NULL;

	unloadedIndices.push_back(id);



	return EX_SUCCESS;
}


void exile::core::PluginManager::UnloadPlugins()
{
	/*
		TO DO:
		may be use stack?
	*/
	std::reverse(plugins.begin(), plugins.end());

	PluginId counter = plugins.size() -1;
	for (exile::core::IPlugin* plugin : plugins)
	{
		exile::core::IPluginLoader* loader = GetPluginLoader(plugin->GetType());
		loader->Unload(plugin, counter);
		counter -=1;
	}
}
