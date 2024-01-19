#define EXILE_PRIVATE
#include <exile/core/instance.hpp>
#include <exile/core/fs/DirectoryIterator.hpp>


exile::core::Engine exGEngine;

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
				exAssertFR(pluginManager.LoadPlugin(dir) == EX_SUCCESS, {}, EX_ERROR, "failed to load plugin from directory %s", folder.c_str());
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

exile::UniversalLoggingProtocol& exile::core::Engine::GetULP()
{
	return ulp;
}

exile::core::EnvironmentStorage& exile::core::Engine::GetEnv()
{
	return env;
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
