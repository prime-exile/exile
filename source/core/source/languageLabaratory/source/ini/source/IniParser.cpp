#define EXILE_PRIVATE
#include <exile/ll/ini/iniParser.hpp>
#include <exile/core/fs/File.hpp>
extern "C"
{
#include <exile/core/assert.h>

}

exile::ll::IniParser::IniParser()
{

}

void exile::ll::IniParser::AddSection(const exile::String& name, const exile::ll::IniInterpretatorSection& newSection)
{
	interpretator.AddSection(name, newSection);
}


const exile::ll::IniInterpretator& exile::ll::IniParser::GetInterpretator() const
{
	return interpretator;
}

u8 exile::ll::IniParser::ParseFromFile(const exile::core::Path& path)
{
	exile::core::File file;
	EX_s1AssertFR(file.Open(path, "r") == EX_ERROR, {}, EX_ERROR, "failed to open file %s", path.CStr());
	
	exile::String str;
	u64 fSize = file.GetSize();
	file.Read(str, fSize);

	file.Close();

	return Parse(str);
}

u8 exile::ll::IniParser::Parse(const exile::String& text)
{
	exile::ll::Lexer lexer(lexerStateMachine);
	lexerStateMachine.Reset();
	EX_s1AssertFR(lexer.Tokenize(text), {}, EX_ERROR, "failed to tokenize ini file\n%s", text);

	exile::ll::Compiler compiler(compilerStateMachine);
	compilerStateMachine.Reset();
	EX_s1AssertFR(compiler.Compile(lexer.GetTokens()), {}, EX_ERROR, "failed to compile ini file\n%s", text);
	for (const exile::ll::IniInstruction& inst : compilerStateMachine.GetInstructions())
	{
		interpretator.Interpretate(inst);
	}

	interpretator.Complete();
	
	return EX_SUCCESS;
}

