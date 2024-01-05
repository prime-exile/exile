cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("exile.core")

set(CPP_SOURCES 
	"${CMAKE_CURRENT_SOURCE_DIR}/source/lexer/iniLexerStateMachine.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/lexer/iniLexerMainState.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/lexer/iniLexerIdReadState.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/lexer/iniLexerNumberReadState.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/lexer/iniLexerSectionNameReadState.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/lexer/iniLexerStringReadState.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/lexer/iniLexerInstructionReadState.cpp"

	"${CMAKE_CURRENT_SOURCE_DIR}/source/compiler/iniCompilerStateMachine.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/compiler/iniCompilerSectionDeclareState.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/compiler/iniCompilerMainState.cpp"

	"${CMAKE_CURRENT_SOURCE_DIR}/source/iniInstruction.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/iniInterpretator.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/iniParser.cpp"
)

target_sources(exile.core PRIVATE ${CPP_SOURCES})