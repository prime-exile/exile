#ifndef _EXILE_CORE_CME_CMD_GET_SYS_ERR_HPP_
#define _EXILE_CORE_CME_CMD_GET_SYS_ERR_HPP_

#if defined(EXILE_UNIX)
#include <errno.h>
#endif

namespace exile
{
	namespace cme
	{
		class CmdGetSysErr : public exile::cme::ICommand
		{
		public:

			u8 Execute(const exile::Vector<exile::String>& args) override
			{
				LogId id = exile::UniversalLoggingProtocol::Get()->GetCoreId();
#if defined(EXILE_UNIX)
				exile::UniversalLoggingProtocol::Get()->Log(id, exile::LogLevel::Info, "error: %s", strerror(errno));
#elif defined(EXILE_WIN)
                DWORD errorMessageID = GetLastError();
                if (errorMessageID == 0) 
				{
					exile::UniversalLoggingProtocol::Get()->Log(id, exile::LogLevel::Info, "None");
					return EX_SUCCESS;
				}

                LPSTR messageBuffer = nullptr;

                size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                    NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

				exile::UniversalLoggingProtocol::Get()->Log(id, exile::LogLevel::Info, "error: %s", messageBuffer);

                LocalFree(messageBuffer);
#endif
				return EX_SUCCESS;
			}

		};
	}
}

#endif