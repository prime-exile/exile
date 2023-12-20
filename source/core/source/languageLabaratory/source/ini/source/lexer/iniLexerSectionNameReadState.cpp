#define EXILE_PRIVATE
#include <exile/ll/ini/iniLexerStateMachine.hpp>

exile::ll::IniLexerSectionNameReadState::IniLexerSectionNameReadState(iniLexerStateMachine* machine)
	:exile::ll::IniLexerState(machine)
{
}

void exile::ll::IniLexerSectionNameReadState::Input(char c, exile::Vector<exile::ll::Tokenized>& tokens)
{
	if (c == ']')
	{
		tokens.push_back(exile::ll::Tokenized(buffer, static_cast<i32>(exile::ll::IniLexerTokenId::SectionName)));
		tokens.push_back(Tokenized{ "]", static_cast<TokenId>(exile::ll::IniLexerTokenId::SectionOperator) });
		GetMachine()->Reset();
		buffer.clear();
		return;
	}
	else if (std::isspace(c))
	{
		/*
			TO DO ERROR OUTPUT

		*/
	}
	buffer += c;
}