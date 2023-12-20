#define EXILE_PRIVATE
#include <exile/ll/lexer.hpp>

exile::ll::LexerStateMachine::LexerStateMachine()
	:currentStateId(0)
{

}

exile::ll::LexerStateMachine::LexerStateMachine(const exile::UnorderedMap<u32, LexerStateMachineState*>& states)
	:states(states), currentStateId(0)
{

}

void exile::ll::LexerStateMachine::AddLexerStateMachineState(u32 id, LexerStateMachineState* s)
{
	states[id] = s;
}

void exile::ll::LexerStateMachine::SetLexerStateMachineState(u32 id)
{
	prevStateId = currentStateId;
	currentStateId = id;
	currentState = states[id];
}

void exile::ll::LexerStateMachine::Reset()
{
	SetLexerStateMachineState(0);
}


void exile::ll::LexerStateMachine::Input(char c, exile::Vector<Tokenized>& tokens)
{
	currentState->Input(c, tokens);
}