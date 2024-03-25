
extern "C"
{
#include <exile/forge/conf.h>
#include <exile/forge/boot.h>
#include <exile/core/memory.h>
#include <exile/core/module.h>
#include <exile/core/critical.h>
}
#include <iostream>

int main()
{
#if defined(EXILE_DISABLE_CME_DUMP)
	printf(
		"dump disabled"
	);
#endif

	exSetupCriticalDefaultConfiguration();
	
	exConf conf;
	exMemset(&conf, 0, sizeof(exConf));
	exFilePath path;
	exFilePathInit2(&path, "concept2.conf");
	
	exConfRead(&conf, &path);

	exForgeContext forge;
	exMemset(&forge, 0, sizeof(exForgeContext));
	exForgeBootKernel(&forge, &conf);

	/*
		your application
	*/

	exForgeBootContextFree(&forge);

	exConfFree(&conf);

	exFilePathFree(&path);


	return 0;
}
