cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("exile" C CXX)

include("exile/platform")

add_subdirectory("core")
add_subdirectory("window")