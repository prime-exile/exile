cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("applications")

include("${CMAKE_SOURCE_DIR}/source/cmake/platform.cmake")

add_subdirectory("exilehost")
