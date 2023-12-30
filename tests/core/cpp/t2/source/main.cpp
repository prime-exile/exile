

#include <exile/core/memory.hpp>
#include <exile/core/containers/function.hpp>
#include <exile/core/containers/unordered_map.hpp>
#include <exile/core/plugin.hpp>
#include <exile/core/pluginLoader.hpp>
#include <exile/core/nativePlugin.hpp>
#include <exile/core/fs/File.hpp>
#include <exile/core/fs/DirectoryIterator.hpp>
#include <exile/core/instance.hpp>
#include <exile/core/cme/instance.hpp>

#include <iostream>
#include <exile/core/containers/sstream.hpp>

#include <stdarg.h>
#include <stdio.h>

static __forceinline void SplitString(const exile::String& str, exile::Vector<exile::String>& splitted, char s)
{
	exile::Stringstream ss(str);
	exile::String tmp;
	for (char i; ss >> i; )
	{
		tmp += i;
		if (ss.peek() == s)
		{
			ss.ignore();
			splitted.push_back(tmp);
			tmp.clear();
		}
	}

	if (tmp.empty())
	{
		splitted.push_back(tmp);
	}
}

void PrintDiretory(const exile::String& path)
{
	exile::core::DirectoryIterator it(path);

	while (!it.IsFinished()) {
		exile::String currentName = it.GetCurrentName();
		if (currentName != "." && currentName != "..") {
			if (it.IsDirectory()) {
				std::cout << "Directory: " << currentName << std::endl;
				PrintDiretory((path + "/") + currentName);
			}
			else {
				std::cout << "File: " << currentName << std::endl;
			}
		}
		++it;
	}
}

int main()
{
	try
	{

		exSetupCriticalDefaultConfiguration();

		auto& engine = exile::core::Engine::Get();

		u8 res = engine.GetPluginManager().LoadPlugin("exDefaultULP");

		engine.GoToCMEPanic("hello");

		//engine.GetULP().Log(engine.GetULP().GetCoreId(), exile::LogLevel::Info, "hello %s help %s ! miea", "strrep", "me");


		engine.GetPluginManager().UnloadPlugins();
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}


	return 0;
}
