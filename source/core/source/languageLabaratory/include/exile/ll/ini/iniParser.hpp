#ifndef _EXILE_LL_INI_PARSER_HPP_
#define _EXILE_LL_INI_PARSER_HPP_

#include <exile/ll/ini/iniLexerStateMachine.hpp>
#include <exile/ll/ini/iniCompilerStateMachine.hpp>
#include <exile/ll/ini/iniInterpretator.hpp>
#include <exile/core/fs/Path.hpp>

namespace exile
{
	namespace ll
	{
		class EX_API IniParser
		{
			exile::ll::IniCompilerStateMachine compilerStateMachine;
			exile::ll::iniLexerStateMachine lexerStateMachine;
		
			exile::ll::IniInterpretator interpretator;
		public:
			IniParser();

			void AddSection(const exile::String& name, const exile::ll::IniInterpretatorSection& newSection);
			const exile::ll::IniInterpretator& GetInterpretator() const;


			u8 ParseFromFile(const exile::core::Path& path);
			u8 Parse(const exile::String& text);

		};
	}
}

#endif