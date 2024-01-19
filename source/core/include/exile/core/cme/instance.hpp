#ifndef _EXILE_CORE_CME_INSTANCE_HPP_
#define _EXILE_CORE_CME_INSTANCE_HPP_

#include <exile/core/cme/commandExecutionEngine.hpp>
#include <exile/core/cme/shell.hpp>

namespace exile
{
	namespace cme
	{
		class EX_API CentralManagmentEngine
		{
			exile::cme::CommandExecutionEngine cmdEngine;
		
			exile::String panicMessage;

			IShell* currentShell;
			u8 continueExection;

			u64 threadId;

			exile::Vector<exile::String> stacktrace;
		public:

			CentralManagmentEngine();

			exile::cme::CommandExecutionEngine& GetCommandEngine();

			void SetupShell(IShell* currentShell);
			void SetPanicMessage(const exile::String& message);
			void RunShell();

			void SetContinueExectionState(u8 state);
			u8 Continue();

			const exile::Vector<exile::String>& GetStacktrace();
			const exile::String& GetPanicMessage();

			void InstallStackTrace(const exile::Vector<exile::String>& stacktrace);
			void InstallStackTrace(const char** const stacktrace, u64 size);

			void AddStackTraceEntry(const exile::String& entry);
			void StackTraceReserve(u32 count);

			void SetThreadId(u64 id);
			u64 GetThreadId();

			~CentralManagmentEngine();
		};
	}
}

#endif