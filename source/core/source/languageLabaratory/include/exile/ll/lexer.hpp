#ifndef _EXILE_LL_LEXER_HPP_
#define _EXILE_LL_LEXER_HPP_

#include <exile/core/API.h>
#include <exile/core/containers/unordered_map.hpp>
#include <exile/core/containers/string.hpp>
#include <exile/core/containers/function.hpp>
#include <exile/core/containers/vector.hpp>

namespace exile
{
	namespace ll
	{
		typedef i32 TokenId;


		class Tokenized
		{
			TokenId id;
			exile::String text;

		public:
			Tokenized(const exile::String& text, const TokenId id)
				:id(id),
				text(text)
			{

			}

			Tokenized()
			{

			}

			Tokenized& operator=(const Tokenized& other)
			{
				text = other.text;
				id = other.id;
				return *this;
			}

			const TokenId GetId() const
			{
				return id;
			}

			const exile::String& GetText() const
			{
				return text;
			}
		};

		class EX_API LexerStateMachineState
		{
		public:
			virtual void Input(char c, exile::Vector<Tokenized>& tokens) = 0;
			virtual ~LexerStateMachineState()
			{

			}
		};

		class EX_API LexerStateMachine
		{
			exile::UnorderedMap<u32, LexerStateMachineState*> states;
			LexerStateMachineState* currentState;

			u32 currentStateId;
			u32 prevStateId;

		public:

			LexerStateMachine();
			LexerStateMachine(const exile::UnorderedMap<u32, LexerStateMachineState*>& LexerStateMachineStates);

			void AddLexerStateMachineState(u32 id, LexerStateMachineState* s);
			void SetLexerStateMachineState(u32 id);

			void Input(char c, exile::Vector<Tokenized>& tokens);

			virtual void Reset();

			virtual ~LexerStateMachine()
			{

			}
		};


		class EX_API Lexer
		{
			LexerStateMachine& machine;
			exile::Vector<Tokenized> tokens;
		public:

			static constexpr TokenId InvalidToken = -2;

			Lexer(LexerStateMachine& machine);

			u8 Tokenize(const exile::String& text);

			const exile::Vector<Tokenized>& GetTokens();
		};
	}
}

#endif