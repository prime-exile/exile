#include <exile/core/critical.hpp>
#include <exile/core/instance.hpp>
#include <exile/core/cme/panic.hpp>
#include <exile/core/assertNew.h>
#include <exile.window/loader.h>
#include <exile.window/window.h>
#include <exile/forge/boot.h>

#define EX_CHECK(res, message)\
		if (res != EX_SUCCESS)\
		{\
			exile::UniversalLoggingProtocol::Get()->Log(exile::UniversalLoggingProtocol::Get()->GetCoreId(), exile::LogLevel::Error, message);\
			return -1;\
		}\

 
int32_t exMain()
{
	try
	{

		exSetupCriticalDefaultConfiguration();
		exile::cme::InstallPanicHandler();

		u8 res = exGEngine->GetPluginManager().LoadPlugin("exDefaultULP");
		EX_CHECK(res, "failed to load exDefaultULP");

		exile::UniversalLoggingProtocol::Get()->Log(exile::UniversalLoggingProtocol::Get()->GetCoreId(), exile::LogLevel::Info, "loaded exDefaultULP");

		res = exGEngine->GetPluginManager().LoadPlugin("exile.window");
		EX_CHECK(res, "failed to load exile.window");
		
		exile::UniversalLoggingProtocol::Get()->Log(exile::UniversalLoggingProtocol::Get()->GetCoreId(), exile::LogLevel::Info, "loaded exile.window");
		exile::core::NativePlugin* plugin = reinterpret_cast<exile::core::NativePlugin*>(
		exGEngine->GetPluginManager().GetPluginByName("PRIME_EXILE_WINDOW"));
		
		res = exWindowInit(plugin);
		EX_CHECK(res, "failed to load exile.window");
		
		exWindow wnd;
		exWindowCreate(&wnd, "testable3", 512, 640);

		while (!exWindowShouldClose(&wnd))
		{

			exWindowUpdate(&wnd);
		}

		exWindowClose(&wnd);

		exGEngine->GetCME().SetPanicMessage("none");
		exGEngine->GetCME().RunShell();
		exGEngine->GetPluginManager().UnloadPlugins();
	}
	catch (const std::exception& ex)
	{
		exCMEDump();
		exPanic(ex.what());
	}
}