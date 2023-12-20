cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("exile.core")

set(CPP_SOURCES 
	"${CMAKE_CURRENT_SOURCE_DIR}/source/lexer/iniLexerStateMachine.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/lexer/iniLexerMainState.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/lexer/iniLexerIdReadState.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/lexer/IniLexerNumberReadState.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/lexer/iniLexerSectionNameReadState.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/lexer/iniLexerStringReadState.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/lexer/IniLexerInstructionReadState.cpp"

	"${CMAKE_CURRENT_SOURCE_DIR}/source/compiler/iniCompilerStateMachine.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/compiler/iniCompilerSectionDeclareState.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/compiler/iniCompilerMainState.cpp"

	"${CMAKE_CURRENT_SOURCE_DIR}/source/IniInstruction.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/IniInterpretator.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/IniParser.cpp"
)

target_sources(exile.core PRIVATE ${CPP_SOURCES})