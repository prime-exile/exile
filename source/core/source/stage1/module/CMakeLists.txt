cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("exile.core")

message("memory ${CMAKE_CURRENT_SOURCE_DIR}")

set(C_SOURCES 
	"${CMAKE_CURRENT_SOURCE_DIR}/source/exNativeModuleFree.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/exNativeModuleGetAddress.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/exNativeModuleLoad.c"
)

target_sources(exile.core PRIVATE ${C_SOURCES} )