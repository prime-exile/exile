cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("exile.LL")

set(CPP_SOURCES 
	"${CMAKE_CURRENT_SOURCE_DIR}/source/lexer.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/stateMachine.cpp"
)

target_sources(exile.core PRIVATE ${CPP_SOURCES})