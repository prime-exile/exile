#include <exile/core/API.h>
#include <exile/core/nativePlugin.hpp>
#include <exile/core/instance.hpp>

exile::core::PluginId gThisID = 0;
exile::LogId gThisLogId = 0;

#if defined(EXILE_UNIX) && defined(EXILE_WINDOW_WAYLAND)
#include <wayland-client.h>

extern struct wl_display* display;
#endif


#if defined(EXILE_UNIX) && defined(EXILE_WINDOW_X11)
#include <X11/Xlib.h>

extern Display* display;
#endif

extern "C"
{
	EXILE_API_EXPORT const char* exPluginName()
	{
		return "PRIME_EXILE_WINDOW";
	}

	EXILE_API_EXPORT u8 exPluginInit(exile::core::NativePlugin* plugin, exile::core::PluginId id)
	{
		gThisID = id;
		exile::LogSource source(exile::LogSourceTypePlugin, exPluginName());

		exAssertR(exile::UniversalLoggingProtocol::Get()->RegisterSource(source, gThisLogId) != EX_SUCCESS, {}, 
			EX_ERROR, "failed to register ULP source");

		return EX_SUCCESS;
	}


	EXILE_API_EXPORT void exPluginTermiate()
	{
#if defined(EXILE_UNIX) && defined(EXILE_WINDOW_WAYLAND)
		if(display != NULL)
		{
			wl_display_disconnect(display);
#endif
		}
#if defined(EXILE_UNIX) && defined(EXILE_WINDOW_X11)
		if (display != NULL)
		{
			XCloseDisplay(display);
		}
#endif
		exile::UniversalLoggingProtocol::Get()->RemoveSource(gThisLogId);
	}

}
