
#define EXILE_PRIVATE
#include <exile/ll/compiler.hpp>

exile::ll::CompilerStateMachine::CompilerStateMachine()
{
}

void exile::ll::CompilerStateMachine::AddState(u32 id, CompilerStateMachineState* s)
{
	states[id] = s;
}

void exile::ll::CompilerStateMachine::SetState(u32 id)
{
	currentState = states[id];
}


void exile::ll::CompilerStateMachine::Input(const Tokenized& token)
{
	currentState->Input(token);
}

void exile::ll::CompilerStateMachine::Reset()
{
	SetState(0);
}

exile::ll::CompilerStateMachine::~CompilerStateMachine()
{

}