#define EXILE_PRIVATE
#include <exile/ll/ini/iniLexerStateMachine.hpp>

exile::ll::IniLexerIdReadState::IniLexerIdReadState(iniLexerStateMachine* machine, exile::String& buffer)
	:exile::ll::IniLexerState(machine), buffer(buffer)
{
}

void exile::ll::IniLexerIdReadState::Input(char c, exile::Vector<exile::ll::Tokenized>& tokens)
{
	if (!isWordReaded)
	{
		if (c == ' ')
		{
			isWordReaded = true;
		}
		else if (c == '=')
		{
			tokens.push_back(exile::ll::Tokenized(buffer, static_cast<i32>(exile::ll::IniLexerTokenId::Identifier)));
			buffer = c;
			tokens.push_back(exile::ll::Tokenized(buffer, static_cast<i32>(exile::ll::IniLexerTokenId::Operator)));
			GetMachine()->Reset();
			buffer.clear();
			return;
		}
		else if (c == '.')
		{
			tokens.push_back(exile::ll::Tokenized(buffer, static_cast<i32>(exile::ll::IniLexerTokenId::Identifier)));
			buffer = c;
			tokens.push_back(exile::ll::Tokenized(buffer, static_cast<i32>(exile::ll::IniLexerTokenId::Operator)));
			GetMachine()->Reset();
			buffer.clear();
			return;
		}
		else if (c == ';' || c == '\n')
		{
			tokens.push_back(exile::ll::Tokenized(buffer, static_cast<i32>(exile::ll::IniLexerTokenId::Identifier)));
			buffer = c;
			tokens.push_back(exile::ll::Tokenized(buffer, static_cast<i32>(exile::ll::IniLexerTokenId::Operator)));
			GetMachine()->Reset();
			buffer.clear();
			return;
		}
	}
	else
	{
		// if operator!
		if (c == '=')
		{
			tokens.push_back(exile::ll::Tokenized(buffer, static_cast<i32>(exile::ll::IniLexerTokenId::Identifier)));
			buffer = c;
			tokens.push_back(exile::ll::Tokenized(buffer, static_cast<i32>(exile::ll::IniLexerTokenId::Operator)));
			GetMachine()->Reset();
			buffer.clear();
			isWordReaded = false;
			return;
		}

	}
	if(!isWordReaded)
		buffer += c;
}