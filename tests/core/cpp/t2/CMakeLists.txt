cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("exile" C CXX)

add_executable(_t2 "source/main.cpp" )

add_test(NAME _t2_test 
	  COMMAND $<TARGET_FILE:_t2>
	)

add_custom_command(
        TARGET _t2 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:exile.core>
                $<TARGET_FILE_DIR:_t2>)

add_custom_command(
        TARGET _t2 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_CURRENT_SOURCE_DIR}/exile.ini"
                $<TARGET_FILE_DIR:_t2>/exDefaultULP/exile.ini)

add_custom_command(
        TARGET _t2 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:exileDefaultULP>
                $<TARGET_FILE_DIR:_t2>/exDefaultULP/)

target_link_libraries(_t2 exile.core)