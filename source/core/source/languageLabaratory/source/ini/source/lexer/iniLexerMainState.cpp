#define EXILE_PRIVATE
#include <exile/ll/ini/iniLexerStateMachine.hpp>

exile::ll::IniLexerMainState::IniLexerMainState(iniLexerStateMachine* machine)
	:exile::ll::IniLexerState(machine)
{
}

exile::String& exile::ll::IniLexerMainState::GetBufferRef()
{
	return buffer;
}

void exile::ll::IniLexerMainState::Input(char c, exile::Vector<exile::ll::Tokenized>& tokens)
{
	if (c == '\"')
	{
		tokens.push_back(Tokenized{ "\"", static_cast<TokenId>(exile::ll::IniLexerTokenId::StringOperator) });
		GetMachine()->SetLexerStateMachineState(static_cast<u32>(exile::ll::IniLexerStateEnum::StringRead));
	}
	else if (c == '[')
	{
		tokens.push_back(Tokenized{ "[", static_cast<TokenId>(exile::ll::IniLexerTokenId::SectionOperator) });
		GetMachine()->SetLexerStateMachineState(static_cast<u32>(exile::ll::IniLexerStateEnum::SectionNameRead));
	}
	else if (c == '=')
	{
		tokens.push_back(Tokenized{ "=", static_cast<TokenId>(exile::ll::IniLexerTokenId::Operator) });
	}
	else if (std::isalpha(c))
	{
		buffer += c;
		GetMachine()->SetLexerStateMachineState(static_cast<u32>(exile::ll::IniLexerStateEnum::IdRead));
	}
	else if (std::isdigit(c))
	{
		buffer += c;
		GetMachine()->SetLexerStateMachineState(static_cast<u32>(exile::ll::IniLexerStateEnum::NumberRead));
	}
	else if (c == '\n' || c == ';')
	{
		tokens.push_back(Tokenized{ {c}, static_cast<TokenId>(exile::ll::IniLexerTokenId::LineEnd)});
		buffer.clear();
	}
}