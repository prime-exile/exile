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
		public:

			CentralManagmentEngine();

			exile::cme::CommandExecutionEngine& GetCommandEngine();

			void SetupShell(IShell* currentShell);
			void SetPanicMessage(const exile::String& message);
			void RunShell();

			void SetContinueExectionState(u8 state);
			u8 Continue();

			~CentralManagmentEngine();
		};
	}
}

#endif