cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("exile.languageLabaratory")

if(EXILE_BUILD_DEV)
add_compile_definitions(EXILE_DEV)
endif()
add_subdirectory("source")

target_include_directories(exile.core PUBLIC "include/")