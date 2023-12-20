#ifndef _EXILE_LL_INI_LEXER_LexerStateMachineState_MACHINE_HPP_
#define _EXILE_LL_INI_LEXER_LexerStateMachineState_MACHINE_HPP_

#include <exile/ll/lexer.hpp>

namespace exile
{
	namespace ll
	{
		enum class IniLexerStateEnum : u32
		{
			Main,
			StringRead,
			SectionNameRead,
			IdRead,
			NumberRead
		};

		enum class IniLexerTokenId : i32
		{
			String,
			StringOperator,
			SectionName,
			SectionOperator,
			Operator,
			Identifier,
			Number,
			LineEnd
		};
		
		class EX_API iniLexerStateMachine;

		class EX_API IniLexerState : public exile::ll::LexerStateMachineState
		{
			iniLexerStateMachine* machine;
		protected:
			iniLexerStateMachine* GetMachine();
			IniLexerState(iniLexerStateMachine* machine);
		public:
			virtual void Input(char c, exile::Vector<Tokenized>& tokens) override 
			{}

		};

		class EX_API IniLexerStringReadState : public exile::ll::IniLexerState
		{
			exile::String buffer;
		public:
			IniLexerStringReadState(iniLexerStateMachine* machine);
			void Input(char c, exile::Vector<Tokenized>& tokens) override;
		};

		class EX_API IniLexerSectionNameReadState : public exile::ll::IniLexerState
		{
			exile::String buffer;
		public:
			IniLexerSectionNameReadState(iniLexerStateMachine* machine);
			void Input(char c, exile::Vector<Tokenized>& tokens) override;
		};

		class EX_API IniLexerIdReadState : public exile::ll::IniLexerState
		{
			exile::String& buffer;
			bool isWordReaded = false;

		public:
			IniLexerIdReadState(iniLexerStateMachine* machine, exile::String& buffer);
			void Input(char c, exile::Vector<Tokenized>& tokens) override;
		};

		class EX_API IniLexerNumberReadState : public exile::ll::IniLexerState
		{
			exile::String& buffer;
		public:
			IniLexerNumberReadState(iniLexerStateMachine* machine, exile::String& buffer);
			void Input(char c, exile::Vector<Tokenized>& tokens) override;
		};

		class EX_API IniLexerMainState : public exile::ll::IniLexerState
		{
			exile::String buffer;
		public:
			IniLexerMainState(iniLexerStateMachine* machine);
			void Input(char c, exile::Vector<Tokenized>& tokens) override;
			exile::String& GetBufferRef();
		};

		// full work of the translate one instruction and have sub states that support to read all
		class EX_API IniLexerInstructionReadState : public exile::ll::IniLexerState
		{
			IniLexerNumberReadState numberReadState;
			IniLexerStringReadState stringReadState;

			exile::String buffer;

		public:
			IniLexerInstructionReadState(iniLexerStateMachine* machine);
			void Input(char c, exile::Vector<Tokenized>& tokens) override;
		};


		class EX_API iniLexerStateMachine : public exile::ll::LexerStateMachine
		{

			IniLexerMainState main;
			IniLexerIdReadState IdRead;
			IniLexerSectionNameReadState SectionNameRead;
			IniLexerStringReadState StringRead;
			IniLexerNumberReadState NumberRead;
			
		public:
			iniLexerStateMachine();

			void Reset() override;
		};
	}
}

#endif 