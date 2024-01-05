#include <exile/core/cme/instance.hpp>
#include <exile/core/instance.hpp>

#include "commands/echo.hpp"
#include "commands/exit.hpp"

exile::cme::CmdEcho cmdEcho;
exile::cme::CmdExit cmdExit;

exile::cme::CentralManagmentEngine::CentralManagmentEngine()
{
	cmdEngine.RegisterCommand("echo", &cmdEcho);
	cmdEngine.RegisterCommand("exit", &cmdExit);
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

const exile::Vector<exile::String>& exile::cme::CentralManagmentEngine::GetStacktrace()
{
	return stacktrace;
}

const exile::String& exile::cme::CentralManagmentEngine::GetPanicMessage()
{
	return panicMessage;
}

void exile::cme::CentralManagmentEngine::InstallStackTrace(const exile::Vector<exile::String>& stacktrace)
{
	this->stacktrace = stacktrace;
}

void exile::cme::CentralManagmentEngine::InstallStackTrace(const char** const stacktrace, u64 size)
{
	this->stacktrace = std::move(exile::Vector<exile::String>(stacktrace, stacktrace+size));
}

void exile::cme::CentralManagmentEngine::AddStackTraceEntry(const exile::String& entry)
{
	stacktrace.emplace_back(entry);
}

void exile::cme::CentralManagmentEngine::StackTraceReserve(u32 count)
{
	stacktrace.reserve(count);
}

exile::cme::CommandExecutionEngine& exile::cme::CentralManagmentEngine::GetCommandEngine()
{
	return cmdEngine;
}

exile::cme::CentralManagmentEngine::~CentralManagmentEngine()
{

}