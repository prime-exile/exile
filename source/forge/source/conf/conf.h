#ifndef _EXILE_FORGE_CONF_HPP_
#define _EXILE_FORGE_CONF_HPP_


#include <exile/core/API.h>
#include <exile/core/path.h>

typedef struct
{
	char name[512];
	u8 isOptionArray;
	void* value;
} exConfOption;


typedef struct
{
	exConfOption* root;
	u16 optionsCount;
} exConf;

u8 exConfRegisterOption(exConf* conf, exConfOption* option);
u8 exConfRead(exConf* conf, const exFilePath* path);

#endif
