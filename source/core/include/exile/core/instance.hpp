#ifndef _EXILE_CORE_INSTANCE_HPP_
#define _EXILE_CORE_INSTANCE_HPP_

#include <exile/core/ulp/ulp.hpp>
#include <exile/core/pluginManager.hpp>
#include <exile/core/nativePlugin.hpp>
#include <exile/core/cme/instance.hpp>
#include <exile/core/cme/shellConsole.hpp>

namespace exile
{
	namespace core
	{
		class EX_API Engine
		{
			static Engine instance;

			exile::cme::ShellConsole consoleShell;
			exile::UniversalLoggingProtocol ulp;
			exile::core::NativePluginLoader nativePluginLoader;
			exile::core::PluginManager pluginManager;
			exile::cme::CentralManagmentEngine centralManagmentEngine;
		public:

			static Engine& Get();

			Engine();

			u8 LoadAllPluginsFromFolder(const exile::String& folder);
			u8 LoadAllPluginsFromFolder(const exile::core::Path& folder);

			exile::UniversalLoggingProtocol& GetULP();
			exile::core::PluginManager& GetPluginManager();

			u8 GoToCMEPanic(const char* message);

		};
	}
}

#endif