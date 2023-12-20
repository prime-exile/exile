#ifndef _EXILE_CORE_NATIVE_PLUGIN_HPP_
#define _EXILE_CORE_NATIVE_PLUGIN_HPP_

#include <exile/core/API.h>
#include <exile/core/pluginLoader.hpp>
#include <exile/core/plugin.hpp>
#include <exile/core/pluginManager.hpp>

#if defined (EXILE_WIN)
#include <Windows.h>
#elif defined(EXILE_UNIX)
#include <dlfcn.h>
#endif

namespace exile
{
	namespace core
	{

#if defined(EXILE_WIN)
		typedef HINSTANCE RawPluginHandle;
#elif defined(EXILE_UNIX)
		typedef void* RawPluginHandle;
#endif

		class EX_API NativePluginLoader : public exile::core::IPluginLoader
		{

		public:

			NativePluginLoader(u8 type);
			NativePluginLoader();

			u8 operator()(exile::core::PluginManager* manager, const exile::String& entry);
			u8 operator()(exile::core::PluginManager* manager, const exile::String& entry, exile::core::PluginId id) override;

			exile::String GetPluginTypeTitle() const override;

			void Unload(exile::core::IPlugin* plugin);
			void Unload(exile::core::IPlugin* plugin, PluginId id) override;
			u8 Load(exile::core::PluginManager* manager, const exile::String& directory);
			u8 Load(exile::core::PluginManager* manager, const exile::String& directory, exile::core::PluginId id);

		};


		class EX_API NativePlugin : public::exile::core::IPlugin
		{
			RawPluginHandle handle;
		public:

			NativePlugin();

			NativePlugin(RawPluginHandle handle);
			NativePlugin(u8 type, RawPluginHandle handle);
			NativePlugin(const exile::String& name, u8 type, RawPluginHandle handle);
			NativePlugin(const exile::String& name, RawPluginHandle handle);

			void* GetProcAddress(const char* proc);
			
			void Free();

			RawPluginHandle GetRawHandle();

			~NativePlugin();

		};
	}
}

#endif