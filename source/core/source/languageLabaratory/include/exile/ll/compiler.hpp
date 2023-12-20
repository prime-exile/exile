#ifndef _EXILE_LL_COMPILER_HPP_
#define _EXILE_LL_COMPILER_HPP_

#include <exile/ll/lexer.hpp>

namespace exile
{

	namespace ll
	{
		class EX_API Compiler;

		class EX_API CompilerStateMachineState
		{

		public:

			virtual void Input(const Tokenized& token) = 0;
			virtual ~CompilerStateMachineState()
			{
				
			}
		};

		class EX_API CompilerStateMachine
		{
			exile::UnorderedMap<u32, CompilerStateMachineState*> states;
			CompilerStateMachineState* currentState;

		public:

			CompilerStateMachine();

			void AddState(u32 id, CompilerStateMachineState* s);
			void SetState(u32 id);


			void Input(const Tokenized& token);
		
			virtual void Reset();

			virtual ~CompilerStateMachine();
		};

		class EX_API Compiler
		{
			CompilerStateMachine& machine;
		public:

			Compiler(CompilerStateMachine& machine);

			u8 Compile(const exile::Vector<Tokenized>& tokens);

		};
	}


}

#endif