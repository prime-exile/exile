#define EXILE_PRIVATE
#include <exile/ll/ini/iniCompilerStateMachine.hpp>
#include <exile/ll/ini/iniLexerStateMachine.hpp>

exile::ll::IniCompilerSectionDeclareState::IniCompilerSectionDeclareState(IniCompilerStateMachine* machine)
	:exile::ll::IniCompilerState(machine)
{

}

void exile::ll::IniCompilerSectionDeclareState::Input(const Tokenized& token)
{
	if (token.GetId() ==
		static_cast<TokenId>(exile::ll::IniLexerTokenId::SectionName))
	{
		IniInstruction inst{
			token,
			IniInstructionId::ds,
			{token.GetText()}
		};

		GetMachine()->AddInstruction(inst);
		GetMachine()->Reset();
	}
}

