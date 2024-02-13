#ifndef _EXILE_CORE_CME_CMD_EXEC_ENGINE_HPP_
#define _EXILE_CORE_CME_CMD_EXEC_ENGINE_HPP_

#include <exile/core/containers/unordered_map.hpp>
#include <exile/core/cme/command.hpp>

namespace exile
{
	namespace cme
	{
		class EX_API CommandExecutionEngine
		{
		private:

			exile::UnorderedMap<u32, exile::cme::ICommand*> commands;

		public:

			CommandExecutionEngine(){}
			CommandExecutionEngine(const CommandExecutionEngine&) = delete;

			i64 RegisterCommand(const exile::String& name, exile::cme::ICommand* command);
			void UnregisterCommand(u32 hash);
			void UnregisterCommand(const exile::String& name);

			u8 CommandExists(const exile::String& name);

			u8 Execute(const exile::String& command);
			u8 Execute(const exile::String& commandName, const exile::Vector<exile::String> args);
			
			u8 Execute(u32 hash, const exile::Vector<exile::String> args);

			exile::cme::CommandExecutionEngine& operator=(exile::cme::CommandExecutionEngine& other) = delete;
			exile::cme::CommandExecutionEngine& operator==(exile::cme::CommandExecutionEngine& other) = delete;

		};
	}
}

#endif