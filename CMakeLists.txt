cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("exile" C CXX)

option(EXILE_ENABLE_TESTS "enable CTests" ON)
option(EXILE_BUILD_DEV "enable dev build" ON)
option(EXILE_BUILD_MINGW "enable dev build" OFF)
option(EXILE_BUILD_APPS "enable applications build" ON)
option(EXILE_BUILD_WINDOW "enable window plugin build" ON)
option(EXILE_BUILD_FORGE "enable forge(please see firstly before enable it)" OFF)



list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/source/cmake")

add_subdirectory("source")
add_subdirectory("applications")


if(EXILE_ENABLE_TESTS)
	message("EXILE_ENABLE_TESTS = ${EXILE_ENABLE_TESTS}")
	add_subdirectory("tests")
endif(EXILE_ENABLE_TESTS)

execute_process(COMMAND date "+%Y-%m-%d %H:%M:%S" OUTPUT_VARIABLE BUILD_TIME OUTPUT_STRIP_TRAILING_WHITESPACE)
message("Build time: ${BUILD_TIME}")
