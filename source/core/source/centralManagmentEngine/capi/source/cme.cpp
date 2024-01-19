#define EXILE_PRIVATE
#include <exile/core/cme/instance.hpp>
#include <exile/core/instance.hpp>

extern "C"
{
#include <exile/core/cme/cme.h>
	

	EXILE_API_EXPORT void exCMEInstallPanicMessage(const char* msg)
	{
		exGEngine.GetCME().SetPanicMessage(msg);
	}

	EXILE_API_EXPORT void exCMERunShell()
	{
		exGEngine.GetCME().RunShell();
	}

	EXILE_API_EXPORT void exCMESetContinueExectionState(u8 state)
	{
		exGEngine.GetCME().SetContinueExectionState(state);
	}
	
	EXILE_API_EXPORT u8 exCMEContinue()
	{
		return exGEngine.GetCME().Continue();
	}

	EXILE_API_EXPORT void exCMEInstallStackTrace(const char** const entry, u64 size)
	{
		exGEngine.GetCME().InstallStackTrace(entry, size);
	}

	EXILE_API_EXPORT void exCMEAddStackTrace(const char* entry)
	{
		exGEngine.GetCME().AddStackTraceEntry(entry);
	}

	EXILE_API_EXPORT void exCMESetThreadId(u64 id)
	{
		exGEngine.GetCME().SetThreadId(id);
	}

	EXILE_API_EXPORT void exCMEStackTraceReserve(u32 count)
	{
		exGEngine.GetCME().StackTraceReserve(count);
	}
}