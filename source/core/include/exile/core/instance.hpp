#ifndef _EXILE_CORE_INSTANCE_HPP_
#define _EXILE_CORE_INSTANCE_HPP_

#include <exile/core/ulp/ulp.hpp>
#include <exile/core/pluginManager.hpp>
#include <exile/core/nativePlugin.hpp>
#include <exile/core/cme/instance.hpp>
#include <exile/core/cme/shellConsole.hpp>
#include <exile/core/storage.hpp>

namespace exile
{
	namespace core
	{
		class EX_API Engine
		{
		private:

			exile::cme::ShellConsole consoleShell;
			exile::UniversalLoggingProtocol ulp;
			exile::core::NativePluginLoader nativePluginLoader;
			exile::core::PluginManager pluginManager;
			exile::cme::CentralManagmentEngine centralManagmentEngine;
			exile::core::EnvironmentStorage env;

		public:

			Engine();
			Engine(const Engine&) = delete;

			u8 LoadAllPluginsFromFolder(const exile::String& folder);
			u8 LoadAllPluginsFromFolder(const exile::core::Path& folder);


			exile::core::EnvironmentStorage& GetEnv();
			exile::UniversalLoggingProtocol& GetULP();
			exile::core::PluginManager& GetPluginManager();
			exile::cme::CentralManagmentEngine& GetCME();

			u8 GoToCMEPanic(const char* message);

			u8 Exec(const exile::String& command);

			exile::core::Engine& operator=(exile::core::Engine& other) = delete;
			exile::core::Engine& operator==(exile::core::Engine& other) = delete;

		};

		
	}
}

extern EX_API exile::core::Engine exGEngine;

#endif