cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("exile")

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/platform.cmake")

add_subdirectory("core")
add_subdirectory("defaultPanicHandler")
add_subdirectory("defaultULP")
