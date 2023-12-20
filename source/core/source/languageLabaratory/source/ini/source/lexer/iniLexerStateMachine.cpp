#define EXILE_PRIVATE
#include <exile/ll/ini/iniLexerStateMachine.hpp>

exile::ll::IniLexerState::IniLexerState(exile::ll::iniLexerStateMachine* machine)
	:machine(machine)
{

}


exile::ll::iniLexerStateMachine* exile::ll::IniLexerState::GetMachine()
{
	return machine;
}

exile::ll::iniLexerStateMachine::iniLexerStateMachine()
	:main(this), SectionNameRead(this), StringRead(this), IdRead(this, main.GetBufferRef()), NumberRead(this, main.GetBufferRef())
{
	AddLexerStateMachineState(static_cast<u32>(exile::ll::IniLexerStateEnum::Main), &main);
	AddLexerStateMachineState(static_cast<u32>(exile::ll::IniLexerStateEnum::SectionNameRead), &SectionNameRead);
	AddLexerStateMachineState(static_cast<u32>(exile::ll::IniLexerStateEnum::StringRead), &StringRead);
	AddLexerStateMachineState(static_cast<u32>(exile::ll::IniLexerStateEnum::IdRead), &IdRead);
	AddLexerStateMachineState(static_cast<u32>(exile::ll::IniLexerStateEnum::NumberRead), &NumberRead);
	Reset();
}

void exile::ll::iniLexerStateMachine::Reset()
{
	SetLexerStateMachineState(static_cast<u32>(exile::ll::IniLexerStateEnum::Main));
}