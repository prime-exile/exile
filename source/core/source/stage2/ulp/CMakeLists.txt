cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("exile.core")


set(CPP_SOURCES 
	"${CMAKE_CURRENT_SOURCE_DIR}/source/UniversalLoggingProtocol.cpp"
)

target_sources(exile.core PRIVATE ${CPP_SOURCES} )