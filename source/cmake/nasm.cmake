cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

message("[exile]: using nasm")

set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> <FLAGS> -o <OBJECT> <SOURCE>")

add_compile_options(
    "$<$<COMPILE_LANGUAGE:ASM_NASM>:-f $<IF:$<BOOL:$<TARGET_PROPERTY:NASM_OBJ_FORMAT>>, \
    $<TARGET_PROPERTY:NASM_OBJ_FORMAT>, ${CMAKE_ASM_NASM_OBJECT_FORMAT}>>"
)

if(WIN32)
	string(APPEND CMAKE_ASM_NASM_FLAGS "-dWIN32=1")
endif(WIN32)

enable_language(ASM_NASM)
