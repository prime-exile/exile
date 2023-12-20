#define EXILE_PRIVATE
#include <exile/core/critical.h>
#include <exile/core/module.h>

extern exNativeModule mdl;

EXILE_API_EXPORT
void exFreeCriticalConfiguration()
{
	if (mdl.moduleType == exNativeModuleType_InBuilt || mdl.handle == NULL) return;
	exNativeModuleFree(&mdl);
	exSetupCriticalDefaultConfiguration();
}