cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("exile.forge")

add_executable(exile.forge "source/main.cpp" "source/conf/conf.c" "source/conf/conf.h")

target_link_libraries(exile.forge PUBLIC exile.core)
