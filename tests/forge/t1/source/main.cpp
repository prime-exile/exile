#include <exile/core/critical.hpp>
#include <exile/core/instance.hpp>
#include <exile/core/cme/panic.hpp>
#include <exile/core/assertNew.h>
#include <exile.window/loader.h>
#include <exile.window/window.h>
#include <iostream>

#define EX_CHECK(res, message)\
		if (res != EX_SUCCESS)\
		{\
			exile::UniversalLoggingProtocol::Get()->Log(exile::UniversalLoggingProtocol::Get()->GetCoreId(), exile::LogLevel::Error, message);\
			return -1;\
		}\

int main()
{
	try
	{
 		std::cout << exGetAllocatedMemorySize() << std::endl;

		return 1; 


		exSetupCriticalDefaultConfiguration();
		exile::cme::InstallPanicHandler();

		u8 res = exGEngine->GetPluginManager().LoadPlugin("exDefaultULP");
		EX_CHECK(res, "failed to load exDefaultULP");

		exile::UniversalLoggingProtocol::Get()->Log(exile::UniversalLoggingProtocol::Get()->GetCoreId(), exile::LogLevel::Info, "loaded exDefaultULP");


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