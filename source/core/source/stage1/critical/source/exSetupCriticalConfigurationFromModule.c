#include "exile/core/critical.h"
#include "shared.h"


EXILE_API_EXPORT u8 exSetupCriticalConfigurationFromModule(const char* path, const char* panicName, const char* warningName)
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

	void* procAddress = exNativeModuleGetAddress(&mdl, panicName);
	exAssertFR(procAddress == NULL, {
		exNativeModuleFree(&mdl);
	}, EX_ERROR, "failed to get function %s from module %s", panicName, path);

	gExileCriticalInstance.panic = (PFNexPanic)procAddress;

	procAddress = exNativeModuleGetAddress(&mdl, warningName);
	exAssertFR(procAddress == NULL, {
		exNativeModuleFree(&mdl);
		exSetupCriticalDefaultConfiguration();
	}, EX_ERROR, "failed to get function %s from module %s", warningName, path);

	gExileCriticalInstance.warn = (PFNexWarning)procAddress;

	return EX_SUCCESS;
}

