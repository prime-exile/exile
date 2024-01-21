#ifndef _EXILE_CORE_CME_SHELL_CONSOLE_HPP_
#define _EXILE_CORE_CME_SHELL_CONSOLE_HPP_

#include <exile/core/cme/shell.hpp>

namespace exile
{
	namespace cme 
	{
		class ShellConsole : public exile::cme::IShell
		{
		private:

			u8 isConsoleOpen;

		public:
			ShellConsole(exile::cme::CentralManagmentEngine* centralManagmentEngine);

			ShellConsole(const ShellConsole&) = delete;

			u8 IsOpen() override;

			void Update() override;

			exile::cme::ShellConsole& operator=(exile::cme::ShellConsole& other) = delete;
			exile::cme::ShellConsole& operator==(exile::cme::ShellConsole& other) = delete;
		};
	}
}

#endif