#define EXILE_PRIVATE 
#include <exile/ll/ini/iniCompilerStateMachine.hpp>

exile::ll::IniCompilerState::IniCompilerState(IniCompilerStateMachine* machine)
	:machine(machine)
{

}

exile::ll::IniCompilerStateMachine* exile::ll::IniCompilerState::GetMachine()
{
	return machine;
}

exile::ll::IniCompilerStateMachine::IniCompilerStateMachine()
	:main(this), declState(this)
{
	AddState(static_cast<u32>(exile::ll::IniCompilerStateEnum::Main), &main);
	AddState(static_cast<u32>(exile::ll::IniCompilerStateEnum::SectionDeclare), &declState);

	exile::ll::IniInstruction mainSectionDeclare{
		{},
		exile::ll::IniInstructionId::ds,
		{"main"}
	};
}

void exile::ll::IniCompilerStateMachine::AddInstruction(const exile::ll::IniInstruction& instruction)
{
	instructions.emplace_back(instruction);
}

const exile::Vector<exile::ll::IniInstruction> exile::ll::IniCompilerStateMachine::GetInstructions() const
{
	return instructions;
}

void exile::ll::IniCompilerStateMachine::Reset()
{
	SetState(static_cast<u32>(exile::ll::IniCompilerStateEnum::Main));
}
