#include <exile/forge/boot.h>
#include <exile/forge/conf.h>
#include <exile/core/assert.h>

#include <exile/core/module.h>

typedef u8(*PFNexForgeInit)();

#define EX_FORGE_EXTENSIONS_INIT "exForgeExtensionInit"
#define EX_FORGE_EXTENSIONS_BOOT_MENU "exForgeExtensionBootMenu"
#define EX_FORGE_CONFIGURATION_SECTION_NAME "forge"

u8 exForgeBootLoadExtension(exForgeContext* ctx, const exFilePath* path)
{
	ctx->forgeExtension = (exNativeModule*)exMalloc(sizeof(exNativeModule));
	exAssertR(!ctx->forgeExtension, {
		}, EX_ERROR, "failed to allocated memory for exNativeModule");
	exMemset(ctx->forgeExtension, 0, sizeof(exNativeModule));

	exAssertFR(!exNativeModuleLoad(ctx->forgeExtension, exFilePathGetCStr(path)), {}, EX_ERROR, "failed to load forge extension %s", exFilePathGetCStr(path));

	void* address = exNativeModuleGetAddress(ctx->forgeExtension, EX_FORGE_EXTENSIONS_INIT);
	if (address)
	{
		PFNexForgeInit exForgeExtensionInit = (PFNexForgeInit)address;
		if (!exForgeExtensionInit())
		{
			exWarnF("failed to initialize forge extension: %s", exFilePathGetCStr(path));
			exNativeModuleFree(ctx->forgeExtension);
			return EX_ERROR;
		}
		//(, {}, EX_ERROR, "failed to initialize forge extension")
	}

	address = exNativeModuleGetAddress(ctx->forgeExtension, EX_FORGE_EXTENSIONS_BOOT_MENU);
	if (address)
	{
		ctx->exForgeBootMenu = (PFNexForgeBootMenu)address;
	}

	return EX_SUCCESS;
}

void exForgeBootFreeExtension(exForgeContext* ctx)
{
	typedef void(*PFNexForgeExtensionShutdown)();

	if (!ctx->exForgeBootMenu) return;

	ctx->exForgeBootMenu = NULL;

	PFNexForgeExtensionShutdown exForgeExtensionShutdown = (PFNexForgeExtensionShutdown)exNativeModuleGetAddress(ctx->forgeExtension, "exForgeExtensionShutdown");
	if (!exForgeExtensionShutdown) exForgeExtensionShutdown();

	exNativeModuleFree(ctx->forgeExtension);
}

u8 exForgeBootLoadKernel(const exConfSection* config,  exNativeModule* handle)
{
	exAssertFR(!exNativeModuleLoad(handle, exFilePathGetCStr(config->kernelModulePath)), {}, EX_ERROR, "failed to load forge extension %s", exFilePathGetCStr(config->kernelModulePath));

	void* address = exNativeModuleGetAddress(handle, EX_FORGE_EXTENSIONS_INIT);
	if (address)
	{
		PFNexForgeInit exForgeExtensionInit = (PFNexForgeInit)address;
		if (!exForgeExtensionInit())
		{
			exWarnF("failed to initialize kernel: %s", exFilePathGetCStr(config->kernelModulePath));
			return EX_ERROR;
		}
		//(, {}, EX_ERROR, "failed to initialize forge extension")
	}

}

const exConfSection* exForgeDefaultBootMenu(const exConf* conf)
{
	return NULL;
}

u8 exForgeBootContextFree(exForgeContext* ctx)
{
	ctx->exForgeBootMenu = NULL;
	if (ctx->defaultBootConfiguration)
	{
		exFree(ctx->defaultBootConfiguration);
		ctx->defaultBootConfiguration = NULL;
	}
	if (ctx->kernel)
	{
		exForgeBootKernelShutdown(ctx->kernel);
		exFree(ctx->kernel);
		ctx->kernel = NULL;
	}
	if (ctx->forgeExtension)
	{
		exForgeBootFreeExtension(ctx);
		exFree(ctx->forgeExtension);
		ctx->forgeExtension = NULL;
	}


	return EX_SUCCESS;
}

u8 exForgeBootKernel(exForgeContext* ctx, const exConf* conf)
{
	exNativeModule extensionModule;

	ctx->exForgeBootMenu = exForgeDefaultBootMenu;

	const exConfSection* it = conf->sections;
	const exConfSection* end = it + conf->sectionsCount + 1;

	const char* defaultBootConfiguration = "default entry";

	for (; it != end; it += 1)
	{
		if (strcmp(it->name, EX_FORGE_CONFIGURATION_SECTION_NAME) == 0)
		{
			if (it->exForgeExtensionModulePath)
			{
				if (!exForgeBootLoadExtension(ctx, it->exForgeExtensionModulePath))
				{
					break;
				}
			}
			
			if (it->exForgeDefaultBootConfiguration)
			{
				defaultBootConfiguration = it->exForgeDefaultBootConfiguration;
			}
			break;
		}
	}

	const exConfSection* selectedConfiguration = ctx->exForgeBootMenu(conf);

	if (!selectedConfiguration)
	{
		if (!exForgeDefaultBootMenu(conf))
		{
			selectedConfiguration = NULL;

			it = conf->sections;
			u8 bootConfigurationIsFind = EX_FALSE;
			for (; it != end; it += 1)
			{
				if (strcmp(it->name, defaultBootConfiguration) == 0)
				{
					if (strcmp(it->platform, EXILE_PLATFORM_STRING) == 0)
					{
						bootConfigurationIsFind = EX_TRUE;
						selectedConfiguration = it;
						break;
					}
				}
			}

			if (!bootConfigurationIsFind)
			{
				exWarnF("failed to find default boot configuration with name: \'%s\'", defaultBootConfiguration);

				for (; it != end; it += 1)
				{
					if (strcmp(it->name, defaultBootConfiguration) == 0)
					{
						if (strcmp(it->platform, EXILE_PLATFORM_STRING))
						{
							bootConfigurationIsFind = EX_TRUE;
							selectedConfiguration = it;
							break;
						}
					}
				}
			}

			if (!bootConfigurationIsFind) return EX_ERROR;
		}
	}

	ctx->kernel = (exNativeModule*)exMalloc(sizeof(exNativeModule));
	exAssertR(!ctx->kernel, {
			exForgeBootContextFree(ctx);
	}, EX_ERROR, "failed to allocate memory for exNativeModule");


	exForgeBootKernelManually(ctx->kernel, selectedConfiguration);
	return EX_SUCCESS;
}

u8 exForgeBootKernelManually(exNativeModule* kernelModule, const exConfSection* conf)
{
	typedef u8(*PFNexKernelEntry)(const char* args);

	exAssertFR(!exNativeModuleLoad(kernelModule, exFilePathGetCStr(conf->kernelModulePath)), {}, EX_ERROR, "failed to load kernel module: %s", exFilePathGetCStr(conf->kernelModulePath));

	PFNexKernelEntry exKernelEntry = (PFNexKernelEntry)exNativeModuleGetAddress(kernelModule, "exKernelEntry");
	exAssertFR(!exKernelEntry, {
		exNativeModuleFree(kernelModule);
	}, EX_ERROR, "failed to get kernel entry address from module %s", exFilePathGetCStr(conf->kernelModulePath));

	exAssertFR(!exKernelEntry(conf->kernelParameters), {
		exNativeModuleFree(kernelModule);
	}, EX_ERROR, "failed to initialize kernel from module %s", exFilePathGetCStr(conf->kernelModulePath));

	return EX_SUCCESS;
}

void exForgeBootKernelShutdown(exNativeModule* kernelModule)
{
	typedef void(*PFNexKernelShutdown)();
	
	PFNexKernelShutdown exKernelShutdown = (PFNexKernelShutdown)exNativeModuleGetAddress(kernelModule, "exKernelShutdown");
	if (exKernelShutdown) 
		exKernelShutdown();

	exNativeModuleFree(kernelModule);
}
