cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("exile.core")

target_sources(exile.core PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/source/thread.c")