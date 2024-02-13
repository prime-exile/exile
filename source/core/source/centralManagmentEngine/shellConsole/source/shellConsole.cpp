#define EXILE_PRIVATE
#include <exile/core/cme/shellConsole.hpp>
#include <exile/core/cme/instance.hpp>
#include <exile/core/containers/string.hpp>

#include <iostream>

exile::cme::ShellConsole::ShellConsole(exile::cme::CentralManagmentEngine* centralManagmentEngine)
	: exile::cme::IShell(centralManagmentEngine), isConsoleOpen(EX_TRUE)
{
}


u8 exile::cme::ShellConsole::IsOpen()
{
	return isConsoleOpen;
}

void exile::cme::ShellConsole::Update()
{
	exile::String line;
	std::getline(std::cin, line);
	if (line == "close")
	{
		isConsoleOpen = EX_FALSE;
	}
	else
	{
		centralManagmentEngine->GetCommandEngine().Execute(line);
	}

}
