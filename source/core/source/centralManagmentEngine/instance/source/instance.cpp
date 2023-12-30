#include <exile/core/cme/instance.hpp>
#include <exile/core/instance.hpp>

#include "commands/echo.hpp"

exile::cme::CmdEcho cmdEcho;

exile::cme::CentralManagmentEngine::CentralManagmentEngine()
{
	cmdEngine.RegisterCommand("echo", &cmdEcho);
}

void exile::cme::CentralManagmentEngine::SetupShell(IShell* currentShell)
{
	this->currentShell = currentShell;
}

void exile::cme::CentralManagmentEngine::SetPanicMessage(const exile::String& message)
{
	panicMessage = message;
}

void exile::cme::CentralManagmentEngine::RunShell()
{
	while (currentShell->IsOpen())
		currentShell->Update();
}

void exile::cme::CentralManagmentEngine::SetContinueExectionState(u8 state)
{
	continueExection = state;
}

u8 exile::cme::CentralManagmentEngine::Continue()
{
	return continueExection;
}

exile::cme::CommandExecutionEngine& exile::cme::CentralManagmentEngine::GetCommandEngine()
{
	return cmdEngine;
}

exile::cme::CentralManagmentEngine::~CentralManagmentEngine()
{

}