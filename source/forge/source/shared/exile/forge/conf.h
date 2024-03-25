#ifndef _EXILE_FORGE_CONF_HPP_
#define _EXILE_FORGE_CONF_HPP_

#define exForgeExtensionModulePath kernelModulePath
#define exForgeDefaultBootConfiguration bootCriticalModulePanicFunctionName

#include <exile/core/API.h>
#include <exile/core/path.h>

typedef struct
{
	char name[512];
	u8 isOptionArray;
	void* value;
} exConfOption;

typedef struct {
	char name[512];
	char platform[512];
	exFilePath* kernelModulePath;
	exFilePath* bootCriticalConfigPath;
	exFilePath* bootCriticalModulePath;
	char* bootCriticalModulePanicFunctionName;
	char* bootCriticalModuleWarnFunctionName;
	char* kernelParameters;
} exConfSection;

typedef struct
{
	exConfSection* sections;
	u16 sectionsCount;
} exConf;


#define EX_CONF_SECTION_FREE(section)\
	{\
	if (section->bootCriticalConfigPath)\
		exFree(section->bootCriticalConfigPath);\
	if (section->bootCriticalModulePanicFunctionName)\
		exFree(section->bootCriticalModulePanicFunctionName);\
	if (section->bootCriticalModuleWarnFunctionName)\
		exFree(section->bootCriticalModuleWarnFunctionName);\
	if (section->bootCriticalModulePath)\
		exFree(section->bootCriticalModulePath);\
	if (section->kernelModulePath)\
		exFree(section->kernelModulePath);\
	}

u8 exConfRegisterOption(exConf* conf, exConfOption* option);
u8 exConfRead(exConf* conf, const exFilePath* path);

exConfSection* exConfAllocSection(exConf* conf);
u8 exConfAddSection(exConf* conf, const exConfSection* section);

void exConfSectionFree(exConfSection* section);
void exConfFree(exConf* conf);

#endif
