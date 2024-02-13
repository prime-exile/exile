#include <exile/core/memory.hpp>
#include <exile/core/thread/thread.hpp>
#include <exile/core/containers/function.hpp>
#include <exile/core/containers/unordered_map.hpp>
#include <exile/core/plugin.hpp>
#include <exile/core/pluginLoader.hpp>
#include <exile/core/nativePlugin.hpp>
#include <exile/core/fs/File.hpp>
#include <exile/core/fs/DirectoryIterator.hpp>
#include <exile/core/instance.hpp>
#include <exile/core/cme/instance.hpp>
#include <exile/core/assertNew.h>
#include <exile/core/string/f32ToString.h>
#include <exile/core/string/i8ToString.h>
#include <exile/core/hash.hpp>
#include <exile/core/cvar.hpp>

#include <iostream>
#include <exile/core/containers/sstream.hpp>

#include <stdarg.h>
#include <stdio.h>
#include <thread>

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

void testThread(exThread* th)
{
	struct tes2 {
		int w;
		int il;
	} tes;
	tes.w = 0;
	tes.il = 2232;
	exThreadCreate(th, [](void* d)->u32 {
		tes2* data = (tes2*)d;
		printf("hello world %i\n\r", data->il);
		printf("hello world %i\n\r", data->il);
		printf("hello world %i\n\r", data->il);
		printf("hello world %i\n\r", data->il);
		printf("hello world %i\n\r", data->il);
		printf("hello world %i\n\r", data->il);
		printf("hello world %i\n\r", data->il);
		printf("hello world %i\n\r", data->il);
		printf("hello world %i\n\r", data->il);
		printf("hello world %i", data->il);
		printf("hello world %i", data->il);
		printf("hello world %i", data->il);
		exThreadSleep(500);
		return 0;
	}, &tes, 0);
}

int main()
{
	struct ThreadArguments
	{
		u32 il;
		u32 rb;
		u32 ih;
	};

	try
	{
		exSetupCriticalDefaultConfiguration();
		
		u64 hres = exile::hash::fnv1a32("hello world");
		std::cout << "hres =" << hres << std::endl;

		auto& engine = exGEngine;

		exile::core::CVarSystem::SetupDefaultImpl();

		exile::core::CVarSystem::Get()->CreateStringCVar("test.int", "tester", "sd3", "ss2");

		exile::core::CVarDesc* desc = exile::core::CVarSystem::Get()->GetCVar(exile::hash::fnv1a32("test.int"));
		u8 res = engine.GetPluginManager().LoadPlugin("exDefaultULP");

		exile::Thread th;
		ThreadArguments ar;

		exile::Function<u32(ThreadArguments*)> f = [](ThreadArguments* args)->u32 {
			printf("hello world %i %i %i\n\r", args->ih, args->il, args->rb);
			exThreadSleep(100);
			printf("hello world %i %i %i\n\r", args->ih, args->il, args->rb);
			return 0;
		};

		ar.ih = 1;
		ar.il = 2;
		ar.rb = 532;
		th.Run<ThreadArguments>(f, &ar);
		printf("jelolasdasdlasdlas';d");
		
		
		
		
		
		
		
		exThreadSleep(100);

		th.Join();


		//f(&ar);
		//th.Run([]()->u32 {
		//});

		//engine.GetULP().Log(engine.GetULP().GetCoreId(), exile::LogLevel::Info, "hello %s help %s ! miea", "strrep", "me");


		engine.GetPluginManager().UnloadPlugins();
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}


	return 0;
}
