#define EXILE_PRIVATE
#include <exile/core/version.h>
#include <exile/core/assert.h>
#include <exile/core/psstring.h>

#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>

/* TO DO:
	find more optimizated mo
*/
EXILE_API_EXPORT
u8 exVersionParse(exVersion* ver, const char* buffer)
{
	int len = strlen(buffer);
	u8 isNumberReading = EX_FALSE;
	
	exString512x tmpBuffer;
	exString512xInit(&tmpBuffer);

	char* sym =  strchr(buffer, ':');
	isNumberReading = sym == NULL;

	u8 numberReadedCounter = 0;

	for(u32 i = 0; i < len; i += 1)
	{
		if(isNumberReading)
		{
			char c = buffer[i];
			if(c == '.')
			{
				unsigned long val = strtoul(tmpBuffer.buffer, NULL, 10);

				switch(numberReadedCounter)
				{
					case 0:
						ver->ver.components.major = val;
					break;
					case 1:
						ver->ver.components.minor = val;
					break;
				}
				
				numberReadedCounter += 1;
				exString512xClear(&tmpBuffer);
				continue;
			}
			exString512xPushChar(&tmpBuffer, c);
		}
		else
		{
			char c = buffer[i];
			if(c == ':')
			{
				EX_s1AssertR(strcmp(tmpBuffer.buffer, "exp") != 0, {}, EX_ERROR, "failed to parse version, token \':\' founded but exp wont found!");
				ver->isExp = EX_TRUE;
				exString512xClear(&tmpBuffer);
				isNumberReading = EX_TRUE;
				continue;
			}

 			exString512xPushChar(&tmpBuffer, c);
		}

	}

	unsigned long val = strtoul(tmpBuffer.buffer, NULL, 10);
	ver->ver.components.alpha = val;

	return EX_SUCCESS;
}
