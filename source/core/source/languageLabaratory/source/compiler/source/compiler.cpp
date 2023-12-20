#include <exile/ll/compiler.hpp>

exile::ll::Compiler::Compiler(CompilerStateMachine& machine)
	:machine(machine)
{

}

u8 exile::ll::Compiler::Compile(const exile::Vector<Tokenized>& tokens)
{
	for (const Tokenized& t : tokens)
	{
		machine.Input(t);
	}

	return 0;
}

