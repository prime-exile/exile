#define EXILE_PRIVATE
#include <exile/ll/ini/iniCompilerStateMachine.hpp>
#include <exile/ll/ini/iniLexerStateMachine.hpp>

exile::ll::IniCompilerMainState::IniCompilerMainState(IniCompilerStateMachine* machine)
	:exile::ll::IniCompilerState(machine)
{

}

void exile::ll::IniCompilerMainState::Input(const Tokenized& token)
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
	else if (!tokens.empty() && token.GetId() ==
		static_cast<TokenId>(exile::ll::IniLexerTokenId::LineEnd))
	{

		if (tokens.size() < 2)
		{
			/*
				TO DO ERROR!
			*/
			exit( -1);
		}
		else if (tokens.size() > 4)
		{

			if (tokens[2].GetText() == "\"")
			{
				IniInstruction inst{
					token,
					IniInstructionId::mov,
					{tokens[0].GetText(), tokens[3].GetText() }
				};

				GetMachine()->AddInstruction(inst);

			}
			else
			{
				exile::String buff;
				buff += tokens[2].GetText();
				buff += ".";
				buff += tokens[4].GetText();

				IniInstruction inst{
					token,
					IniInstructionId::movv,
					{tokens[0].GetText(),buff}
				};

				GetMachine()->AddInstruction(inst);


			}
			tokens.clear();
		}
		else
		{
			IniInstruction inst{
				token,
				IniInstructionId::mov,
				{tokens[0].GetText(),tokens[2].GetText()}
			};

			GetMachine()->AddInstruction(inst);

			tokens.clear();
		}


	}
	else if (token.GetId() ==
		static_cast<TokenId>(exile::ll::IniLexerTokenId::SectionOperator))
	{
		return;
	}
	else
	{
		if (token.GetId() ==
			static_cast<TokenId>(exile::ll::IniLexerTokenId::LineEnd))
			return;
		tokens.emplace_back(token);
	}


}
