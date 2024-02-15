#include "conf.h"

#include <stdio.h>
#include <exile/core/memory.h>
#include <exile/core/panic.h>

u8 exConfRegisterOption(exConf* conf, exConfOption* option)
{
	const u64 exConfOptionSize = sizeof(exConfOptionSize);
	if (!conf->root)
	{
		conf->root = exMalloc(exConfOptionSize);
		if (conf->root == NULL) 
		{
			exPanicF("failed to allocate memory for conf option: %s", option->name);
			return EX_ERROR;
		}
		exMemcpy(conf->root, option, exConfOptionSize);
	}
	else 
	{
		exRealloc(conf->root, conf->optionsCount + 1);
		exMemcpy(conf->root + conf->optionsCount, option, exConfOptionSize);
	}
	return EX_SUCCESS;
}

u8 exConfRead(exConf* conf, const exFilePath* path)
{
	FILE* file = fopen(exFilePathGetCStr(path), "r");

	char buffer[1024];
	i32 bufferCounter = 0;
	char* bufferPointer = buffer;

	u8 readString = EX_FALSE;

	for (;;)
	{
		int rc = getc(file);
		if (rc == EOF) break;
		
		if (readString)
		{
			if (rc == '\'')
			{
				readString = EX_FALSE;
			}

			bufferPointer += 1;
			bufferCounter += 1;
			*bufferPointer = (char)rc;
		}

		if (rc == '\'')
		{
			readString = EX_TRUE;
		}



	}


	fclose(file);

	return EX_SUCCESS;
}
