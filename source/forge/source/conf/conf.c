#include "exile/forge/conf.h"
#include "exile/forge/assert.h"

#include <stdio.h>
#include <exile/core/memory.h>
#include <exile/core/panic.h>
#include <exile/core/psstring.h>
#include <exile/core/assert.h>

u8 exConfRegisterOption(exConf* conf, exConfOption* option)
{
	//const u64 exConfOptionSize = sizeof(exConfOptionSize);
	//if (!conf->root)
	//{
	//	conf->root = exMalloc(exConfOptionSize);
	//	if (conf->root == NULL) 
	//	{
	//		exPanicF("failed to allocate memory for conf option: %s", option->name);
	//		return EX_ERROR;
	//	}
	//	exMemcpy(conf->root, option, exConfOptionSize);
	//}
	//else 
	//{
	//	exRealloc(conf->root, conf->optionsCount + 1);
	//	exMemcpy(conf->root + conf->optionsCount, option, exConfOptionSize);
	//}
	//return EX_SUCCESS;
}

#define EX_BOOT_CONFIGURATION_FIELD_DEFINE(nameStr, inFid, srcStr)\
	if (strcmp(srcStr.buffer, nameStr) == 0)\
	{\
		fid = inFid;\
		readValue = EX_TRUE;\
		exString1024xClear(&srcStr);\
		continue;\
	}

typedef enum
{
	exBootConfigurationFieldId_None,
	/*
		main configuration parameters
	*/
	exBootConfigurationFieldId_Platform,
	exBootConfigurationFieldId_Kernel,
	exBootConfigurationFieldId_KernelParameters,

	/*
		boot panic configuration parameters
	*/
	exBootConfigurationFieldId_CriticalConfig,
	exBootConfigurationFieldId_CriticalModulePath,
	exBootConfigurationFieldId_CriticalModulePanicFunctionName,
	exBootConfigurationFieldId_CriticalModuleWarnFunctionName,

	/*
		forge configuration parameters
	*/
	exBootConfigurationFieldId_ForgeExtensionsModulePath,
	exBootConfigurationFieldId_ForgeDefaultBootConfiguration,
} exBootConfigurationFieldId;

static __forceinline void exConfApplyFieldValue(exConfSection* section, exBootConfigurationFieldId fid, exString1024x* value)
{
	switch (fid)
	{
	case exBootConfigurationFieldId_Platform:
	{
		exMemcpy(section->platform, value->buffer, value->occupied);
		break;
	}
	case exBootConfigurationFieldId_Kernel:
	{
		if(!section->kernelModulePath)
			section->kernelModulePath = exMalloc(sizeof(exFilePath));
		
		exFilePathInit2(section->kernelModulePath, value->buffer);
		break;
	}
	case exBootConfigurationFieldId_CriticalConfig:
	{
		if (!section->bootCriticalConfigPath)
			section->bootCriticalConfigPath = exMalloc(sizeof(exFilePath));

		exFilePathInit2(section->bootCriticalConfigPath, value->buffer);
		break;
	}
	case exBootConfigurationFieldId_CriticalModulePath:
	{
		if (!section->bootCriticalModulePath)
			section->bootCriticalModulePath = exMalloc(sizeof(exFilePath));

		exFilePathInit2(section->bootCriticalModulePath, value->buffer);
		break;
	}
	case exBootConfigurationFieldId_CriticalModulePanicFunctionName:
	{
		if (!section->bootCriticalModulePanicFunctionName)
			section->bootCriticalModulePanicFunctionName = exMalloc(value->occupied + 1);

		exMemcpy(section->bootCriticalModulePanicFunctionName, value->buffer, value->occupied + 1);
		break;
	}
	case exBootConfigurationFieldId_CriticalModuleWarnFunctionName:
	{
		if (!section->bootCriticalModuleWarnFunctionName)
			section->bootCriticalModuleWarnFunctionName = exMalloc(value->occupied + 1);

		exMemcpy(section->bootCriticalModuleWarnFunctionName, value->buffer, value->occupied + 1);
		break;
	}
	case exBootConfigurationFieldId_ForgeExtensionsModulePath:
	{
		if(!section->exForgeExtensionModulePath)
			section->exForgeExtensionModulePath = exMalloc(sizeof(exFilePath));

		exFilePathInit2(section->exForgeExtensionModulePath, value->buffer);
		break;
	}
	case exBootConfigurationFieldId_ForgeDefaultBootConfiguration:
	{
		if (!section->exForgeDefaultBootConfiguration)
			section->exForgeDefaultBootConfiguration = exMalloc(value->occupied + 1);

		exMemcpy(section->exForgeDefaultBootConfiguration, value->buffer, value->occupied + 1);
		break;
	}
	case exBootConfigurationFieldId_KernelParameters:
	{
		if (!section->exForgeDefaultBootConfiguration)
			section->exForgeDefaultBootConfiguration = exMalloc(value->occupied + 1);

		exMemcpy(section->exForgeDefaultBootConfiguration, value->buffer, value->occupied + 1);
		break;
	}
	default:
		return;
		break;
	}
}

u8 exConfRead(exConf* conf, const exFilePath* path)
{
	u8 firstSection = EX_TRUE;

	u8 readString = EX_FALSE;
	u8 readConfiguration = EX_FALSE;
	
	u8 readValue = EX_FALSE;
	u8 readSectionName = EX_FALSE;
	u8 readValueStarted = EX_FALSE;
	
	exString1024x readerString;

	exBootConfigurationFieldId fid = exBootConfigurationFieldId_None;
	FILE* file = fopen(exFilePathGetCStr(path), "r");
	if (!file) return EX_ERROR;

	exString1024xInit(&readerString);
	exConfSection currentSection;

	for (;;)
	{
		int rc = getc(file);
		if (rc == EOF)
		{
			break;
		}
		char c = (char)rc;
		
		exAssertFR(readerString.occupied >= 1024,
			{
				fclose(file);
			},
			EX_ERROR, "failed to parse readerString.occupied >= 1024 in file %s", exFilePathGetCStr(file));

		if (c == '[')
		{
			readSectionName = EX_TRUE;
			continue;
		}

		if (readValue)
		{
			if (readValueStarted)
			{
				if (c == '\"')
				{
					readValue = EX_FALSE;
					readValueStarted = EX_FALSE;

					exConfApplyFieldValue(&currentSection, fid, & readerString);
					exString1024xClear(&readerString);
					continue;
				}
				exString1024xPushChar(&readerString, (char)c);
			}
			else if (c == '\"')
			{
				readValueStarted = EX_TRUE;
			}

			continue;
		}

		if (c == '=')
		{
			EX_BOOT_CONFIGURATION_FIELD_DEFINE("exPlatform", exBootConfigurationFieldId_Platform, readerString);
			EX_BOOT_CONFIGURATION_FIELD_DEFINE("exCriticalBootPanicConfig", exBootConfigurationFieldId_CriticalConfig, readerString);
			EX_BOOT_CONFIGURATION_FIELD_DEFINE("exCriticalbootCriticalModulePath", exBootConfigurationFieldId_CriticalModulePath, readerString);
			EX_BOOT_CONFIGURATION_FIELD_DEFINE("exCriticalBootPanicModuleFunctionName", exBootConfigurationFieldId_CriticalModulePanicFunctionName, readerString);
			EX_BOOT_CONFIGURATION_FIELD_DEFINE("exCriticalBootWarnModuleFunctionName", exBootConfigurationFieldId_CriticalModulePanicFunctionName, readerString);
			EX_BOOT_CONFIGURATION_FIELD_DEFINE("exKernelModulePath", exBootConfigurationFieldId_Kernel, readerString);
			EX_BOOT_CONFIGURATION_FIELD_DEFINE("exKernelParameters", exBootConfigurationFieldId_KernelParameters, readerString);

			EX_BOOT_CONFIGURATION_FIELD_DEFINE("exForgeExtensionModulePath", exBootConfigurationFieldId_ForgeExtensionsModulePath, readerString);
			EX_BOOT_CONFIGURATION_FIELD_DEFINE("exForgeDefaultBootConfiguration", exBootConfigurationFieldId_ForgeDefaultBootConfiguration, readerString);
		}
		else if (!readSectionName && (c == ' ' || c == '\t' || c == '\n' || c == '\r'))
		{
			continue;
		}

		if (readSectionName)
		{
			if (c == ']')
			{
				readSectionName = EX_FALSE;
				
				//
				//if (currentSection)
				//{
				//	exConfAddSection(conf, currentSection);
				//	
				//}
				if (!firstSection)
				{
					exConfAddSection(conf, &currentSection);
				}
				else firstSection = EX_FALSE;

				exMemset(&currentSection, 0, sizeof(exConfSection));
				exMemcpy(currentSection.name, readerString.buffer, readerString.occupied);
				currentSection.name[readerString.occupied] = '\0';


				exString1024xClear(&readerString);
				continue;
			}
			//else if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
			//{
			//	continue;
			//}
		}

		//if (readSectionName || readValue)
		exString1024xPushChar(&readerString, (char)rc);
	}

	//if (!currentSection)
	//{
	//	exConfAddSection(conf, currentSection);
	//}

	exConfAddSection(conf, &currentSection);

	fclose(file);

	return EX_SUCCESS;
}

exConfSection* exConfAllocSection(exConf* conf)
{
	exConfSection* section = exMalloc(sizeof(exConfSection));
	exMemset(section, 0, sizeof(exConfSection));
	return section;
}

u8 exConfAddSection(exConf* conf, const exConfSection* section)
{
	if (!conf->sections)
	{
		//TO DO CHECK ON NULL
		conf->sections = exMalloc(sizeof(exConfSection));
		exAssertFR(!conf->sections, {}, EX_ERROR, "failed to allocate %d bytes for section", sizeof(exConfSection));
		
		exMemcpy(conf->sections, section, sizeof(exConfSection));
		conf->sectionsCount = 1;
	}
	else
	{
		//TO DO CHECK ON NULL
		conf->sections = exRealloc(conf->sections, (conf->sectionsCount + 1) * sizeof(exConfSection));
		exAssertFR(!conf->sections, {}, EX_ERROR, "failed to allocate %d bytes for sections", (conf->sectionsCount + 1) * sizeof(exConfSection));
		
		exConfSection* destSection = &conf->sections[conf->sectionsCount];
		exMemcpy(destSection, section, sizeof(exConfSection));
		conf->sectionsCount += 1;
	}

	return EX_SUCCESS;
}

#define FREE_FIELD(section,field)\
	if(section->field){\
		exFree(section->field);\
		section->field = NULL;\
	}\

#define FREE_FIELD_PATH(section,field)\
	if(section->field){\
		exFilePathFree(section->field);\
		exFree(section->field);\
		section->field = NULL;\
	}\

void exConfSectionFree(exConfSection* section)
{
	FREE_FIELD(section, bootCriticalModulePanicFunctionName);
	FREE_FIELD(section, bootCriticalModuleWarnFunctionName);
	FREE_FIELD(section, kernelParameters);
	FREE_FIELD(section, exForgeDefaultBootConfiguration);

	FREE_FIELD_PATH(section, bootCriticalConfigPath);
	FREE_FIELD_PATH(section, bootCriticalModulePath);
	FREE_FIELD_PATH(section, kernelModulePath);
	FREE_FIELD_PATH(section, exForgeExtensionModulePath);
}

void exConfFree(exConf* conf)
{
	exConfSection* end = conf->sections + conf->sectionsCount;
		
	for (exConfSection* sec = conf->sections; sec != end; sec += 1)
	{
		exConfSectionFree(sec);
	}

	exFree(conf->sections);
}
