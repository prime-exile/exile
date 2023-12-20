
#include <exile/core/critical.h>
#include <exile/core/module.h>

extern exNativeModule mdl;

EXILE_API_EXPORT void exSetupCriticalConfiguration(PFNexPanic newPanic)
{
	if(mdl.handle != NULL)
	{
		exFreeCriticalConfiguration();
	}

	gExileCriticalInstance.panic = newPanic;
	mdl.moduleType = exNativeModuleType_InBuilt;
}
