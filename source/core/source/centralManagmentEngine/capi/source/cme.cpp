#define EXILE_PRIVATE
#include <exile/core/cme/instance.hpp>
#include <exile/core/instance.hpp>

extern "C"
{
#include <exile/core/cme/cme.h>


	EXILE_API_EXPORT void exCMEInstallPanicMessage(const char* msg)
	{
		exile::core::Engine::Get().GetCME().SetPanicMessage(msg);
	}

	EXILE_API_EXPORT void exCMERunShell()
	{
		exile::core::Engine::Get().GetCME().RunShell();
	}

	EXILE_API_EXPORT void exCMESetContinueExectionState(u8 state)
	{
		exile::core::Engine::Get().GetCME().SetContinueExectionState(state);
	}
	
	EXILE_API_EXPORT u8 exCMEContinue()
	{
		return exile::core::Engine::Get().GetCME().Continue();
	}

	EXILE_API_EXPORT void exCMEInstallStackTrace(const char** const entry, u64 size)
	{
		return exile::core::Engine::Get().GetCME().InstallStackTrace(entry, size);
	}
}