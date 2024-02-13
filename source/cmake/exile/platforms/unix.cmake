cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

message("[exile]: platfrom = unix")

add_compile_definitions(EXILE_UNIX)

set(EXILE_NASM_OBJ_FORMAT elf64) 

add_compile_definitions(EXILE_PLATFORM_STRING="unix")