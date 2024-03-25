#include <exile/core/API.h>
#include <exile/core/instance.hpp>
#include <exile/core/psstring.h>
#include <iostream>

exile::UniversalLoggingProtocol* ULPdefaultImlp;

extern "C"
{

	u8 exKernelHandleArgs(const char* args)
	{
		int len = strlen(args);
		const char* const end = args + len + 1;

		u8 flag = EX_FALSE;
		u8 loadLibraryFlag = EX_FALSE;

		exString1024x buffer{};
		exString1024xInit(&buffer);

		for (const char* it = args; args != end; it += 1)
		{
			if (flag)
			{
				switch (*it)
				{
				case 'l':
					loadLibraryFlag = EX_TRUE;
					break;
				}
			}

			if (*it == '-')
			{
				flag = EX_TRUE;
				continue;
			}

			if (loadLibraryFlag)
			{

			}


		}

		return EX_SUCCESS;
	}


	/*
		init 
	*/

	EXILE_API_EXPORT
	u8 exKernelEntry(const char* args)
	{
		std::cout << exGetAllocatedMemorySize() << std::endl;
		ULPdefaultImlp = exile::memory::Alloc<exile::UniversalLoggingProtocol>();
		exile::core::CVarSystem::SetupDefaultImpl();
		exGEngine = exile::memory::Alloc<exile::core::Engine>();

		exile::UniversalLoggingProtocol::SetupImpl(ULPdefaultImlp);
		std::cout << exGetAllocatedMemorySize() << std::endl;
		return EX_SUCCESS;
	}

	EXILE_API_EXPORT
	void exKernelShutdown()
	{
		std::cout << exGetAllocatedMemorySize() << std::endl;
		exile::memory::Free(exGEngine);
		exile::core::CVarSystem::Free();
		exile::memory::Free(ULPdefaultImlp);
		std::cout << exGetAllocatedMemorySize() << std::endl;
	}
}