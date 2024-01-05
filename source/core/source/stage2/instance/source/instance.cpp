#define EXILE_PRIVATE
#include <exile/core/instance.hpp>
#include <exile/core/fs/DirectoryIterator.hpp>


exile::core::Engine exile::core::Engine::instance;

exile::core::Engine& exile::core::Engine::Get()
{
	return instance;
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
				const exile::String dir = (folder + "/") + currentName;
				EX_s1AssertFR(pluginManager.LoadPlugin(dir) == EX_SUCCESS, {}, EX_ERROR, "failed to load plugin from directory %s", folder.c_str());
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
				EX_s1AssertFR(pluginManager.LoadPlugin(dir) == EX_SUCCESS, {}, EX_ERROR, "failed to load plugin from directory %s", folder.CStr());
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

exile::UniversalLoggingProtocol& exile::core::Engine::GetULP()
{
	return ulp;
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

exile::core::PluginManager& exile::core::Engine::GetPluginManager()
{
	return pluginManager;
}
