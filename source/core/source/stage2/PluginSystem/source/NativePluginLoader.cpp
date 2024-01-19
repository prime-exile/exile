#define EXILE_PRIVATE
#include <exile/core/nativePlugin.hpp>
#include <exile/core/instance.hpp>

typedef u8(*PFNexPluginInit)(exile::core::NativePlugin* plugin);
typedef u8(*PFNexPluginInit2)(exile::core::NativePlugin* plugin, exile::core::PluginId id);
typedef void(*PFNexPluginTerminate)();

#if defined(EXILE_WIN)
#define GetAddr(handle, sym)(GetProcAddress(handle, sym))
#elif defined(EXILE_UNIX)
#define GetAddr(handle, sym)(dlsym(handle, sym))
#endif

exile::core::NativePluginLoader::NativePluginLoader(u8 type)
	:exile::core::IPluginLoader(type)
{

}

exile::core::NativePluginLoader::NativePluginLoader()
	:exile::core::IPluginLoader(0)
{
	
}


exile::String exile::core::NativePluginLoader::GetPluginTypeTitle() const
{
	return "Native";
}

u8 exile::core::NativePluginLoader::operator()(exile::core::PluginManager* manager, const exile::String& entry)
{
	return Load(manager, entry);
}

u8 exile::core::NativePluginLoader::operator()(exile::core::PluginManager* manager, const exile::String& entry, const exVersion& version, PluginId id)
{
	return Load(manager, entry, version, id);
}

void exile::core::NativePluginLoader::Unload(exile::core::IPlugin* iplugin, PluginId id)
{
	Unload(iplugin);
}

void exile::core::NativePluginLoader::Unload(exile::core::IPlugin* iplugin) 
{
	exile::core::NativePlugin* plugin = reinterpret_cast<exile::core::NativePlugin*>(iplugin);

	void* terminateAddress = plugin->GetProcAddress("exPluginTermiate");
	if (terminateAddress != NULL)
	{
		PFNexPluginTerminate exPluginTerminate = reinterpret_cast<PFNexPluginTerminate>(terminateAddress);

		exPluginTerminate();
	}

	plugin->Free();
	exile::memory::Free(plugin);
}

u8 exile::core::NativePluginLoader::Load(exile::core::PluginManager* manager, const exile::String& entry, const exVersion& version, PluginId id)
{
#if defined(EXILE_WIN)
	RawPluginHandle handle = LoadLibraryA(entry.c_str());
	/*
	   Load error from system and print!
	*/
	exAssertFR(handle == NULL, {}, EX_ERROR, "LoadLibraryA: failed to load library %s", entry.c_str());
#elif defined(EXILE_UNIX)

	RawPluginHandle handle = dlopen(entry.c_str(), RTLD_LAZY);
	/*
	   Load error from system and print!
	*/
	exAssertFR(handle == NULL, {}, EX_ERROR, "dlopen: failed to load library %s, desc: %s", entry.c_str(), dlerror());
#endif

	exile::String pluginName = "unnamed";
	void* pluginNameAddr = GetAddr(handle, "exPluginName");
	if (pluginNameAddr != NULL)
	{
		const char* (*exPluginName)() = reinterpret_cast<const char* (*)()>(pluginNameAddr);
		pluginName = exPluginName();
	}

	exile::core::NativePlugin* plugin = exile::memory::Alloc<exile::core::NativePlugin>(pluginName, SupportedPluginType(), handle, version);

	PFNexPluginInit2 exPluginInit = reinterpret_cast<PFNexPluginInit2>(plugin->GetProcAddress("exPluginInit"));
	if (exPluginInit != NULL)
	{
		exAssertFR(exPluginInit(plugin, id) != EX_SUCCESS, {
			exile::memory::Free(plugin);
			}, EX_ERROR, "exPluginInit: failed to initialize plugin %s", entry.c_str());
	}

	exAssertFR(manager->AddPlugin(plugin) != EX_SUCCESS, {
		exile::memory::Free(plugin);
		}, EX_ERROR, "failed to add plugin %s in manager!", entry.c_str());

	return EX_SUCCESS;
}

u8 exile::core::NativePluginLoader::Load(exile::core::PluginManager* manager, const exile::String& entry)
{
#if defined(EXILE_WIN)
	 RawPluginHandle handle = LoadLibraryA(entry.c_str());
	 /*
		Load error from system and print!
	 */
	 exAssertFR(handle == NULL, {}, EX_ERROR, "LoadLibraryA: failed to load library %s", entry.c_str());
#elif defined(EXILE_UNIX)

	RawPluginHandle handle = dlopen(entry.c_str(), RTLD_LAZY);
	/*
	   Load error from system and print!
	*/
	exAssertFR(handle != NULL, {}, EX_ERROR, "dlopen: failed to load library %s, desc: %s", entry.c_str(), dlerror());
#endif

	exile::String pluginName = "unnamed";
	void* pluginNameAddr = GetAddr(handle, "exPluginName");
	if (pluginNameAddr != NULL)
	{
		const char* (*exPluginName)() = reinterpret_cast<const char*(*)()>(pluginNameAddr);
		pluginName = exPluginName();
	}

	exile::core::NativePlugin* plugin = exile::memory::Alloc<exile::core::NativePlugin>(pluginName, SupportedPluginType(), handle);
	
	PFNexPluginInit exPluginInit = reinterpret_cast<PFNexPluginInit>(plugin->GetProcAddress("exPluginInit"));
	if (exPluginInit != NULL)
	{
		exAssertFR(exPluginInit(plugin) != EX_SUCCESS, {
			exile::memory::Free(plugin); 
		}, EX_ERROR, "exPluginInit: failed to initialize plugin %s", entry.c_str());
	}
	
	exAssertFR(manager->AddPlugin(plugin) != EX_SUCCESS, {
		exile::memory::Free(plugin);
	}, EX_ERROR, "failed to add plugin %s in manager!", entry.c_str());

	return EX_SUCCESS;
}
