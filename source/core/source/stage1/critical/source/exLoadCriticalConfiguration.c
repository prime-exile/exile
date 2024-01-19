#define EXILE_PRIVATE
#define EXILE_PRIVATE_SELF
#include <exile/core/critical.h>
#include <exile/core/psstring.h>
#include <exile/core/module.h>
#include <exile/core/assert.h>

#include <stdio.h>

typedef struct
{
	char filename[512];
	char function[512];
} exCriticalConfiguration;

exNativeModule mdl;

exCriticalInstance gExileCriticalInstance = {
	.panic = NULL
};

#define LRETURN_IF_FAILED(pred, func)\
	if(pred == EX_ERROR)\
	{\
		func\
		return EX_ERROR;\
	}

#define EX_CRITICAL_CONFIGURATION_FIELD_DEFINE(nameStr, inFid, srcStr)\
	if (strcmp(srcStr.buffer, nameStr) == 0)\
	{\
		fid = inFid;\
		readValue = EX_TRUE;\
		exString512xClear(&srcStr);\
		continue;\
	}

typedef enum 
{
	exCriticalConfigurationFieldId_None,
	exCriticalConfigurationFieldId_File,
	exCriticalConfigurationFieldId_Function
} exCriticalConfigurationFieldId;

static __forceinline void exLoadCriticalApplyFieldValue(exCriticalConfiguration* conf, exCriticalConfigurationFieldId fid, exString512x* value)
{
	switch (fid)
	{
	case exCriticalConfigurationFieldId_File:
		exMemcpy(conf->filename, value->buffer, value->occupied);
		break;
	case exCriticalConfigurationFieldId_Function:
		exMemcpy(conf->function, value->buffer, value->occupied);
		break;
	default:
		return;
		break;
	}
}

EXILE_API_EXPORT
u8 exLoadCriticalConfiguration(const char* file)
{
	if (gExileCriticalInstance.panic == NULL)
	{
		exSetupCriticalDefaultConfiguration();
	}

	FILE* f = fopen(file, "r");

	exAssertFR(f == NULL, {
	}, EX_ERROR, "failed to open file configuration file %s!", file);
	
	exCriticalConfiguration conf;
	exMemset(&conf, 0, sizeof(exCriticalConfiguration));

	exString512x readerString;

	exString512xInit(&readerString);

	u8 readConfiguration = EX_FALSE;
	exCriticalConfigurationFieldId fid = exCriticalConfigurationFieldId_None;

	u8 readValue = EX_FALSE;
	u8 readPlatformSection = EX_FALSE;
	u8 readValueStarted = EX_FALSE;
	while (EX_TRUE)
	{
		int rc = getc(f);
		if (rc == EOF)
		{
			break;
		}
		char c = (char)rc;

		exAssertFR(readerString.occupied >= 512, 
			{
				fclose(f); 
			}, 
		EX_ERROR, "failed to parse readerString.occupied >= 512 in file %s", file);

		if (c == '[')
		{
			readPlatformSection = EX_TRUE;
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
					exLoadCriticalApplyFieldValue(&conf, fid, &readerString);
					exString512xClear(&readerString);
					continue;
				}
				exString512xPushChar(&readerString, (char)c);
			}
			else if (c == '\"')
			{
				readValueStarted = EX_TRUE;
			}

			continue;
		}

		if (readConfiguration)
		{
			if (c == '=')
			{
				EX_CRITICAL_CONFIGURATION_FIELD_DEFINE("file", exCriticalConfigurationFieldId_File, readerString);
				EX_CRITICAL_CONFIGURATION_FIELD_DEFINE("function", exCriticalConfigurationFieldId_Function, readerString);
			}
			else if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
			{
				continue;
			}
		}
		else
		{
			if (readPlatformSection)
			{
				if (c == ']')
				{
					readPlatformSection = EX_FALSE;
					if (strcmp(readerString.buffer, EXILE_PLATFORM_STRING) == 0)
					{
						readConfiguration = EX_TRUE;
					}
					exString512xClear(&readerString);
					continue;
				}
				else if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
				{
					continue;
				}
			}
		}

		if (readPlatformSection || readConfiguration || readValue)
			exString512xPushChar(&readerString, (char)rc);
	}

	fclose(f);

	exAssertFR(exSetupCriticalConfigurationFromModule(conf.filename, conf.function) == EX_ERROR, {}, EX_ERROR, "failed to load configuration from file %s", file);
	
	return EX_SUCCESS;
}