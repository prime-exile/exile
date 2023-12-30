#include<exile/core/memory.h>
#include<exile/core/version.h>
#include<exile/core/path.h>
#include <stdio.h>

void PrintVersion(const exVersion* version)
{
	char buffer[1024];
	u32 len = exVersionStr(version, 1024, buffer);
	if (len >= 1024)
	{
		char* dBuffer = exMalloc(len + 1);
		exVersionStr(version, len, dBuffer);
		puts(dBuffer);
		puts("\n");
	}

	puts(buffer);
}

int main()
{
	exVersion vers;
	puts( EX_VERSION_STRING);
	exVersionParse(&vers, "exp:21.2.0");
	printf("App Version: %u.%u alpha %u\n", vers.ver.components.major, vers.ver.components.minor, vers.ver.components.alpha);
	PrintVersion(&vers);
	exVersionParse(&vers, "exp:0.1.0");
	printf("App Version: %u.%u alpha %u\n", vers.ver.components.major, vers.ver.components.minor, vers.ver.components.alpha);
	PrintVersion(&vers);
	exVersionParse(&vers, "0.0.1");
	printf("App Version: %u.%u alpha %u\n", vers.ver.components.major, vers.ver.components.minor, vers.ver.components.alpha);
	PrintVersion(&vers);

	return 0;
}
