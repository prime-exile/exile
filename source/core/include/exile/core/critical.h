#ifndef _EXILE_CORE_INSTANCE_H_
#define _EXILE_CORE_INSTANCE_H_

#define exPanicF(message, ...)(gExileCriticalInstance.panic(message, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__))
#define exPanic(message)(gExileCriticalInstance.panic(message, __FILE__, __LINE__, __FUNCTION__))

#include <exile/core/API.h>
#include <exile/core/module.h>

typedef u8(*PFNexPanic)(const char* message, const char* filename, const u64 line, const char* function, ...);

typedef struct
{
	PFNexPanic panic;
}exCriticalInstance;

EX_API extern exCriticalInstance gExileCriticalInstance;

EX_API u8 exLoadCriticalConfiguration(const char* file);

EX_API void exSetupCriticalConfiguration(PFNexPanic newPanic);
EX_API u8 exSetupCriticalConfigurationFromModule(const char* path, const char* function);

EX_API void exFreeCriticalConfiguration();
EX_API void exSetupCriticalDefaultConfiguration();
#endif
