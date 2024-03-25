#ifndef _EXILE_FORGE_BOOT_HPP_
#define _EXILE_FORGE_BOOT_HPP_

#include <exile/core/API.h>
#include <exile/forge/conf.h>
#include <exile/core/module.h>

#if defined(EXILE_FORGE_MAIN)
#define main exMain
#endif 

typedef const exConfSection* (*PFNexForgeBootMenu)(const exConf* conf);

typedef struct 
{
	PFNexForgeBootMenu exForgeBootMenu;
	char* defaultBootConfiguration;
	exNativeModule* forgeExtension;
	exNativeModule* kernel;
}exForgeContext;

u8 exForgeBootLoadExtension(exForgeContext* ctx, const exFilePath* path);


u8 exForgeBootContextFree(exForgeContext* ctx);


u8 exForgeBootKernel(exForgeContext* ctx,const exConf* conf);
u8 exForgeBootKernelManually(exNativeModule* kernelModule, const exConfSection* conf);
void exForgeBootKernelShutdown(exNativeModule* kernelModule);

#endif
