cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("exile" C CXX)

add_executable(wnd_t1 "source/main.cpp")

target_link_libraries(wnd_t1 exile.core exile.window.loader)

add_custom_command(
        TARGET wnd_t1 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:exile.core>
                $<TARGET_FILE_DIR:wnd_t1>)

add_custom_command(
        TARGET wnd_t1 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_CURRENT_SOURCE_DIR}/exDefaultULP/exile.ini"
                $<TARGET_FILE_DIR:wnd_t1>/exDefaultULP/exile.ini)

add_custom_command(
        TARGET wnd_t1 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:exileDefaultULP>
                $<TARGET_FILE_DIR:wnd_t1>/exDefaultULP/)

add_custom_command(
        TARGET wnd_t1 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_CURRENT_SOURCE_DIR}/exile.window/exile.ini"
                $<TARGET_FILE_DIR:wnd_t1>/exile.window/exile.ini)

add_custom_command(
        TARGET wnd_t1 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:exile.window>
                $<TARGET_FILE_DIR:wnd_t1>/exile.window/)