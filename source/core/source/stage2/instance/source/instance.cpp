#define EXILE_PRIVATE
#include <exile/core/instance.hpp>
#include <exile/core/fs/DirectoryIterator.hpp>



#if defined(EXILE_BUILD_FORGE)
exile::core::Engine* exGEngine = NULL;
#else
exile::core::Engine _exEngine{};
exile::core::Engine* exGEngine = &_exEngine;
#endif


u8 exile::core::Engine::CollectInformation(exile::core::PluginDepencyMap& depMap, const exile::String& folder)
{
	constexpr const char* pluginConfigSectionName = "exile_" EXILE_PLATFORM_STRING;

	exile::core::Path dirPath(folder);

	exile::core::Path configurationFilePath(folder + "/exile.ini");

	if (!configurationFilePath.exists()) return 0;
	exile::ll::IniParser ini;
	pluginManager.ConfigureIniParser(ini);

	exAssertFR(ini.ParseFromFile(configurationFilePath) != EX_SUCCESS, {}, EX_ERROR, "failed to parse ini file %s", configurationFilePath.Str().c_str());

	const exile::ll::IniInterpretatorSection& pluginConfig = ini.GetInterpretator().GetSection(pluginConfigSectionName);
	const exile::ll::IniInterpretatorSection& pluginTypeSection = ini.GetInterpretator().GetSection("PluginType");
	
	if (ini.GetInterpretator().Containts("Dependices"))
	{
		//ini.GetInterpretator().GetSection()
	}
	const exile::ll::IniInterpretatorSection& pluginDepsSection = ini.GetInterpretator().GetSection("Dependices");
	
	const exile::String pluginEntry = pluginConfig.GetValue("name");


}


u8 exile::core::Engine::LoadAllPluginsFromFolder(const exile::String& folder)
{
	exile::core::DirectoryIterator it(folder);



	while (!it.IsFinished()) 
	{
		const exile::String currentName = it.GetCurrentName();
		if (currentName != "." && currentName != "..") 
		{
			if (it.IsDirectory()) 
			{
				constexpr const char* pluginConfigSectionName = "exile_" EXILE_PLATFORM_STRING;



				//const exile::String dir = (folder + "/") + currentName;
				//exAssertFR(pluginManager.LoadPlugin(dir) == EX_SUCCESS, {}, EX_ERROR, "failed to load plugin from directory %s", folder.c_str());
			}
		}
		++it;
	}

	return EX_SUCCESS;
}

u8 exile::core::Engine::LoadAllPluginsFromFolder(const exile::core::Path& folder)
{
	exile::core::DirectoryIterator it(folder);

	while (!it.IsFinished())
	{
		const exile::String currentName = it.GetCurrentName();
		if (currentName != "." && currentName != "..")
		{
			if (it.IsDirectory())
			{
				const exile::String dir = (folder.Str() + "/") + currentName;
				exAssertFR(pluginManager.LoadPlugin(dir) == EX_SUCCESS, {}, EX_ERROR, "failed to load plugin from directory %s", folder.CStr());
			}
		}
		++it;
	}

	return EX_SUCCESS;
}

exile::core::Engine::Engine()
	:consoleShell(&centralManagmentEngine)
{
	pluginManager.AddPluginLoader(&nativePluginLoader);
	centralManagmentEngine.SetupShell(&consoleShell);
}

exile::cme::CentralManagmentEngine& exile::core::Engine::GetCME()
{
	return centralManagmentEngine;
}

u8 exile::core::Engine::GoToCMEPanic(const char* message)
{
	centralManagmentEngine.SetPanicMessage(message);
	centralManagmentEngine.RunShell();
	return centralManagmentEngine.Continue();
}

u8 exile::core::Engine::Exec(const exile::String& command)
{
	return centralManagmentEngine.GetCommandEngine().Execute(command);
}


exile::core::PluginManager& exile::core::Engine::GetPluginManager()
{
	return pluginManager;
}
