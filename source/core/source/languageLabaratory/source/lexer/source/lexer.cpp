#define EXILE_PRIVATE
#include <exile/ll/lexer.hpp>
#include <exile/core/containers/vector.hpp>

exile::ll::Lexer::Lexer(exile::ll::LexerStateMachine& machine)
	:machine(machine)
{}


u8 exile::ll::Lexer::Tokenize(const exile::String& text)
{
	exile::String tmpBuffer;

	exile::Vector<exile::UnorderedMapPair<TokenId, exile::String>> vec;

	for (char c : text)
	{
		machine.Input(c, tokens);
	}

	return 0;
}

const exile::Vector<exile::ll::Tokenized>& exile::ll::Lexer::GetTokens()
{
	return tokens;
}