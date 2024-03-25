cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("exile.forge")

add_library(exile.forge.kernel SHARED "source/main.cpp")

target_link_libraries(exile.forge.kernel PRIVATE exile.core)