cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("exile")

include("exile/platform")
include("exile/path")


add_subdirectory("core")
add_subdirectory("defaultPanicHandler")
add_subdirectory("defaultULP")
add_subdirectory("forge")
if(EXILE_BUILD_WINDOW)
add_subdirectory("window")
endif(EXILE_BUILD_WINDOW)

