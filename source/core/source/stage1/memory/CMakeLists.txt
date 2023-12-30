cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("exile.core")

set(C_SOURCES 
	"${CMAKE_CURRENT_SOURCE_DIR}/source/exFree.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/exMalloc.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/exRealloc.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/exGetAllocatedMemorySize.c"
)

add_subdirectory("source/${EXILE_NASM_OBJ_FORMAT}")

target_sources(exile.core PRIVATE ${C_SOURCES}  )