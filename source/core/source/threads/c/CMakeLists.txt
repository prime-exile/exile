cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("exile.core")

set(C_SOURCES 
	"${CMAKE_CURRENT_SOURCE_DIR}/source/exThreadCreate.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/exThreadDestroy.c"
)

target_sources(exile.core PRIVATE ${C_SOURCES})
