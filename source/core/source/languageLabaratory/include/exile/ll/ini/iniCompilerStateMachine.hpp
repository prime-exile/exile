#ifndef _EXILE_LL_INI_COMPILER_STATE_MACHINE_HPP_
#define _EXILE_LL_INI_COMPILER_STATE_MACHINE_HPP_

#include <exile/ll/compiler.hpp>
#include <exile/ll/ini/iniInstruction.hpp>

namespace exile
{
	namespace ll
	{


		class EX_API IniCompilerStateMachine;
		enum class IniCompilerStateEnum : u32
		{
			Main,
			SectionDeclare
		};

		class EX_API IniCompilerState : public exile::ll::CompilerStateMachineState
		{
			IniCompilerStateMachine* machine;
		protected:
			IniCompilerStateMachine* GetMachine();
			IniCompilerState(IniCompilerStateMachine* machine);
		public:
			virtual void Input(const Tokenized& token) override
			{}

		};

		class EX_API IniCompilerMainState : public exile::ll::IniCompilerState
		{
			exile::Vector<exile::ll::Tokenized> tokens;
		public:

			IniCompilerMainState(IniCompilerStateMachine* machine);
			void Input(const Tokenized& token) override;

		};

		class EX_API IniCompilerSectionDeclareState : public exile::ll::IniCompilerState
		{

		public:

			IniCompilerSectionDeclareState(IniCompilerStateMachine* machine);
			void Input(const Tokenized& token) override;

		};

		class EX_API IniCompilerStateMachine : public exile::ll::CompilerStateMachine
		{
			exile::Vector<exile::ll::IniInstruction> instructions;

			IniCompilerSectionDeclareState declState;
			IniCompilerMainState main;

		public:
			IniCompilerStateMachine();

			void AddInstruction(const exile::ll::IniInstruction& instruction);

			void Reset() override;

			const exile::Vector<exile::ll::IniInstruction> GetInstructions() const;
		};
	}
}

#endif