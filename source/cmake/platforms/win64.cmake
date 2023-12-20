cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

message("[exile]: platfrom = win64")
# EXILE_WIN_LONG_PATH/EXILE_CUSTOM_PATH_LEN
add_compile_definitions(EXILE_WIN)

option(ENABLE_EXILE_WIN_LONG_PATH "enable windows long path(see in docs)" OFF)


if(MSVC)
	add_compile_definitions(EXILE_MSVC)
endif(MSVC)

set(EXILE_NASM_OBJ_FORMAT win64) 

add_compile_definitions(EXILE_PLATFORM_STRING="win64")
