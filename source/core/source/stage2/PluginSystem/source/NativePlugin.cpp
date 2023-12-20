#include <exile/core/nativePlugin.hpp>

exile::core::NativePlugin::NativePlugin()
	:exile::core::IPlugin("", 0), 
	handle(NULL)
{

}

exile::core::NativePlugin::NativePlugin(RawPluginHandle handle)
	:exile::core::IPlugin("",0),
	handle(handle)
{

}

exile::core::NativePlugin::NativePlugin(u8 type, RawPluginHandle handle)
	:exile::core::IPlugin("", type),
	handle(handle)
{

}
exile::core::NativePlugin::NativePlugin(const exile::String& name, u8 type, RawPluginHandle handle)
	:exile::core::IPlugin(name, type),
	handle(handle)
{

}

exile::core::NativePlugin::NativePlugin(const exile::String& name, RawPluginHandle handle)
	:exile::core::IPlugin(name, 0),
	handle(handle)
{

}

void* exile::core::NativePlugin::GetProcAddress(const char* proc)
{
#if defined(EXILE_WIN)
	return ::GetProcAddress(handle, proc);
#elif defined(EXILE_UNIX)
	return dlsym(handle, proc);
#endif
}

void exile::core::NativePlugin::Free()
{
	if (handle != NULL)
	{
#if defined(EXILE_WIN)
		FreeLibrary(handle);
#elif defined(EXILE_UNIX)
		dlclose(handle);
#endif
	}
}

exile::core::RawPluginHandle exile::core::NativePlugin::GetRawHandle()
{
	return handle;
}

exile::core::NativePlugin::~NativePlugin()
{
	Free();
}
