#include <exile/core/API.h>
#include <exile/core/nativePlugin.hpp>
#include <exile/core/instance.hpp>
#include <iostream>

exile::core::PluginId g_ThisID = 0;

class EXILE_API_EXPORT TastablePlugin : public exile::core::IPlugin
{
	int h;

public:

	TastablePlugin(const exile::String& name, u8 type, int handle)
		:exile::core::IPlugin(name, type, exVersion{0}), h(handle)
	{

	}


};

class EXILE_API_EXPORT TastableLoader : public exile::core::IPluginLoader
{

public:

	TastableLoader(u8 type)
		:exile::core::IPluginLoader(type)
	{

	}
	TastableLoader()
		:exile::core::IPluginLoader(0)
	{
	}

	exile::String GetPluginTypeTitle() const override
	{
		return "tast";
	}


	u8 operator()(exile::core::PluginManager* manager, const exile::String& entry, const exVersion& version, exile::core::PluginId id) override
	{

		exile::ll::IniParser parser;
		parser.ParseFromFile(entry);
		auto& sec = parser.GetInterpretator().GetSection("TastableLoader");
		const exile::String name = sec.GetValue("name");
		
		TastablePlugin* plugin = exile::memory::Alloc<TastablePlugin>(name, SupportedPluginType(), 1);
		
		manager->AddPlugin(plugin, id);

		exGEngine.GetPluginManager().GetDepencyManager().AddDepency(id, g_ThisID);

		return EX_SUCCESS;
	}

	void Unload(exile::core::IPlugin* plugin, exile::core::PluginId id) override
	{
		exGEngine.GetPluginManager().GetDepencyManager().RemoveDepency(id, g_ThisID);

		exile::memory::Free(plugin);

	}
};

TastableLoader loader;

extern "C"
{
	EXILE_API_EXPORT const char* exPluginName()
	{
		return "EX_TEST_PLUGIN!";
	}

	EXILE_API_EXPORT u8 exPluginInit(exile::core::NativePlugin* plugin, exile::core::PluginId id)
	{
		g_ThisID = id;
		exGEngine.GetPluginManager().AddPluginLoader(&loader);
		//exile::core::Engine::Get().GetULP().RegisterHandler();
		return EX_SUCCESS;
	}

	
	EXILE_API_EXPORT void exPluginTermiate()
	{
		std::cout << "hiii" << std::endl;

	}


}


