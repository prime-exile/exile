#ifndef _EXILE_CORE_CME_SHELL_CONSOLE_HPP_
#define _EXILE_CORE_CME_SHELL_CONSOLE_HPP_

#include <exile/core/cme/shell.hpp>

namespace exile
{
	namespace cme 
	{
		class ShellConsole : public exile::cme::IShell
		{
			u8 isConsoleOpen;

		public:
			ShellConsole(exile::cme::CentralManagmentEngine* centralManagmentEngine);

			u8 IsOpen() override;

			void Update() override;

		};
	}
}

#endif