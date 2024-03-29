#ifndef _EXILE_CORE_NATIVE_PLUGIN_HPP_
#define _EXILE_CORE_NATIVE_PLUGIN_HPP_

#include <exile/core/API.h>
#include <exile/core/pluginLoader.hpp>
#include <exile/core/plugin.hpp>
#include <exile/core/pluginManager.hpp>

extern "C"
{
#include <exile/core/version.h>
}

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

			NativePluginLoader(const NativePluginLoader&) = delete;

			u8 operator()(exile::core::PluginManager* manager, const exile::String& entry);
			u8 operator()(exile::core::PluginManager* manager, const exile::String& entry, const exVersion& version, exile::core::PluginId id) override;

			exile::String GetPluginTypeTitle() const override;

			void Unload(exile::core::IPlugin* plugin);
			void Unload(exile::core::IPlugin* plugin, PluginId id) override;
			u8 Load(exile::core::PluginManager* manager, const exile::String& directory);
			u8 Load(exile::core::PluginManager* manager, const exile::String& directory,  const exVersion& version, exile::core::PluginId id);

			exile::core::NativePluginLoader& operator=(exile::core::NativePluginLoader& other) = delete;
			exile::core::NativePluginLoader& operator==(exile::core::NativePluginLoader& other) = delete;

		};


		class EX_API NativePlugin : public::exile::core::IPlugin
		{
		private:

			RawPluginHandle handle;

		public:

			NativePlugin(const NativePlugin&) = delete;
			NativePlugin();

			NativePlugin(RawPluginHandle handle);
			NativePlugin(u8 type, RawPluginHandle handle);
			NativePlugin(const exile::String& name, u8 type, RawPluginHandle handle, const exVersion& version);
			NativePlugin(const exile::String& name, u8 type, RawPluginHandle handle);
			NativePlugin(const exile::String& name, RawPluginHandle handle);

			void* GetProcAddress(const char* proc);
			
			void Free();

			RawPluginHandle GetRawHandle();

			~NativePlugin();

			exile::core::NativePlugin& operator=(exile::core::NativePlugin& other) = delete;
			exile::core::NativePlugin& operator==(exile::core::NativePlugin& other) = delete;

		};
	}
}

#endif