cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("exile.forge")

add_library(exile.forge STATIC "source/conf/conf.c" "source/shared/exile/forge/conf.h" "kernel/source/main.cpp" "source/boot/boot.c" "source/shared/exile/forge/assert.h")

if(EXILE_FORGE_MAIN)
target_sources(exile.forge PRIVATE "source/entry.cpp")
endif(EXILE_FORGE_MAIN)

add_executable(exile.forge.example "source/main.cpp" )

target_link_libraries(exile.forge PUBLIC exile.core)
target_link_libraries(exile.forge.example PRIVATE exile.forge exile.core)

target_include_directories(exile.forge PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/source/shared/")

target_compile_definitions(exile.forge PRIVATE EXILE_DISABLE_CME_DUMP)

add_subdirectory("kernel")

add_custom_command(
        TARGET exile.forge POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:exile.core>
                $<TARGET_FILE_DIR:exile.forge>)

add_custom_command(
        TARGET exile.forge POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:exile.forge.kernel>
                $<TARGET_FILE_DIR:exile.forge>)
                
add_custom_command(
        TARGET exile.forge POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_CURRENT_SOURCE_DIR}/concept2.conf"
                $<TARGET_FILE_DIR:exile.forge>/concept2.conf)

