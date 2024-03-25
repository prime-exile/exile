#define EXILE_PRIVATE
#include <exile/core/critical.h>
#include <exile/core/module.h>

extern exNativeModule mdl;

EXILE_API_EXPORT void exSetupCriticalConfiguration(PFNexPanic newPanic, PFNexWarning newWarning)
{
	if(mdl.handle != NULL)
	{
		exFreeCriticalConfiguration();
	}

	gExileCriticalInstance.panic = newPanic;
	gExileCriticalInstance.warn = newWarning;
	mdl.moduleType = exNativeModuleType_InBuilt;
}
