cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("exile.core")

set_source_files_properties(${ASM_SOURCES} PROPERTIES LANGUAGE ASM_NASM)

set(ASM_SOURCES
	"${CMAKE_CURRENT_SOURCE_DIR}/test_asm.asm"
	"${CMAKE_CURRENT_SOURCE_DIR}/memset.asm"
)

target_sources(exile.core PRIVATE ${ASM_SOURCES})