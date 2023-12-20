#define EXILE_PRIVATE
#include <exile/ll/ini/iniLexerStateMachine.hpp>

exile::ll::IniLexerNumberReadState::IniLexerNumberReadState(iniLexerStateMachine* machine, exile::String& buffer)
	:exile::ll::IniLexerState(machine), buffer(buffer)
{
}

void exile::ll::IniLexerNumberReadState::Input(char c, exile::Vector<exile::ll::Tokenized>& tokens)
{
	if (c == ' ')
	{
		tokens.push_back(exile::ll::Tokenized(buffer, static_cast<i32>(exile::ll::IniLexerTokenId::Identifier)));
		GetMachine()->Reset();
		buffer.clear();
	}
	else if (c == '\n' || c == ';')
	{
		tokens.push_back(exile::ll::Tokenized(buffer, static_cast<i32>(exile::ll::IniLexerTokenId::Identifier)));
		tokens.push_back(Tokenized{ {c}, static_cast<TokenId>(exile::ll::IniLexerTokenId::LineEnd) });
		GetMachine()->Reset();
		buffer.clear();
	}
	buffer += c;
}