cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("exile" C CXX)

include("exile/platform")
include("exile/path")

add_subdirectory("core")
add_subdirectory("window")
add_subdirectory("forge")