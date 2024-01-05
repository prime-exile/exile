#define EXILE_PRIVATE
#include <exile/ll/ini/iniLexerStateMachine.hpp>

exile::ll::IniLexerInstructionReadState::IniLexerInstructionReadState(iniLexerStateMachine* machine)
	:exile::ll::IniLexerState(machine), stringReadState(machine), numberReadState(machine, buffer)
{

}

void exile::ll::IniLexerInstructionReadState::Input(char c, exile::Vector<Tokenized>& tokens)
{
	
}
