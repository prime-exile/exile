cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(exile.core)

add_subdirectory("commandExecutionEngine")
add_subdirectory("instance")
add_subdirectory("panic")
add_subdirectory("shellConsole")
add_subdirectory("capi")