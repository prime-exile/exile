#include "shared.h"


EXILE_API_EXPORT u8 exSetupCriticalConfigurationFromModule(const char* path, const char* function)
{
	if (mdl.handle != NULL)
	{
		exFreeCriticalConfiguration();
		exSetupCriticalDefaultConfiguration();
	}

	exAssertFR(!exNativeModuleLoad(&mdl, path), {}, EX_ERROR, "failed to load module %s", path);

	void* address = exNativeModuleGetAddress(&mdl, "exCriticalInit");

	if (address != NULL)
	{
		PFNexCriticalInit init = (PFNexCriticalInit)address;
		init();
	}

	void* panicHandlder = exNativeModuleGetAddress(&mdl, function);
	exAssertFR(panicHandlder == NULL, {
		exNativeModuleFree(&mdl);
	}, EX_ERROR, "failed to get function %s from module %s", function, path);

	gExileCriticalInstance.panic = (PFNexPanic)panicHandlder;

	return EX_SUCCESS;
}

