cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("defaultPanicHandler")

add_library(dph SHARED "source/main.c")
target_link_libraries(dph exile.core)