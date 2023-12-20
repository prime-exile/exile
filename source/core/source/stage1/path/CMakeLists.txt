cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("exile.core")

if(EX_DYN_PATH)
file(GLOB STR_SPEC_SOURCES "source/dynamic/*.c")
else()
file(GLOB STR_SPEC_SOURCES "source/static/*.c")
endif()
file(GLOB STR_SOURCES "source/*.c")


set(C_SOURCES 
	${STR_SPEC_SOURCES}
	${STR_SOURCES}
)

target_sources(exile.core PRIVATE ${C_SOURCES})