cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("exile" C CXX)

add_executable(critical_t1 "source/main.c" )

add_test(NAME critical_t1_test 
	  COMMAND $<TARGET_FILE:memory_t1>
	)


add_custom_command(
        TARGET critical_t1 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:exile.core>
                $<TARGET_FILE_DIR:critical_t1>)

add_custom_command(
        TARGET critical_t1 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_CURRENT_SOURCE_DIR}/critical.conf"
                $<TARGET_FILE_DIR:critical_t1>)

add_custom_command(
        TARGET critical_t1 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:dph>
                $<TARGET_FILE_DIR:critical_t1>)

target_link_libraries(critical_t1 exile.core)