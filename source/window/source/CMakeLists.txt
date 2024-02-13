cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("exile.window")

target_sources(exile.window PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")


add_subdirectory("backend")
add_subdirectory("platform")

target_include_directories(exile.window PRIVATE "include/")


