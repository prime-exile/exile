#define EXILE_PRIVATE
#include <exile/ll/ini/iniLexerStateMachine.hpp>

exile::ll::IniLexerStringReadState::IniLexerStringReadState(iniLexerStateMachine* machine)
	:exile::ll::IniLexerState(machine)
{
}

void exile::ll::IniLexerStringReadState::Input(char c, exile::Vector<exile::ll::Tokenized>& tokens)
{
	if (c == '\"')
	{
		tokens.push_back(exile::ll::Tokenized(buffer, static_cast<i32>(exile::ll::IniLexerTokenId::String)));
		tokens.push_back(Tokenized{ "\"", static_cast<TokenId>(exile::ll::IniLexerTokenId::StringOperator) });
		GetMachine()->Reset();
		buffer.clear();
	}
	else buffer += c;
}