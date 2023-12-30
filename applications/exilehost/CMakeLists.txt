cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("exilehost")

add_executable(exilehost "source/main.cpp")

if(WIN32)
target_link_libraries(exilehost PUBLIC exile.core dbghelp)
else()
target_link_libraries(exilehost PUBLIC exile.core)
endif()

add_custom_command(
        TARGET exilehost POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_CURRENT_SOURCE_DIR}/exDefaultULP/exile.ini"
                $<TARGET_FILE_DIR:exilehost>/exDefaultULP/exile.ini)

add_custom_command(
        TARGET exilehost POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:exileDefaultULP>
                $<TARGET_FILE_DIR:exilehost>/exDefaultULP/)

add_custom_command(
        TARGET exilehost POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:exile.core>
                $<TARGET_FILE_DIR:exilehost>)

