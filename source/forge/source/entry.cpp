extern "C"
{
#include <exile/core/API.h>
#include <exile/core/assert.h>
#include <exile/forge/conf.h>
#include <exile/forge/boot.h>

}


extern int32_t exMain();

#if defined(main)
#undef main
#endif


int main(int argc, char* argv)
{
	exSetupCriticalDefaultConfiguration();
	
	exConf conf;
	exMemset(&conf, 0, sizeof(exConf));
	exFilePath path;
	exAssertF(exFilePathInit2(&path, "forge.conf"), {}, "failed to load boot config!");

	exConfRead(&conf, &path);

	exForgeContext forge;
	exMemset(&forge, 0, sizeof(exForgeContext));
	exForgeBootKernel(&forge, &conf);

	int32_t res = exMain();

	exForgeBootContextFree(&forge);

	exConfFree(&conf);

	exFilePathFree(&path);

	return res;
}
