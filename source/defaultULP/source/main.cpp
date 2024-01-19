#include <exile/core/API.h>
#include <exile/core/nativePlugin.hpp>
#include <exile/core/instance.hpp>
#include <iostream>

#if defined(EXILE_DULP_STDOUT)
#include "stdout/stdoutLogHandler.hpp"
#endif

#if defined(EXILE_DULP_VS_OUTPUT)
#include "vsoutput/vsoutputLogHandler.hpp"
#endif

exile::core::PluginId gCurrentPluginId = 0;

extern "C"
{
#if defined(EXILE_DULP_STDOUT)
	exile::StdOutLogHandler stdOutLogHandler;
	exile::LogId stdOutHandlerId = 0;
#endif

#if defined(EXILE_DULP_VS_OUTPUT)
	exile::VSOutLogHandler vsOutLogHandler;
	exile::LogId vsOutHandlerId = 0;

#endif


	EXILE_API_EXPORT const char* exPluginName()
	{
		return "exDefaultULP";
	}

	EXILE_API_EXPORT u8 exPluginInit(exile::core::NativePlugin* plugin, exile::core::PluginId id)
	{
		gCurrentPluginId = id;

#if defined(EXILE_DULP_STDOUT)
		exGEngine.GetULP().RegisterHandler(&stdOutLogHandler, stdOutHandlerId);
#endif

#if defined(EXILE_DULP_VS_OUTPUT)
		exGEngine.GetULP().RegisterHandler(&vsOutLogHandler, vsOutHandlerId);
#endif
		return EX_SUCCESS;
	}


	EXILE_API_EXPORT void exPluginTermiate()
	{
#if defined(EXILE_DULP_STDOUT)
		exGEngine.GetULP().RemoveHandler(stdOutHandlerId);
		//exile::core::Engine::Get().GetULP().RemoveHandler("exileDefaultULP:StdOutLogHandler");
#endif

#if defined(EXILE_DULP_VS_OUTPUT)
		exGEngine.GetULP().RemoveHandler(vsOutHandlerId);
		//exile::core::Engine::Get().GetULP().RemoveHandler("exileDefaultULP:VSOutLogHandler");
#endif		//exileDefaultULP:VSOutLogHandler
	}


}


