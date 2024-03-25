#ifndef _EXILE_CORE_INSTANCE_H_
#define _EXILE_CORE_INSTANCE_H_

#define exPanicF(message, ...)(gExileCriticalInstance.panic(message, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__))
#define exPanic(message)(gExileCriticalInstance.panic(message, __FILE__, __LINE__, __FUNCTION__))

#define exWarnF(message, ...)(gExileCriticalInstance.warn(message, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__))
#define exWarn(message)(gExileCriticalInstance.warn(message, __FILE__, __LINE__, __FUNCTION__))


#include <exile/core/API.h>
#include <exile/core/module.h>

typedef u8(*PFNexPanic)(const char* message, const char* filename, const u64 line, const char* function, ...);
typedef u8(*PFNexWarning)(const char* message, const char* filename, const u64 line, const char* function, ...);

typedef struct
{
	PFNexPanic panic;
	PFNexWarning warn;
}exCriticalInstance;

EX_API extern exCriticalInstance gExileCriticalInstance;

/// <summary>
/// Load panic handler from native module using config
/// </summary>
/// <param name="file">path to the configuration file</param>
/// <returns> EX_SUCCESS - on success </returns>
/// <returns> EX_ERROR - on failed </returns>
EX_API u8 exLoadCriticalConfiguration(const char* file);

/// <summary>
/// Setup panic handler manually
/// </summary>
/// <param name="newPanic">function pointer to new panic handler</param>
/// <param name="newWarning">function pointer to new warning handler</param>
EX_API void exSetupCriticalConfiguration(PFNexPanic newPanic, PFNexWarning newWarning);

/// <summary>
/// Load panic handler from native module
/// </summary>
/// <param name="path">path to the native module</param>
/// <param name="panicName">name of panic function handler </param>
/// <param name="warningName">name of warning function handler </param>
/// <returns> EX_SUCCESS - on success </returns>
/// <returns> EX_ERROR - on failed </returns>
EX_API u8 exSetupCriticalConfigurationFromModule(const char* path, const char* panicName, const char* warningName);

/// <summary>
/// Unload native module if it loaded
/// </summary>
EX_API void exFreeCriticalConfiguration();

/// <summary>
/// Setup inbuilt panic handler
/// </summary>
EX_API void exSetupCriticalDefaultConfiguration();
#endif
