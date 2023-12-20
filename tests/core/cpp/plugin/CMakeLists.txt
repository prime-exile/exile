cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("exile" C CXX)


add_library(plugin SHARED "source/main.cpp")

target_link_libraries(plugin exile.core)
add_custom_command(
        TARGET plugin POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_CURRENT_SOURCE_DIR}/exile.ini"
                $<TARGET_FILE_DIR:plugin>)